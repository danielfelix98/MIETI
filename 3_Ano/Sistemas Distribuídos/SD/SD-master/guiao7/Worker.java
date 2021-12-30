import java.net.*;
import java.io.*;

class Worker extends Thread{
    private Socket clSocket;
    public Worker(Socket clsocket){
        this.clSocket= clsocket;
    }
    public void run(){
        try{
            BufferedReader in=new BufferedReader(new InputStreamReader(clSocket.getInputStream()));
            BufferedWriter out=new BufferedWriter(new OutputStreamWriter(clSocket.getOutputStream()));
            String str=in.readLine();
            while(str!=null){
                out.write(Integer.toString(soma));
                out.newLine();
                out.flush();
                System.out.println(str);
                str=in.readLine();
            }
            clSocket.shutdownOutput();
            clSocket.shutdownInput();
            clSocket.close();
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}