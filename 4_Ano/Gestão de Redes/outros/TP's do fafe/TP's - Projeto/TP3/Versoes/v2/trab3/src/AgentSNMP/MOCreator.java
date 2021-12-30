package AgentSNMP;

import org.snmp4j.agent.mo.MOAccessImpl;
import org.snmp4j.agent.mo.MOScalar;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.Variable;

/**
 * This class creates and returns ManagedObjects
 */
public class MOCreator {
    public static MOScalar<Variable> createReadOnly(OID oid, Object value ){
        return new MOScalar<>(oid, MOAccessImpl.ACCESS_READ_ONLY, getVariable(value));
    }

    public static Variable getVariable(Object value) {
        if(value instanceof String) {
            return new OctetString((String)value);
        }
        throw new IllegalArgumentException("Unmanaged Type: " + value.getClass());
    }
}