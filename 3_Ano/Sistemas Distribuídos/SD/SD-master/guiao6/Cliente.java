import java.net.*;
import java.io.*;
import java.util.*;

public class Cliente{  
    public static void main(String[] args){
        try {
            Socket socket=new Socket("127.0.0.1", 12345);
            BufferedReader in=new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter out=new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            Scanner ler=new Scanner(System.in);
            String str=null;
            while(!(str=ler.nextLine()).equals("Quit")){
                out.write(str);
                out.newLine();
                out.flush();
                System.out.println(in.readLine());
            }
            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
        }catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}