package ManagerSNMP;

import java.io.IOException;
import java.util.Scanner;

import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.Target;
import org.snmp4j.TransportMapping;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.Address;
import org.snmp4j.smi.GenericAddress;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.VariableBinding;
import org.snmp4j.transport.DefaultUdpTransportMapping;

public class SNMPManager {

    private Snmp snmp = null;
    private String address = null;

    /**
     * Constructor
     */
    private SNMPManager(String add) {
        address = add;
    }

    public static void main(String[] args) throws IOException {
        System.out.println("***** Welcome to Gestão de Redes Project Number 3 *****\n");
        Scanner in = new Scanner(System.in);
        System.out.println("Please insert IP address and port (IP/port)");
        System.out.print(">> ");
        String s = in.nextLine();
        String sFinal = "udp:" + s;
        SNMPManager client = new SNMPManager(sFinal);
        client.start();

        System.out.println("Please insert valid OID");
        System.out.print(">> ");
        String oid = in.nextLine();
        // .1.3.6.1.3.1.1.5.1.1.x -> seeds
        // .1.3.6.1.3.1.1.4.0 -> reset
        // .1.3.6.1.3.1.1.6.0 -> community
        // .1.3.6.1.3.1.1.1.0 -> refresh
        // .1.3.6.1.3.1.1.2.0 -> table entries
        // .1.3.6.1.3.1.1.3.0 -> digits
        // .1.3.6.1.3.1.1.7.0 -> port
        // .1.3.6.1.3.1.1.8.0 -> seed path
        String sysDescr = client.getAsString(new OID(oid));
        System.out.println("\nResponse from SNMP Agent\n" + sysDescr);
    }

    /**
     * Start the Snmp session. If you forget the listen() method you will not
     * get any answers because the communication is asynchronous
     * and the listen() method listens for answers.
     */
    private void start() throws IOException {
        TransportMapping transport = new DefaultUdpTransportMapping();
        snmp = new Snmp(transport);
        transport.listen();
    }

    /**
     * Method which takes a single OID and returns the response from the agent as a String.
     */
    private String getAsString(OID oid) throws IOException {
        ResponseEvent event = get(new OID[]{oid});
        return event.getResponse().get(0).getVariable().toString();
    }

    /**
     * This method is capable of handling multiple OIDs
     */
    private ResponseEvent get(OID oids[]) throws IOException {
        PDU pdu = new PDU();
        for (OID oid : oids) {
            pdu.add(new VariableBinding(oid));
        }
        pdu.setType(PDU.GET);
        ResponseEvent event = snmp.send(pdu, getTarget(), null);
        if (event != null) {
            return event;
        }
        throw new RuntimeException("GET timed out");
    }

    /**
     * This method returns a Target, which contains information about
     * where the data should be fetched and how.
     */
    private Target getTarget() {
        Address targetAddress = GenericAddress.parse(address);
        CommunityTarget target = new CommunityTarget();
        target.setCommunity(new OctetString("unpredictable"));
        target.setAddress(targetAddress);
        target.setRetries(2);
        target.setTimeout(1500);
        target.setVersion(SnmpConstants.version2c);
        return target;
    }
}