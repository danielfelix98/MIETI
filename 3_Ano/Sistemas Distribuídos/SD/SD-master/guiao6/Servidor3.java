import java.net.*;
import java.io.*;

public class Servidor3{
    public static void main(String[] args){
        try{
            ServerSocket sSocket=new ServerSocket(12345);
            System.out.println("Server is running!");
            while(true){
                Thread t = new Thread(new Worker(sSocket.accept()));
                t.start();
            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}