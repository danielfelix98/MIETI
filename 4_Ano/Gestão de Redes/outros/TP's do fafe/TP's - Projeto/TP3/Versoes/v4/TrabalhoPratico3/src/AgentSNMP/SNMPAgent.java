package AgentSNMP;

import MIB.UMINHOGRMIB;
import org.snmp4j.TransportMapping;
import org.snmp4j.agent.*;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.security.MutableVACM;
import org.snmp4j.mp.MPv3;
import org.snmp4j.security.SecurityLevel;
import org.snmp4j.security.SecurityModel;
import org.snmp4j.security.USM;
import org.snmp4j.smi.*;
import org.snmp4j.transport.TransportMappings;

import java.io.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.TimerTask;

public class SNMPAgent extends BaseAgent {

    private String address;
    /**
     * arrayList with the configuration parameters
     * index
     * 0 - porta udp
     * 1 - community-string
     * 2 - refreshRate
     * 3 - table-size
     * 4 - number-size
     * 5 - first-seed path
     */
    private ArrayList<String> params = new ArrayList<>();
    private int enviar;
    private String enviarFinal;
    private MOScalar<Variable> serverCount;
    private static final OID sysDescr = new OID(".1.3.6.1.3.1.1.4.0");

    private SNMPAgent(String add) throws IOException {
        /*
           Creates a base agent with boot-counter, config file, and a
           CommandProcessor for processing SNMP requests. Parameters:
           "bootCounterFile" - a file with serialized boot-counter information
           (read/write). If the file does not exist it is created on shutdown of
           the agent. "configFile" - a file with serialized configuration
           information (read/write). If the file does not exist it is created on
           shutdown of the agent. "commandProcessor" - the CommandProcessor
           instance that handles the SNMP requests.
         */
        super(new File("conf.agent"),
                new File("bootCounter.agent"),
                new CommandProcessor(new OctetString(MPv3.createLocalEngineID())));
        this.address = add;
    }

    /**
     * Adds community to security name mappings needed for SNMPv2c.
     */
    @Override
    protected void addCommunities(SnmpCommunityMIB communityMIB) {
        Variable[] com2sec = new Variable[]{new OctetString("public"),
                new OctetString("cpublic"), // security name
                getAgent().getContextEngineID(), // local engine ID
                new OctetString("public"), // default context name
                new OctetString(), // transport tag
                new Integer32(StorageType.nonVolatile), // storage type
                new Integer32(RowStatus.active) // row status
        };
        MOTableRow row = communityMIB.getSnmpCommunityEntry().createRow(new OctetString("public2public").toSubIndex(true), com2sec);
        communityMIB.getSnmpCommunityEntry().addRow((SnmpCommunityMIB.SnmpCommunityEntryRow) row);
    }

    /**
     * Adds initial notification targets and filters.
     */
    @Override
    protected void addNotificationTargets(SnmpTargetMIB arg0, SnmpNotificationMIB arg1) {
        // TODO Auto-generated method stub
    }

    /**
     * Adds all the necessary initial users to the USM.
     */
    @Override
    protected void addUsmUser(USM arg0) {
        // TODO Auto-generated method stub
    }

    /**
     * Adds initial VACM configuration.
     */
    @Override
    protected void addViews(VacmMIB vacm) {
        vacm.addGroup(SecurityModel.SECURITY_MODEL_SNMPv2c,
                new OctetString("cpublic"),
                new OctetString("v1v2group"),
                StorageType.nonVolatile);

        vacm.addAccess(new OctetString("v1v2group"),
                new OctetString("public"),
                SecurityModel.SECURITY_MODEL_ANY, SecurityLevel.NOAUTH_NOPRIV,
                MutableVACM.VACM_MATCH_EXACT, new OctetString("fullReadView"),
                new OctetString("fullWriteView"), new OctetString("fullNotifyView"),
                StorageType.nonVolatile);

        vacm.addViewTreeFamily(new OctetString("fullReadView"),
                new OID("1.3"),
                new OctetString(),
                VacmMIB.vacmViewIncluded,
                StorageType.nonVolatile);
    }

    /**
     * Unregister the basic MIB modules from the agent's MOServer.
     */
    @Override
    protected void unregisterManagedObjects() {
        // TODO Auto-generated method stub
    }

    /**
     * Register additional managed objects at the agent's server.
     */
    @Override
    protected void registerManagedObjects() {
        // TODO Auto-generated method stub
    }

    protected void initTransportMappings() throws IOException {
        transportMappings = new TransportMapping[1];
        Address addr = GenericAddress.parse(address);
        TransportMapping tm = TransportMappings.getInstance().createTransportMapping(addr);
        transportMappings[0] = tm;
    }

    /**
     * Start method invokes some initialization methods needed to start the
     * agent
     */
    private void start() throws IOException {
        init();

        MOFactory moFactory = DefaultMOFactory.getInstance();
        UMINHOGRMIB uminhogrmib = new UMINHOGRMIB(moFactory);
         /*
           This method reads some old config from a file and causes
           unexpected behavior.
           loadConfig(ImportModes.REPLACE_CREATE);
         */
        addShutdownHook();
        getServer().addContext(new OctetString("public"));
        finishInit();
        run();
        sendColdStartNotification();

        unregisterManagedObject(getSnmpv2MIB());

        enviar = RandomServer();
        enviarFinal = "Numero random: " + enviar;

        registerManagedObject(enviarFinal);

        int delay = 1000;
        int interval = 1000;
        java.util.Timer timer;
        timer = new java.util.Timer();

        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                enviar = RandomServer();
                enviarFinal = "Numero random: " + enviar;
                setValue(enviarFinal);
                System.out.println(enviarFinal);
            }
        }, delay, interval);
    }

    /**
     * Clients can register the MO they need
     */
    private void registerManagedObject(Object value) {
        try {
            serverCount = new MOScalar<>(sysDescr, MOAccessImpl.ACCESS_READ_ONLY, getVariable(value));
            server.register(serverCount, null);
        } catch (DuplicateRegistrationException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void setValue(Object value) {
        serverCount.setValue(getVariable(value));
    }

    private static Variable getVariable(Object value) {
        if (value instanceof String) {
            return new OctetString((String) value);
        }
        throw new IllegalArgumentException("Unmanaged Type: " + value.getClass());
    }

    private void unregisterManagedObject(MOGroup moGroup) {
        moGroup.unregisterMOs(server, getContext(moGroup));
    }

    private void configurationParameters() throws IOException {
        File conf = new File("unpredictable-conf.txt");
        if (conf.exists()) { // if exists it's true
            BufferedReader fileParameters;
            String param;
            fileParameters = new BufferedReader(new FileReader("unpredictable-conf.txt"));
            while ((param = fileParameters.readLine()) != null) {
                String[] splitParam = param.split(" ");
                params.add(splitParam[1]);
            }
        } else {
            System.out.println("Sem ficheiro de configuracao.\n Coloque na pasta respectiva!");
            System.out.println("Pasta  " + System.getProperty("user.dir"));
            System.exit(0);
        }
    }

    private static int RandomServer() {
        Random randomGenerator = new Random();
        return randomGenerator.nextInt(10000000);
    }

    public static void main(String[] args) throws IOException {
        SNMPAgent agent = new SNMPAgent("0.0.0.0/6666");
        agent.configurationParameters();
        agent.start();
    }
}