package server;

import java.io.*;
import java.util.*;
import java.net.*;

public class Servidor {
    public static final int Socket_porta = 9999;

    private static final HashMap<String, Boolean> tipos = new HashMap<String, Boolean>();
    private static final HashMap<String, String> ligacaoClientes = new HashMap<String, String>();
    private static final HashMap<String, PrintWriter> envia_mensagem = new HashMap<String, PrintWriter>();

    public static void main(String[] args) throws IOException {

        ServerSocket socket = null;
        try {
            socket = new ServerSocket(Socket_porta); //Serversocket é criado na porta 9999
            System.out.println("Servidor esta ligado na porta " + Socket_porta);
        } catch (IOException e) { //Se não se conseguir ligar á porta 9999
            System.out.println("O Servidor não se conseguiu ligar á porta " + Socket_porta);
            System.exit(-1);
        }
        try{
            while (1==1) {
                new Thread(new LigarClientes(socket.accept())).start();//Inicia um thread com a classe LigarClientes por 
                                                                        //cada cliente ligado
            }
        }catch (IOException e) {}
    }
    
    private static class LigarClientes implements Runnable {
        private BufferedReader input; // Buffer de leitura
        private PrintWriter output; // Printwiter para enviar mensagens para o cliente
        private final Socket socket; //Socket do cliente para o servidor
        private String tipo; //Tipo de utilizador
        private String parceiro; //Tipo de utilizador parceiro
        private PrintWriter enviar; // PrintWriter para enviar as mensagens recebidas de um cliente

        public LigarClientes(Socket socket) {this.socket = socket;}
        
        @Override
        public void run(){
            try {
                input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                output = new PrintWriter(socket.getOutputStream(), true);

                while (1==1) {
                    output.println("DIGITENOME");
                    tipo = input.readLine();
                    if (!(("user".equals(tipo))|("genious".equals(tipo)))) {
                        continue;
                    }
                    synchronized (tipos) {
                        tipos.put(tipo, false);//Não tem parceiro
                        break;
                    }
                }

                output.println("NOMEACEITE");
                envia_mensagem.put(tipo, output);//Prepara o PrintWriter para enviar mensagens 

                while (1==1) {
                    String tipoparc = null;
                    if("user".equals(tipo)){tipoparc="genious";}//Se o tipo do cliente é user o parceiro é genious
                    if("genious".equals(tipo)){tipoparc="user";}//Se o tipo do cliente é genious o parceiro é user
                    synchronized (tipos) {
                        if (!tipos.containsKey(tipoparc)) {//Se não existe em tipos um cliente do tipo "tipoarc"
                            continue;
                        }else{
                            if (!tipos.get(tipoparc)) { //Se o cliente ainda não tem parceiro
                                parceiro = tipoparc; //O parceiro vai ser
                                tipos.replace(tipoparc, false, true);//Já não se pode conectar ninguém a este parceiro
                                ligacaoClientes.put(tipoparc,tipo);//Emparelhamento
                                ligacaoClientes.put(tipo,tipoparc);//dos clientes
                                break;
                            }else{continue;}
                        }
                    }
                }
                output.println("PARCEIROCONECTADO");//Informa o cliente que já tem um parceiro      
                enviar = envia_mensagem.get(parceiro);//Pritwriter para enviar as mensagens para cliente, com o nome
                                                      //incluido em parceiro
                while (1==1) {
                    String mensagem = input.readLine();
                    mensagem = mensagem.substring(8);//Retira a palavra "Mensagem" ao que recebeu
                    enviar.println("MENSAGEM " + tipo + ":" + mensagem); // Mensagem a enviar.
                    System.out.println("Mensagem do " + tipo + ":" + mensagem);//Mensagem recebida
                }
            } catch (IOException e) {System.out.println(e);} 
            finally {
                if(enviar != null) {//Para notificar o outro cliente que o seu parceiro se desconectou-se permitindo receber
                    enviar.println("PARCEIROFORA"); //outro cliente como parceiro
                }try{
                    socket.close();
                } catch (IOException e) {}
            }
        }
    }
}