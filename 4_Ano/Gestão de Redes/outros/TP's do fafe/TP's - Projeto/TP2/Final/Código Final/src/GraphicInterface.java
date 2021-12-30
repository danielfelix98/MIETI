import org.knowm.xchart.QuickChart;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;
import org.knowm.xchart.XYSeries;
import org.knowm.xchart.XYSeries.XYSeriesRenderStyle;
import org.knowm.xchart.demo.charts.ExampleChart;
import org.knowm.xchart.style.Styler;
import org.knowm.xchart.style.Styler.LegendPosition;
import org.knowm.xchart.style.markers.SeriesMarkers;

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
import java.util.Objects;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;

public class GraphicInterface extends JFrame {

    private Snmp snmp = null;
    private String address = null;
    private String addressAux = null;
    private JFrame frame; //for the frame
    private java.util.Timer timer;
    private boolean aux = false;
    private JTextArea textArea_2;
    private  double[]initdata = new double[50];
    private double[]initdata2 = new double[50];
    private double[]xOutOctets = new double[50];
    private double[]yOutOctets = new double[50];
    private XYChart chart;
    private SwingWrapper<XYChart> sw;

    GraphicInterface() {
        initialize();
    }

    private void initialize() {

        //FRAME
        frame = new JFrame();
        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE); //to close
        frame.setTitle("Gestão de Redes - TP2");
        frame.getContentPane().setLayout(null);
        frame.getContentPane().setBackground(Color.getColor("#FFFFF"));
        frame.setBounds(500, 200, 300, 250);    //x,y,width,height
        frame.setVisible(true);

        //UP
        JLabel label_1 = new JLabel("IP Address/Port");
        label_1.setBounds(20, 20, 150, 20);
        frame.getContentPane().add(label_1);
        frame.validate();

        JScrollPane scrollPane1 = new JScrollPane();
        scrollPane1.setBounds(20, 50, 250, 20);
        frame.getContentPane().add(scrollPane1);
        frame.validate();
        JTextArea textArea_1 = new JTextArea();
        textArea_1.setText(null);
        textArea_1.setEditable(true);
        scrollPane1.setViewportView(textArea_1);
        frame.validate();

        JButton confirm = new JButton();
        confirm.setBounds(20, 80, 250, 20);
        confirm.setText("OK");
        confirm.setEnabled(true);
        frame.getContentPane().add(confirm);
        frame.validate();
        frame.repaint();

        JButton stop = new JButton();
        stop.setBounds(20, 150, 250, 20);
        stop.setText("STOP");
        stop.setEnabled(false);
        frame.getContentPane().add(stop);
        frame.validate();
        frame.repaint();

        //CENTER
        JButton exit = new JButton();
        exit.setBounds(20, 200, 250, 20);
        exit.setText("EXIT");
        exit.setEnabled(true);
        frame.getContentPane().add(exit);
        frame.validate();
        frame.repaint();

        stop.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                timer.cancel();
                textArea_1.setEnabled(true);
                confirm.setEnabled(true);
                stop.setEnabled(false);
            }
        });


        exit.addActionListener(new ActionListener() { // Quando cliclar em EXIT termina o programa
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        confirm.addActionListener(new ActionListener() { //Quando clicar no OK executa isto.
            @Override
            public void actionPerformed(ActionEvent e) {
                stop.setEnabled(true);
                String ip = textArea_1.getText(); //127.0.0.1/5555 para testar
                textArea_1.setEnabled(false);
                confirm.setEnabled(false);
                System.out.println(ip);
                final String ifInOctets = ".1.3.6.1.2.1.2.2.1.10.3";
                final String ifOutOctets = ".1.3.6.1.2.1.2.2.1.16.3";

                if(!aux) {
                    frame = new JFrame();
                    frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE); //to close
                    frame.setTitle("Display Data");
                    frame.getContentPane().setLayout(null);
                    frame.getContentPane().setBackground(Color.getColor("#FFFFF"));
                    frame.setBounds(500, 100, 300, 450);    //x,y,width,height
                    frame.setVisible(true);

                    JLabel jLabel = new JLabel("ifInOctets | ifOutOctets");
                    jLabel.setBounds(60, 10, 260, 20);
                    frame.getContentPane().add(jLabel);
                    frame.validate();

                    JScrollPane scrollPane2 = new JScrollPane();
                    scrollPane2.setBounds(20, 30, 260, 400);
                    frame.getContentPane().add(scrollPane2);
                    frame.validate();
                    textArea_2 = new JTextArea();
                    textArea_2.setText(null);
                    textArea_2.setEditable(false);
                    scrollPane2.setViewportView(textArea_2);
                    frame.validate();
                    frame.repaint();

                    initdata[0] = 0;
                    initdata2[0] = 0;
                    xOutOctets[0] = 0;
                    yOutOctets[0] = 0;

                    chart = QuickChart.getChart("IP Monitoring", "Time(ms)", "Bytes", "ifInOctects",initdata, initdata2);
                    XYSeries outOc = chart.addSeries("ifOutOctects", xOutOctets, yOutOctets);
                    outOc.setMarker(SeriesMarkers.NONE);
                    sw = new SwingWrapper<>(chart);
                    sw.displayChart();

                    aux = true;
                }

                address = "udp:" + ip;
                if(!Objects.equals(address, addressAux)){
                    addressAux = address;
                    textArea_2.setText(null);
                }

                int delay = 1000;
                int interval = 1000;
                long start = System.currentTimeMillis();
                timer = new java.util.Timer();
                timer.scheduleAtFixedRate(new TimerTask() {
                    @Override
                    public void run() {
                        try {
                            int i = 0;
                            start();
                            String sIn = getAsString(new OID(ifInOctets));
                            String sOut = getAsString(new OID(ifOutOctets));
                            int in, out;
                            if (!sIn.equals("noSuchInstance") && !sOut.equals("noSuchInstance")) {

                                System.out.println("ifInOctets: " + sIn + " | ifOutOctets: " + sOut + "\n");
                                textArea_2.append("               " + sIn + " | " + sOut + "\n");

                                in = Integer.parseInt(sIn);
                                out = Integer.parseInt(sOut);
                                long duration = System.currentTimeMillis() - start;
                                initdata[i] = (double)in;
                                initdata2[i] = (double)duration;
                                yOutOctets[i] = (double)out;
                                xOutOctets[i] = (double)duration;
                                chart.updateXYSeries("ifInOctects", initdata2, initdata, null);
                                chart.updateXYSeries("ifOutOctects",xOutOctets, yOutOctets, null);
                                sw.repaintChart();

                            } else
                                System.out.print("noSuchInstance");
                        } catch (IOException ex) {
                            Logger.getLogger(MainProject.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }, delay, interval);
            }

            // Inicia a sessão snmp.
            private void start() throws IOException {
                TransportMapping transport = new DefaultUdpTransportMapping();
                snmp = new Snmp(transport);
                transport.listen();
            }

            //Recebe um OID e retorna a resposta do agente como uma String
            private String getAsString(OID oid) throws IOException {
                PDU pdu = new PDU();
                pdu.add(new VariableBinding(oid));
                pdu.setType(PDU.GET);
                ResponseEvent event = snmp.send(pdu, getTarget(), null);
                if (event != null) {
                    return event.getResponse().get(0).getVariable().toString();
                }
                throw new RuntimeException("NULL");
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

