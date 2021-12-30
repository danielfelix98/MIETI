package client;

import java.awt.event.ActionEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public final class Cliente_user_genious {

    BufferedReader input;
    PrintWriter output;
    JFrame frame = new JFrame("Chat User-Genious");
    JTextField textField = new JTextField(30);
    JTextArea messageArea = new JTextArea(15,30);

    public Cliente_user_genious() {
        layout();
        enviarMensagem();
    }
    
    public void enviarMensagem(){
        textField.addActionListener((ActionEvent e) -> {
            output.println("MENSAGEM " + textField.getText());
            messageArea.append("Eu: " + textField.getText() + "\n");
            textField.setText("");
        });
    }
    
    public void layout() {
        textField.setEditable(false);
        messageArea.setEditable(false);
        frame.getContentPane().add(textField, "South");
        frame.getContentPane().add(new JScrollPane(messageArea), "North");
        frame.pack();
    }
    
    public String getNome() {return JOptionPane.showInputDialog(frame,"Introduza o seu tipo:","Selecionar o tipo de utilizador",JOptionPane.PLAIN_MESSAGE);}

    public void run() throws IOException {

        Socket socket = new Socket("localhost", 9999);
        input = new BufferedReader(new InputStreamReader(socket.getInputStream()));//Para ler
        output = new PrintWriter(socket.getOutputStream(), true);//Para escrever

        while (true) {
            String mensagem = input.readLine();
            if (mensagem.startsWith("DIGITENOME")) {//Posso intrudozir o meu tipo
                String nome = getNome();
                frame.setTitle(nome);
                output.println(nome);
            } else if (mensagem.startsWith("NOMEACEITE")) {//O meu nome foi aceite
                textField.setEditable(true);
            } else if (mensagem.startsWith("PARCEIROCONECTADO")) {//Já tem parceiro
                textField.setEditable(true);
            } else if (mensagem.startsWith("PARCEIROFORA")) {//O parceiro desconectou-se
                textField.setEditable(false);
                messageArea.append("ATENÇÃO!! O meu parceiro desconectou-se");
            } else if (mensagem.startsWith("MENSAGEM")) {
                messageArea.append(mensagem.substring(8) + "\n");
            }
        }
    }
    
    public static void main(String[] args) throws Exception {
        Cliente_user_genious client = new Cliente_user_genious();
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.setVisible(true);
        client.run();
    }
}