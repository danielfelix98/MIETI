import org.snmp4j.*;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.*;
import org.snmp4j.transport.DefaultUdpTransportMapping;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Scanner;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Created by jorge on 11-02-2016.
 */

public class GUI extends JFrame {

    private Snmp snmp = null;
    private String address = null;
    private JFrame frame; //for the frame


    public GUI() {

        initialize();

    }

    private void initialize() {

        //FRAME
        frame = new JFrame();
        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE); //to close
        frame.setTitle("Gestão de Redes - TP2");
        frame.getContentPane().setLayout(null);
        frame.getContentPane().setBackground(Color.getColor("#FFFFF"));
        frame.setBounds(500, 100, 270, 410);    //x,y,width,height
        frame.setVisible(true);


        //UP
        JLabel label_1 = new JLabel(" valid IP address/port:");
        label_1.setBounds(20, 20, 150, 20);
        frame.getContentPane().add(label_1);
        frame.validate();

        JScrollPane scrollPane1 = new JScrollPane();
        scrollPane1.setBounds(20, 50, 150, 20);
        frame.getContentPane().add(scrollPane1);
        frame.validate();
        JTextArea textArea_1 = new JTextArea();
        textArea_1.setText(null);
        textArea_1.setEditable(true);
        scrollPane1.setViewportView(textArea_1);
        frame.validate();

        JButton confirm = new JButton();
        confirm.setBounds(190, 50, 60, 20);
        confirm.setText("OK");
        confirm.setEnabled(true);
        frame.getContentPane().add(confirm);
        frame.validate();

        frame.repaint();

        //CENTER
        JLabel label_2 = new JLabel("ipInReceives :");
        label_2.setBounds(20, 100, 230, 20);
        frame.getContentPane().add(label_2);
        frame.validate();

        JScrollPane scrollPane2 = new JScrollPane();
        scrollPane2.setBounds(20, 130, 230, 20);
        frame.getContentPane().add(scrollPane2);
        frame.validate();
        JTextArea textArea_2 = new JTextArea();
        textArea_2.setText(null);
        textArea_2.setEditable(false);
        scrollPane2.setViewportView(textArea_2);
        frame.validate();
        frame.repaint();

        JLabel label_3 = new JLabel("ipOutRequests :");
        label_3.setBounds(20, 170, 230, 20);
        frame.getContentPane().add(label_3);
        frame.validate();

        JScrollPane scrollPane3 = new JScrollPane();
        scrollPane3.setBounds(20, 200, 230, 20);
        frame.getContentPane().add(scrollPane3);
        frame.validate();
        JTextArea textArea_3 = new JTextArea();
        textArea_3.setText(null);
        textArea_3.setEditable(false);
        scrollPane3.setViewportView(textArea_3);
        frame.validate();
        frame.repaint();
        //
        JLabel label_4 = new JLabel("ipForwDatagrams :");
        label_4.setBounds(20, 240, 230, 20);
        frame.getContentPane().add(label_4);
        frame.validate();

        JScrollPane scrollPane4 = new JScrollPane();
        scrollPane4.setBounds(20, 270, 230, 20);
        frame.getContentPane().add(scrollPane4);
        frame.validate();
        JTextArea textArea_4 = new JTextArea();
        textArea_4.setText(null);
        textArea_4.setEditable(false);
        scrollPane4.setViewportView(textArea_4);
        frame.validate();
        frame.repaint();
        //DOWN

        JLabel label_5 = new JLabel("TOTAL :");
        label_5.setBounds(20, 310, 230, 20);
        frame.getContentPane().add(label_5);
        frame.validate();

        JScrollPane scrollPane5 = new JScrollPane();
        scrollPane5.setBounds(20, 340, 230, 20);
        frame.getContentPane().add(scrollPane5);
        frame.validate();
        JTextArea textArea_5 = new JTextArea();
        textArea_5.setText(null);
        textArea_5.setEditable(false);
        scrollPane5.setViewportView(textArea_5);
        frame.validate();
        frame.repaint();

        confirm.addActionListener(new ActionListener() { //Quando confirmar o ip, faz o resto.
            @Override
            public void actionPerformed(ActionEvent e) {
                String ip = textArea_1.getText();
                //127.0.0.1/161 para testes
                textArea_1.setEnabled(false);
                confirm.setEnabled(false);
                System.out.println(ip);

                final String ipInReceives = ".1.3.6.1.2.1.4.3.0";
                final String ipOutRequests = ".1.3.6.1.2.1.4.10.0";
                final String ipForwDatagrams = ".1.3.6.1.2.1.4.6.0";


                address = "udp:" + ip;

                int delay = 1000;
                int interval = 1000;
                java.util.Timer timer = new java.util.Timer();

                timer.scheduleAtFixedRate(new TimerTask() {
                    @Override
                    public void run() {

                        try {
                            start();
                            String sIn = getAsString(new OID(ipInReceives));
                            String sOut = getAsString(new OID(ipOutRequests));
                            String sForw = getAsString(new OID(ipForwDatagrams));
                            int in, out, forw;
                            if (!sIn.equals("noSuchInstance") && !sForw.equals("noSuchInstance") && !sOut.equals("noSuchInstance")) {
                                in = Integer.parseInt(sIn);
                                forw = Integer.parseInt(sForw);
                                out = Integer.parseInt(sOut);
                                int total = forw + out;
                                String sTotal = "" + total;
                                System.out.println("| ipInReceives: " + in + "\t| ipOutRequests: " + out + "\t| ipForwDatagrams: " + forw + "\t| total: " + total + " |");

                            } else
                                System.out.print("noSuchInstance");


                        } catch (IOException ex) {
                            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }, delay, interval);

                Scanner scanner = new Scanner(System.in);
                while (true) {
                    if (scanner.hasNext())
                        if (scanner.next().equals("s"))
                            timer.cancel();
                    break;
                }
            }

            // Inicia a sessão snmp.
            private void start() throws IOException {
                TransportMapping transport = new DefaultUdpTransportMapping();
                snmp = new Snmp(transport);
                transport.listen();
            }
            //Recebe um OID e retorna a resposta do agente como uma String
            public String getAsString(OID oid) throws IOException {
                PDU pdu = new PDU();
                pdu.add(new VariableBinding(oid));
                pdu.setType(PDU.GET);
                ResponseEvent event = snmp.send(pdu, getTarget(), null);
                if (event != null) {
                    return event.getResponse().get(0).getVariable().toString();
                }
                throw new RuntimeException("Got null");
            }

            //This method returns a Target, which contains information about  where the data should be fetched and how.
            private Target getTarget() {
                Address targetAddress = GenericAddress.parse(address);
                CommunityTarget target = new CommunityTarget();
                target.setCommunity(new OctetString("public"));
                target.setAddress(targetAddress);
                target.setRetries(2);
                target.setTimeout(1500);
                target.setVersion(SnmpConstants.version2c);
                return target;
            }

        });
    }
}