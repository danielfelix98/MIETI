package AgentSNMP;

import MIB.UMINHOGRMIB;
import org.snmp4j.TransportMapping;
import org.snmp4j.agent.BaseAgent;
import org.snmp4j.agent.CommandProcessor;
import org.snmp4j.agent.DuplicateRegistrationException;
import org.snmp4j.agent.MOGroup;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.security.MutableVACM;
import org.snmp4j.mp.MPv3;
import org.snmp4j.security.SecurityLevel;
import org.snmp4j.security.SecurityModel;
import org.snmp4j.security.USM;
import org.snmp4j.smi.*;
import org.snmp4j.transport.TransportMappings;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.text.Normalizer;
import java.util.ArrayList;

public class SNMPAgent extends BaseAgent {

    private String address;
    private ArrayList<String> params = new ArrayList<>();
    private ArrayList<String> seeds = new ArrayList<>();
    private MOFactory moFactory = DefaultMOFactory.getInstance();
    private UMINHOGRMIB uminhogrmib = new UMINHOGRMIB(moFactory);
    private String community;
    private String refresh;
    private String tableSize;
    private String numberSize;
    private String seedPat;
    private static String cc = "dfh8ty3t-4rq8549";
    private int i = 1;
    private java.util.Timer timer = new java.util.Timer();
    private RefreshTimer timers;
    private int u = 0;
    private int delay;
    private long interval;

    public SNMPAgent(String add) throws IOException {
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
        Variable[] com2sec = new Variable[]{new OctetString(community),
                new OctetString("c" + community), // security name
                getAgent().getContextEngineID(), // local engine ID
                new OctetString(community), // default context name
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
                new OctetString("c" + community),
                new OctetString("v1v2group"),
                StorageType.nonVolatile);

        vacm.addAccess(new OctetString("v1v2group"),
                new OctetString(community),
                SecurityModel.SECURITY_MODEL_ANY, SecurityLevel.NOAUTH_NOPRIV,
                MutableVACM.VACM_MATCH_EXACT, new OctetString("fullReadView"),
                new OctetString("fullWriteView"), new OctetString("fullNotifyView"),
                StorageType.nonVolatile);

        vacm.addViewTreeFamily(new OctetString("fullWriteView"),
                new OID("1.3"),
                new OctetString(),
                VacmMIB.vacmViewIncluded,
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
        configurationParameters();
        setParameters();

        init();
        unregisterManagedObject(getSnmpv2MIB());
        registerManagedObject();
         /*
           This method reads some old config from a file and causes
           unexpected behavior.
           loadConfig(ImportModes.REPLACE_CREATE);
         */
        addShutdownHook();
        getServer().addContext(new OctetString(community));
        finishInit();
        run();
        sendColdStartNotification();

        getSeeds();
        char[][] lel = getMatrix();
        int tabSize = Integer.parseInt(tableSize);
        for (int p = 0; p < tabSize; p++) {
            char[] q = lel[p];
            String w = String.valueOf(q);
            System.out.println(w);
            setValue(w);
        }

        delay = Integer.parseInt(refresh) * 10000;
        interval = (long) ((1 / Float.parseFloat(refresh)) * 1000);
        timers = new RefreshTimer();

        MOChangeListener l = new MOChangeListener() {
            @Override
            public void beforePrepareMOChange(MOChangeEvent moChangeEvent) {
            }

            @Override
            public void afterPrepareMOChange(MOChangeEvent moChangeEvent) {
            }

            @Override
            public void beforeMOChange(MOChangeEvent moChangeEvent) {
            }

            @Override
            public void afterMOChange(MOChangeEvent moChangeEvent) {
                if (uminhogrmib.getUnpredictableReset().getValue().equals(getOctetString(cc))) {
                    uminhogrmib.getUnpredictableReset().setValue(getOctetString(""));
                    u = 0;
                    timers.cancelTimer();
                    try {
                        reset();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    try {
                        timers.startTimer(delay, interval);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        uminhogrmib.getUnpredictableReset().addMOChangeListener(l);
        timers.startTimer(0, interval);
    }

    public void refresh() {
        // Refresh M(T,K)
        // Update Mib -> setValue(New Matriz)
        System.out.print(u++ + "\n");
    }

    private void reset() throws IOException {
        i = 1;
        getSeeds();
        for (int h = 1; h <= 256; h++) {
            uminhogrmib.getRandomEntry().removeRow(new OID(new int[]{h}));
        }

        char[][] matriz = new char[256][8];
        for (int i = 0; i < 256; i++) {
            String aux = seeds.get(i);
            for (int j = 0; j < 8; j++) {
                char[] split = aux.toCharArray();
                matriz[i][j] = split[j];
            }
        }
        for (int p = 0; p < 256; p++) {
            char[] q = matriz[p];
            String w = String.valueOf(q);
            System.out.println(w);
            setValue(w);
        }
    }

    /**
     * Clients can register the MO they need
     */
    private void registerManagedObject() {
        try {
            uminhogrmib.registerMOs(server, getDefaultContext());
        } catch (DuplicateRegistrationException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void setValue(Object value) {
        DefaultMOMutableTableModel model = (DefaultMOMutableTableModel) uminhogrmib.getRandomEntry().getModel();
        Variable[] v = new Variable[]{getOctetString(value)};
        model.addRow(model.createRow((new OID(new int[]{i})), v));
        i++;
    }

    private void setParameters() {
        String porta = params.get(0);
        community = params.get(1);
        refresh = params.get(2);
        tableSize = params.get(3);
        numberSize = params.get(4);
        seedPat = params.get(5);
        String seedPath = Normalizer.normalize(seedPat, Normalizer.Form.NFD);
        seedPath = seedPath.replaceAll("[\\p{InCombiningDiacriticalMarks}]", "");

        uminhogrmib.getUnpredictableCommunity().setValue(getOctetString(community));
        uminhogrmib.getUnpredictableSeed().setValue(getOctetString(seedPath));
        uminhogrmib.getUnpredictableRefresh().setValue(getInteger(refresh));
        uminhogrmib.getUnpredictableEntries().setValue(getInteger(tableSize));
        uminhogrmib.getUnpredictableDigits().setValue(getInteger(numberSize));
        uminhogrmib.getUnpredictablePort().setValue(getInteger(porta));
    }

    private static Integer32 getInteger(Object value) {
        if (value instanceof String) {
            Integer x = Integer.valueOf((String) value);
            return new Integer32(x);
        }
        throw new IllegalArgumentException("Unmanaged Type: " + value.getClass());
    }

    private static OctetString getOctetString(Object value) {
        if (value instanceof String) {
            return new OctetString((String) value);
        }
        throw new IllegalArgumentException("Unmanaged Type: " + value.getClass());
    }

    private void unregisterManagedObject(MOGroup moGroup) {
        uminhogrmib.unregisterMOs(server, getContext(moGroup));
    }

    private void configurationParameters() throws IOException {
        /*
         * ArrayList with the configuration parameters
         * index
         * 0 - porta udp
         * 1 - community-string
         * 2 - refreshRate
         * 3 - table-size
         * 4 - number-size
         * 5 - first-seed path
        */
        File conf = new File("unpredictable-conf");
        if (conf.exists()) { // if exists it's true
            BufferedReader fileParameters;
            String param;
            fileParameters = new BufferedReader(new FileReader("unpredictable-conf"));
            while ((param = fileParameters.readLine()) != null) {
                String[] splitParam = param.split(":");
                params.add(splitParam[1]);
            }
        } else {
            System.out.println("Sem ficheiro de configuracao.\n Coloque na pasta respectiva!");
            System.out.println("Pasta  " + System.getProperty("user.dir"));
            System.exit(0);
        }
    }

    private void getSeeds() throws IOException {
        File conf = new File(seedPat);
        if (conf.exists()) { // if exists it's true
            BufferedReader fileParameters;
            String param;
            fileParameters = new BufferedReader(new FileReader("1st-seed"));
            while ((param = fileParameters.readLine()) != null) {
                seeds.add(param);
            }
        } else {
            System.out.println("Sem ficheiro de configuracao.\nColoque na pasta respectiva!");
            System.out.println("Pasta  " + System.getProperty("user.dir"));
            System.exit(0);
        }
    }

    private char[][] getMatrix() {
        int numSize = Integer.parseInt(numberSize);
        int tabSize = Integer.parseInt(tableSize);
        char[][] matriz = new char[tabSize][numSize];
        for (int i = 0; i < tabSize; i++) {
            String aux = seeds.get(i);
            for (int j = 0; j < numSize; j++) {
                char[] split = aux.toCharArray();
                matriz[i][j] = split[j];
            }
        }
        return matriz;
    }

    public static void main(String[] args) throws IOException {
        System.out.println("***** Welcome to SNMP Random Generator Agent *****");
        SNMPAgent agent = new SNMPAgent("0.0.0.0/6666");
        agent.start();
    }
}