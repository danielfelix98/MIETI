import java.net.*;
import java.io.*;

class Worker extends Thread{
    private Socket clSocket;
    public Worker(Socket clsocket){
        this.clSocket= clsocket;
    }
    public void run(){
        try{
            BufferedReader in = new BufferedReader(new InputStreamReader(clSocket.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(clSocket.getOutputStream()));
            int soma=0;
            int conta=0;
            String str = in.readLine();
            while(str != null){
                soma+= Integer.parseInt(str);
                out.write(Integer.toString(soma));
                out.newLine();
                out.flush();
                System.out.println(str);
                str = in.readLine();
                conta++;                    
            }
            out.write(Integer.toString(soma/conta));
            out.newLine();
            out.flush();
            clSocket.shutdownOutput();
            clSocket.shutdownInput();
            clSocket.close();   
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }
}