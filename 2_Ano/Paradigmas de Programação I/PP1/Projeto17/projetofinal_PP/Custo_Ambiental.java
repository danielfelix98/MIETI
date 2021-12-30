import java.util.GregorianCalendar;
import java.util.Objects;
import java.util.*;
import java.lang.Iterable;
import java.io.*;
public interface Custo_Ambiental 
{
    public void setCustoAmbientalbase(long cst_amb);
    public double getCustoAmbientalbase();
    public double calcula_custo_ambiental();
}