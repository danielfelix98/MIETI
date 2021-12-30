package MIB;

//--AgentGen BEGIN=_BEGIN
//--AgentGen END

import org.snmp4j.smi.*;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.agent.*;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.mo.snmp.smi.*;
import org.snmp4j.agent.request.*;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogAdapter;
import org.snmp4j.agent.mo.snmp.tc.*;


//--AgentGen BEGIN=_IMPORT
//--AgentGen END

public class UMINHOGRMIB implements MOGroup {

    private static final LogAdapter LOGGER = LogFactory.getLogger(UMINHOGRMIB.class);

//--AgentGen BEGIN=_STATIC
//--AgentGen END

    // Factory
    private MOFactory moFactory = DefaultMOFactory.getInstance();

// Constants

    /**
     * OID of this MIB module for usage which can be
     * used for its identification.
     */
    public static final OID oidUminhoGrMib = new OID(new int[]{1, 3, 6, 1, 3, 1});

    // Identities
// Scalars
    public static final OID oidUnpredictableRefresh =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 1, 0});
    public static final OID oidUnpredictableEntries =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 2, 0});
    public static final OID oidUnpredictableDigits =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 3, 0});
    public static final OID oidUnpredictableReset =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 4, 0});
// Tables

// Notifications

// Enumerations

    // TextualConventions
    private static final String TC_MODULE_SNMPV2_TC = "SNMPv2-TC";
    private static final String TC_DISPLAYSTRING = "DisplayString";

    // Scalars
    private MOScalar<Integer32> unpredictableRefresh;
    private MOScalar<Integer32> unpredictableEntries;
    private MOScalar<Integer32> unpredictableDigits;
    private MOScalar<OctetString> unpredictableReset;

    // Tables
    public static final OID oidRandomEntry =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 5, 1});

    // Index OID definitions
    public static final OID oidRandomKey =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 5, 1, 1});
    public static final OID oidRandomNumber =
            new OID(new int[]{1, 3, 6, 1, 3, 1, 1, 5, 1, 2});

// Column TC definitions for randomEntry:

    // Column sub-identifier definitions for randomEntry:
    public static final int colRandomKey = 1;
    public static final int colRandomNumber = 2;

    // Column index definitions for randomEntry:
    public static final int idxRandomKey = 0;
    public static final int idxRandomNumber = 1;

    private MOTableSubIndex[] randomEntryIndexes;
    private MOTableIndex randomEntryIndex;

    private MOTable<RandomEntryRow,
            MOColumn,
            MOTableModel<RandomEntryRow>> randomEntry;
    private MOTableModel<RandomEntryRow> randomEntryModel;


//--AgentGen BEGIN=_MEMBERS
//--AgentGen END

    /**
     * Constructs a UMINHO-GR-MIB instance without actually creating its
     * <code>ManagedObject</code> instances. This has to be done in a
     * sub-class constructor or after construction by calling
     * {@link #createMO(MOFactory moFactory)}.
     */
    protected UMINHOGRMIB() {
//--AgentGen BEGIN=_DEFAULTCONSTRUCTOR
//--AgentGen END
    }

    /**
     * Constructs a UMINHO-GR-MIB instance and actually creates its
     * <code>ManagedObject</code> instances using the supplied
     * <code>MOFactory</code> (by calling
     * {@link #createMO(MOFactory moFactory)}).
     *
     * @param moFactory the <code>MOFactory</code> to be used to create the
     *                  managed objects for this module.
     */
    public UMINHOGRMIB(MOFactory moFactory) {
        this();
        createMO(moFactory);
//--AgentGen BEGIN=_FACTORYCONSTRUCTOR
//--AgentGen END
    }

//--AgentGen BEGIN=_CONSTRUCTORS
//--AgentGen END

    /**
     * Create the ManagedObjects defined for this MIB module
     * using the specified {@link MOFactory}.
     *
     * @param moFactory the <code>MOFactory</code> instance to use for object
     *                  creation.
     */
    protected void createMO(MOFactory moFactory) {
        addTCsToFactory(moFactory);
        unpredictableRefresh =
                moFactory.createScalar(oidUnpredictableRefresh,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
                        new Integer32());
        unpredictableEntries =
                moFactory.createScalar(oidUnpredictableEntries,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
                        new Integer32());
        unpredictableDigits =
                moFactory.createScalar(oidUnpredictableDigits,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
                        new Integer32());
        unpredictableReset =
                new UnpredictableReset(oidUnpredictableReset,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE));
        unpredictableReset.addMOValueValidationListener(new UnpredictableResetValidator());
        createRandomEntry(moFactory);
    }

    public MOScalar<Integer32> getUnpredictableRefresh() {
        return unpredictableRefresh;
    }

    public MOScalar<Integer32> getUnpredictableEntries() {
        return unpredictableEntries;
    }

    public MOScalar<Integer32> getUnpredictableDigits() {
        return unpredictableDigits;
    }

    public MOScalar<OctetString> getUnpredictableReset() {
        return unpredictableReset;
    }


    public MOTable<RandomEntryRow, MOColumn, MOTableModel<RandomEntryRow>> getRandomEntry() {
        return randomEntry;
    }


    @SuppressWarnings(value = {"unchecked"})
    private void createRandomEntry(MOFactory moFactory) {
        // Index definition
        randomEntryIndexes =
                new MOTableSubIndex[]{
                        moFactory.createSubIndex(oidRandomKey,
                                SMIConstants.SYNTAX_INTEGER, 1, 1),
                        moFactory.createSubIndex(oidRandomNumber,
                                SMIConstants.SYNTAX_INTEGER, 1, 1)};

        randomEntryIndex =
                moFactory.createIndex(randomEntryIndexes,
                        false,
                        new MOTableIndexValidator() {
                            public boolean isValidIndex(OID index) {
                                boolean isValidIndex = true;
                                //--AgentGen BEGIN=randomEntry::isValidIndex
                                //--AgentGen END
                                return isValidIndex;
                            }
                        });

        // Columns
        MOColumn[] randomEntryColumns = new MOColumn[2];
        randomEntryColumns[idxRandomKey] =
                moFactory.createColumn(colRandomKey,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        randomEntryColumns[idxRandomNumber] =
                moFactory.createColumn(colRandomNumber,
                        SMIConstants.SYNTAX_INTEGER,
                        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        // Table model
        randomEntryModel =
                moFactory.createTableModel(oidRandomEntry,
                        randomEntryIndex,
                        randomEntryColumns);
        ((MOMutableTableModel<RandomEntryRow>) randomEntryModel).setRowFactory(
                new RandomEntryRowFactory());
        randomEntry =
                moFactory.createTable(oidRandomEntry,
                        randomEntryIndex,
                        randomEntryColumns,
                        randomEntryModel);
    }


    public void registerMOs(MOServer server, OctetString context)
            throws DuplicateRegistrationException {
        // Scalar Objects
        server.register(this.unpredictableRefresh, context);
        server.register(this.unpredictableEntries, context);
        server.register(this.unpredictableDigits, context);
        server.register(this.unpredictableReset, context);
        server.register(this.randomEntry, context);
//--AgentGen BEGIN=_registerMOs
//--AgentGen END
    }

    public void unregisterMOs(MOServer server, OctetString context) {
        // Scalar Objects
        server.unregister(this.unpredictableRefresh, context);
        server.unregister(this.unpredictableEntries, context);
        server.unregister(this.unpredictableDigits, context);
        server.unregister(this.unpredictableReset, context);
        server.unregister(this.randomEntry, context);
//--AgentGen BEGIN=_unregisterMOs
//--AgentGen END
    }

// Notifications

    // Scalars
    public class UnpredictableReset extends DisplayStringScalar<OctetString> {
        UnpredictableReset(OID oid, MOAccess access) {
            super(oid, access, new OctetString(),
                    0,
                    255);
//--AgentGen BEGIN=unpredictableReset
//--AgentGen END
        }

        public int isValueOK(SubRequest request) {
            Variable newValue =
                    request.getVariableBinding().getVariable();
            int valueOK = super.isValueOK(request);
            if (valueOK != SnmpConstants.SNMP_ERROR_SUCCESS) {
                return valueOK;
            }
            OctetString os = (OctetString) newValue;
            if (!(((os.length() >= 0) && (os.length() <= 255)))) {
                valueOK = SnmpConstants.SNMP_ERROR_WRONG_LENGTH;
            }
            //--AgentGen BEGIN=unpredictableReset::isValueOK
            //--AgentGen END
            return valueOK;
        }

        public OctetString getValue() {
            //--AgentGen BEGIN=unpredictableReset::getValue
            //--AgentGen END
            return super.getValue();
        }

        public int setValue(OctetString newValue) {
            //--AgentGen BEGIN=unpredictableReset::setValue
            //--AgentGen END
            return super.setValue(newValue);
        }

        //--AgentGen BEGIN=unpredictableReset::_METHODS
        //--AgentGen END

    }


// Value Validators

    /**
     * The <code>UnpredictableResetValidator</code> implements the value
     * validation for <code>UnpredictableReset</code>.
     */
    static class UnpredictableResetValidator implements MOValueValidationListener {

        public void validate(MOValueValidationEvent validationEvent) {
            Variable newValue = validationEvent.getNewValue();
            OctetString os = (OctetString) newValue;
            if (!(((os.length() >= 0) && (os.length() <= 255)))) {
                validationEvent.setValidationStatus(SnmpConstants.SNMP_ERROR_WRONG_LENGTH);
                return;
            }
            //--AgentGen BEGIN=unpredictableReset::validate
            //--AgentGen END
        }
    }


// Rows and Factories

    public class RandomEntryRow extends DefaultMOMutableRow2PC {

        //--AgentGen BEGIN=randomEntry::RowMembers
        //--AgentGen END

        public RandomEntryRow(OID index, Variable[] values) {
            super(index, values);
            //--AgentGen BEGIN=randomEntry::RowConstructor
            //--AgentGen END
        }

        public Integer32 getRandomKey() {
            //--AgentGen BEGIN=randomEntry::getRandomKey
            //--AgentGen END
            return (Integer32) super.getValue(idxRandomKey);
        }

        public void setRandomKey(Integer32 newColValue) {
            //--AgentGen BEGIN=randomEntry::setRandomKey
            //--AgentGen END
            super.setValue(idxRandomKey, newColValue);
        }

        public Integer32 getRandomNumber() {
            //--AgentGen BEGIN=randomEntry::getRandomNumber
            //--AgentGen END
            return (Integer32) super.getValue(idxRandomNumber);
        }

        public void setRandomNumber(Integer32 newColValue) {
            //--AgentGen BEGIN=randomEntry::setRandomNumber
            //--AgentGen END
            super.setValue(idxRandomNumber, newColValue);
        }

        public Variable getValue(int column) {
            //--AgentGen BEGIN=randomEntry::RowGetValue
            //--AgentGen END
            switch (column) {
                case idxRandomKey:
                    return getRandomKey();
                case idxRandomNumber:
                    return getRandomNumber();
                default:
                    return super.getValue(column);
            }
        }

        public void setValue(int column, Variable value) {
            //--AgentGen BEGIN=randomEntry::RowSetValue
            //--AgentGen END
            switch (column) {
                case idxRandomKey:
                    setRandomKey((Integer32) value);
                    break;
                case idxRandomNumber:
                    setRandomNumber((Integer32) value);
                    break;
                default:
                    super.setValue(column, value);
            }
        }

        //--AgentGen BEGIN=randomEntry::Row
        //--AgentGen END
    }

    class RandomEntryRowFactory implements MOTableRowFactory<RandomEntryRow> {
        public synchronized RandomEntryRow createRow(OID index, Variable[] values)
                throws UnsupportedOperationException {
            RandomEntryRow row =
                    new RandomEntryRow(index, values);
            //--AgentGen BEGIN=randomEntry::createRow
            //--AgentGen END
            return row;
        }

        public synchronized void freeRow(RandomEntryRow row) {
            //--AgentGen BEGIN=randomEntry::freeRow
            //--AgentGen END
        }

        //--AgentGen BEGIN=randomEntry::RowFactory
        //--AgentGen END
    }


//--AgentGen BEGIN=_METHODS
//--AgentGen END

    // Textual Definitions of MIB module UMINHO-GR-MIB
    protected void addTCsToFactory(MOFactory moFactory) {
    }


//--AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_BEGIN
//--AgentGen END

    // Textual Definitions of other MIB modules
    public void addImportedTCsToFactory(MOFactory moFactory) {
    }

//--AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_END
//--AgentGen END

//--AgentGen BEGIN=_CLASSES
//--AgentGen END

//--AgentGen BEGIN=_END
//--AgentGen END
}


