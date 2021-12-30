/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

import ManagerSNMP.SNMPManager;
import java.io.IOException;
import org.snmp4j.smi.OID;

/**
 *
 * @author root
 */
public class cliente {

    private static SNMPManager client;
        public static final OID sysDescr = new OID(".1.3.6.1.2.1.1.1.0");

    
    public static void main(String[] args) throws IOException{
        // Setup the client to use our newly started agent
        client = new SNMPManager("udp:127.0.0.1/2001");
       client.start();
       // Get back Value which is set
       System.out.println(client.getAsString(sysDescr));
    }
    
}
