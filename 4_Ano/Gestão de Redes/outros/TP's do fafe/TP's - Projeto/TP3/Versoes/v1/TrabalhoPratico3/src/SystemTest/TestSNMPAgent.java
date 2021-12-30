package SystemTest;

import AgentSNMP.MOCreator;
import AgentSNMP.SNMPAgent;
import ManagerSNMP.SNMPManager;
import RandomGenerator.RandomServer;
import org.snmp4j.smi.OID;

import java.io.IOException;

public class TestSNMPAgent {

    public static final OID sysDescr = new OID(".1.3.6.1.2.1.1.1.0");

    public static void main(String[] args) throws IOException {
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

    public void init() throws IOException {
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

        // Setup the client to use our newly started agent
        client = new SNMPManager("udp:127.0.0.1/2001");
        client.start();
        // Get back Value which is set
        System.out.println(client.getAsString(sysDescr));
    }

}