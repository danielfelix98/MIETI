package SystemTest;

import AgentSNMP.MOCreator;
import AgentSNMP.SNMPAgent;
import ManagerSNMP.SNMPManager;
import RandomGenerator.RandomServer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import org.snmp4j.smi.OID;

import org.snmp4j.smi.VariableBinding;

import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;

public class TestSNMPAgent {

    public static final OID sysDescr = new OID(".1.3.6.1.2.1.1.1.0");
    
    /* arrayList with the configuration parameters
    * index
    *   0 - porta udp
    *   1 - community-string
    *   2 - refreshRate
    *   3 - table-size
    *   4 - number-size
    *   5 - first-seed path
    */
    ArrayList<String> params = new ArrayList<>(); 
    
    public static void main(String[] args) throws IOException, ParseException {
        TestSNMPAgent client = new TestSNMPAgent("udp:127.0.0.1/5555");
        client.init();
    }

    SNMPAgent agent = null;
    /**
     * This is the client which we have created earlier
     */
    SNMPManager client = null;

    String address = null;

    /**
     * Constructor
     *
     * @param add
     */
    public TestSNMPAgent(String add) {
        address = add;
    }

    public void init() throws IOException, ParseException {
        
        configurationParameters();
        
        
        //---------- start agent ------------------------------
        agent = new SNMPAgent("0.0.0.0/2001");
        agent.start();
        
        RandomServer randomServer = new RandomServer();
        int lel = randomServer.main();
        String enviar = "Numero random: " + lel;

        // Since BaseAgent registers some MIBs by default we need to unregister
        // one before we register our own sysDescr. Normally you would
        // override that method and register the MIBs that you need
        agent.unregisterManagedObject(agent.getSnmpv2MIB());

        // Register a system description, use one from you product environment
        // to test with
        agent.registerManagedObject(MOCreator.createReadOnly(sysDescr,enviar));

        while(true){
            randomServer = new RandomServer();
            lel = randomServer.main();
            enviar = "Numero random: " + lel;

            VariableBinding binding = new VariableBinding(sysDescr, MOCreator.getVariable(enviar));
            agent.setManagedObject(binding);
        }

        // Setup the client to use our newly started agent
        // client = new SNMPManager("udp:127.0.0.1/2001");
        //client.start();
        // Get back Value which is set
        //System.out.println(client.getAsString(sysDescr));
    }
    
    public void configurationParameters() throws FileNotFoundException,IOException{
        File conf = new File("unpredictable-conf.txt");
        if(conf.exists()) // if exists it's true
        {
            BufferedReader fileParameters = null;
            String param="";
            
            fileParameters = new BufferedReader(new FileReader("unpredictable-conf.txt"));
            while((param=fileParameters.readLine())!=null){
                //System.out.println(param);
                String[] splitParam = param.split(" ");
                //System.out.println(splitParam[1]);
                params.add(splitParam[1]);
            }
        } else{
            System.out.println("Sem ficheiro de configuracao. Coloque na pasta respectiva!");
            System.out.println("Pastaaaa  "+System.getProperty("user.dir"));
            System.exit(0);
        }
    }

}