import java.net.*;
import java.io.*;

public class Servidor2{
    public static void main(String[] args){
        try{
            ServerSocket sSocket=new ServerSocket(12345);
            int conta=0;
            int soma=0;
            while(true){
                Socket clSocket=sSocket.accept();
                BufferedReader in=new BufferedReader(new InputStreamReader(clSocket.getInputStream()));
                BufferedWriter out=new BufferedWriter(new OutputStreamWriter(clSocket.getOutputStream()));
                String str=in.readLine();
                while(str!=null){
                    soma+=Integer.parseInt(str);
                    out.write(Integer.toString(soma));
                    out.newLine();
                    out.flush();
                    str=in.readLine();
                    conta++;
                }
                out.write(Integer.toString(soma/conta));
                out.newLine();
                out.flush();
                clSocket.shutdownOutput();
                clSocket.shutdownInput();
                clSocket.close();
            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}