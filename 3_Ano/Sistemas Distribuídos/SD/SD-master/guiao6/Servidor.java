import java.net.*;
import java.io.*;

public class Servidor{
    public static void main(String[] args){
        try{
            ServerSocket sSocket=new ServerSocket(12345);
            while(true){
                Socket clSocket=sSocket.accept();
                BufferedReader in=new BufferedReader(new InputStreamReader(clSocket.getInputStream()));
                BufferedWriter out=new BufferedWriter(new OutputStreamWriter(clSocket.getOutputStream()));
                String str=in.readLine();
                while(str!=null){
                    out.write(str);
                    out.newLine();
                    out.flush();
                    System.out.println(str);
                    str=in.readLine();
                }
                clSocket.shutdownOutput();
                clSocket.shutdownInput();
                clSocket.close();
            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}