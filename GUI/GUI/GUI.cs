using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using ZedGraph;
using System.Collections;
using System.IO.Ports;
using System.Net.Sockets;
using System.Net;
using System.IO;



namespace GUI
{
    public partial class GUI : Form
    {


        private Hashtable hashtable = new Hashtable();
        private Graph graph1, graph2;

        private TcpListener tcpListener;
        private Thread listenThread;

        volatile private Boolean isAbortThreadRequest = false;

        string[] ports = SerialPort.GetPortNames();
        private List<TextBox> listTextBox = new List<TextBox>();

        private const int faktor_serial = 1000;

        public GUI()
        {
            InitializeComponent();

            foreach (string s in ports) comboBox_Comports.Items.Add(s);
            comboBox_Comports.Items.Add("Socket");

            hashtable.Add("roll", 0);
            hashtable.Add("pitch", 0);
            hashtable.Add("yaw", 0);

            hashtable.Add("pR", 0);
            hashtable.Add("iR", 0);
            hashtable.Add("dR", 0);

            hashtable.Add("pP", 0);
            hashtable.Add("iP", 0);
            hashtable.Add("dP", 0);

            hashtable.Add("pY", 0);
            hashtable.Add("iY", 0);
            hashtable.Add("dY", 0);

            hashtable.Add("pTr", 0);
            hashtable.Add("iTr", 0);
            hashtable.Add("dTr", 0);

            hashtable.Add("pTp", 0);
            hashtable.Add("iTp", 0);
            hashtable.Add("dTp", 0);

            hashtable.Add("fl", 0);
            hashtable.Add("fr", 0);
            hashtable.Add("bl", 0);
            hashtable.Add("br", 0);
            hashtable.Add("e", 0);
            

          if (!serialPort1.IsOpen)
                btn_serialDisconnect.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            graph1 = new Graph(zedGraphControl1, "Graph1", "Time", "", "", "", "");
            graph2 = new Graph(zedGraphControl2, "Graph2", "Time", "", "", "", "");

            gMap.MapProvider = GMap.NET.MapProviders.GoogleMapProvider.Instance;
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerOnly;
            gMap.Position = new GMap.NET.PointLatLng(48.209206, 16.372778);

            timer1.Start();

        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string line;
            try
            {
                line = serialPort1.ReadLine();
                this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
            }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }

        private delegate void LineReceivedEvent(string line);

        private void addValuesTextBox()
        {
            foreach (String s in hashtable.Keys)
            {

                foreach (TextBox t in listTextBox)
                {
                    if (t.Name.ToString().Equals("textBox_" + s))
                        t.Text = hashtable[s].ToString();

                }
            }

            try
            {
                if (Convert.ToInt32(hashtable["bl"]) != 0)
                {
                    progressBar_bl.Value = Convert.ToInt32(hashtable["bl"]);
                    progressBar_br.Value = Convert.ToInt32(hashtable["br"]);
                    progressBar_fl.Value = Convert.ToInt32(hashtable["fl"]);
                    progressBar_fr.Value = Convert.ToInt32(hashtable["fr"]);
                }
            }
            catch (Exception e) { MessageBox.Show(e.Message); }


            textBox_br.Text = hashtable["br"].ToString();
            textBox_bl.Text = hashtable["bl"].ToString();
            textBox_fl.Text = hashtable["fl"].ToString();
            textBox_fr.Text = hashtable["fr"].ToString();

            textBox_pTr.Text = hashtable["pTr"].ToString();
            textBox_iTr.Text = hashtable["iTr"].ToString();
            textBox_dTr.Text = hashtable["dTr"].ToString();

            textBox_e.Text = hashtable["e"].ToString(); //throttle

            textBox_pR.Text = hashtable["pR"].ToString();
            textBox_iR.Text = hashtable["iR"].ToString();
            textBox_dR.Text = hashtable["dR"].ToString();

            textBox_pP.Text = hashtable["pP"].ToString();
            textBox_iP.Text = hashtable["iP"].ToString();
            textBox_dP.Text = hashtable["dP"].ToString();




        }


        private void LineReceived(string line)
        {

            if (!line.Contains("?") && line != "\r" && line != "" && !line.Contains(","))
            {
                textBox_SerialPrint.AppendText(line.ToString());
                textBox_SerialPrint.AppendText(Environment.NewLine);
            }
            else
            {
                string[] dataSplitedGroups = null;
                string[] dataSplitedValues;

                dataSplitedGroups = line.Trim().Split(',');

                foreach (string s in dataSplitedGroups)
                {
                    dataSplitedValues = s.Split('/');
                    if (hashtable.Contains(dataSplitedValues[0]))
                    {
                        double valDouble;
                        try
                        {
                            string number = dataSplitedValues[1];
                            valDouble = double.Parse(number, System.Globalization.CultureInfo.InvariantCulture);
                            hashtable[dataSplitedValues[0]] = valDouble;
                        }
                        catch (Exception e) { MessageBox.Show(e.Message); }

                    }
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Hashtable hashTableGraph1 = new Hashtable();
            Hashtable hashTableGraph2 = new Hashtable();

            foreach (object s in checkedListBox_graph1.CheckedItems)
                hashTableGraph1.Add(s.ToString(), hashtable[s.ToString()]);
            foreach (object s in checkedListBox_graph2.CheckedItems)
                hashTableGraph2.Add(s.ToString(), hashtable[s.ToString()]);

            graph1.drawGraph(hashTableGraph1);
            graph2.drawGraph(hashTableGraph2);

            if (serialPort1.IsOpen)
            {
                lb_connectionStatus.Text = "Connected";
                btn_serialDisconnect.Enabled = true;
                btn_ConnectSerial.Enabled = false;
                addValuesTextBox();

                attitudeIndicatorInstrumentControl1.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));
                attitudeIndicatorInstrumentControl2.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));

                headingIndicatorInstrumentControl1.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
                headingIndicatorInstrumentControl2.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);

            }
        }

        private void btn_ConnectSerial_Click(object sender, EventArgs e)
        {
            textBox_SerialPrint.Clear();
            String comPort = Convert.ToString(comboBox_Comports.SelectedItem);
            switch (comPort)
            {
                case "Socket":
                    {
                        this.tcpListener = new TcpListener(IPAddress.Any, 6000);
                        this.listenThread = new Thread(new ThreadStart(ListenForClients));
                        this.listenThread.Start();
                        if (this.listenThread.IsAlive)
                        {
                            btn_ConnectSerial.Enabled = false;
                            btn_serialDisconnect.Enabled = true;
                        }
                        break;
                    }
                default:
                    {
                        try
                        {
                            if (!serialPort1.IsOpen)
                            {
                                serialPort1.DtrEnable = true;
                                serialPort1.PortName = comPort;
                                serialPort1.Open();
                                serialPort1.DataReceived += serialPort1_DataReceived;
                            }
                        }
                        catch (Exception ex) { MessageBox.Show("Unable to connect: " + ex.Message); }

                        break;
                    }
            }
        }

        
        volatile NetworkStream clientStream;
        private void HandleClientComm(object client)
        {
            TcpClient tcpClient = (TcpClient)client;
            this.clientStream = tcpClient.GetStream();

            byte[] message = new byte[4096];
            int bytesRead;

            while (true)
            {
                if (isAbortThreadRequest) break;

                bytesRead = 0;

                try
                {
                    //blocks until a client sends a message
                    bytesRead = clientStream.Read(message, 0, 4096);
                }
                catch
                {
                    //a socket error has occured
                    break;
                }

                if (bytesRead == 0)
                {
                    //the client has disconnected from the server
                    break;
                }

                //message has successfully been received
                ASCIIEncoding encoder = new ASCIIEncoding();
                // Console.WriteLine(encoder.GetString(message, 0, bytesRead));
                try
                {
                    if (InvokeRequired)
                    {
                        this.Invoke(new Action(() => LineReceived(encoder.GetString(message, 0, bytesRead))));

                    }
                    if (textBox_socketRead.InvokeRequired)
                        textBox_socketRead.Invoke((MethodInvoker)delegate
                        {
                            textBox_socketRead.AppendText(encoder.GetString(message, 0, bytesRead));
                            textBox_socketRead.AppendText(Environment.NewLine);
                        });
                    else
                    {
                        textBox_socketRead.AppendText(encoder.GetString(message, 0, bytesRead));
                        textBox_socketRead.AppendText(Environment.NewLine);
                    }
                }
                catch (Exception e)
                {

                    MessageBox.Show(e.Message);
                }
            }

            tcpClient.Close();
        }

        private void ListenForClients()
        {
            this.tcpListener.Start();
            Console.WriteLine("tcplistener started");
            while (true)
            {
                //blocks until a client has connected to the server
                TcpClient client = this.tcpListener.AcceptTcpClient();
               // Console.WriteLine("tcplistener connected");
                if (lb_connectionStatus.InvokeRequired) lb_connectionStatus.Invoke((MethodInvoker)delegate
                    {
                        lb_connectionStatus.Text = "Connected";
                    }
                     );
                else{
                    lb_connectionStatus.Text = "Connected";
                }

                //create a thread to handle communication 
                //with connected client
                Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
                clientThread.Start(client);
                if (isAbortThreadRequest) break;
            }
        }

        private void btn_serialDisconnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();

            if (listenThread.IsAlive)
            {
                this.tcpListener = null;
                isAbortThreadRequest = true;
                btn_ConnectSerial.Enabled = true;
                btn_serialDisconnect.Enabled = false;
                lb_connectionStatus.Text = "Disconnected";
            }

            if (!serialPort1.IsOpen && !listenThread.IsAlive)
            {
                btn_ConnectSerial.Enabled = true;
                btn_serialDisconnect.Enabled = false;
                lb_connectionStatus.Text = "Disconnected";
            }
        }

        private void comboBoxComports_Click(object sender, EventArgs e)
        {
            comboBox_Comports.Items.Clear();
            ports = null;
            ports = SerialPort.GetPortNames();
            foreach (string s in ports) comboBox_Comports.Items.Add(s);
            comboBox_Comports.Items.Add("Socket");
        }

        private void sendStringSerial(SerialPort serialPort, string str)
        {
            if (serialPort.IsOpen)
                serialPort.WriteLine(str.ToString());
        }

        private void sendStringSocket(String str)
        {
            if (listenThread.IsAlive)
            {
                byte[] msgBuffer = Encoding.ASCII.GetBytes(str);
                this.clientStream.Write(msgBuffer, 0, msgBuffer.Length);
            }

        }

        private void sendOverStreamCommand(string str,string value )
        {
            string dataSend = "";
            dataSend += str + (Convert.ToDouble(value) * faktor_serial).ToString();
            Console.WriteLine(dataSend);

            if (checkBox_sendSocket.Checked)
                sendStringSocket(dataSend);
            if (checkBox_sendDataToArduino.Checked)
                sendStringSerial(serialPort1, dataSend);
        }

        private void numericUpDown_pR_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("P",numericUpDown_pR.Value.ToString());
        }

        private void numericUpDown_iR_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("I",numericUpDown_iR.Value.ToString());
        }

        private void numericUpDown_dR_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("D",numericUpDown_dR.Value.ToString());
        }

        private void trackBar_throttle_Scroll(object sender, EventArgs e)
        {
            sendOverStreamCommand("E",trackBar_throttle.Value.ToString());
        }

        private void numericUpDown_pPitch_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("Q",numericUpDown_pPitch.Value.ToString());
        }

        private void numericUpDown_iPitch_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("R",numericUpDown_iPitch.Value.ToString());
        }

        private void numericUpDown_dPitch_ValueChanged(object sender, EventArgs e)
        {
            sendOverStreamCommand("W",numericUpDown_dPitch.Value.ToString()); 
        }


        private void btn_up_Click(object sender, EventArgs e)
        {
            sendOverStreamCommand("U", numericUpDown_stearingRatio.Value.ToString());
        }

        private void btn_left_Click(object sender, EventArgs e)
        {
            sendOverStreamCommand("L", numericUpDown_stearingRatio.Value.ToString());

        }

        private void brn_down_Click(object sender, EventArgs e)
        {
            sendOverStreamCommand("N", numericUpDown_stearingRatio.Value.ToString());

        }

        private void btn_right_Click(object sender, EventArgs e)
        {
            sendOverStreamCommand("G", numericUpDown_stearingRatio.Value.ToString());

        }

        private void button_clearSerial_Click(object sender, EventArgs e)
        {
            textBox_SerialPrint.Clear();
            textBox_socketRead.Clear();
        }


        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();
            if(listenThread != null)
            if (listenThread.IsAlive)
            {
                this.tcpListener = null;
                isAbortThreadRequest = true;
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Left)
            {
                Console.WriteLine("You pressed Left arrow key");
                sendOverStreamCommand("L", numericUpDown_stearingRatio.Value.ToString());
                return true;
            }
            if (keyData == Keys.Right)
            {
                Console.WriteLine("You pressed Right arrow key");
                sendOverStreamCommand("G", numericUpDown_stearingRatio.Value.ToString());

                return true;
            }
            if (keyData == Keys.Up)
            {
                Console.WriteLine("You pressed Up arrow key");
                sendOverStreamCommand("U", "5");
                return true;
            }
            if (keyData == Keys.Down)
            {
                Console.WriteLine("You pressed Down arrow key");
                sendOverStreamCommand("N", numericUpDown_stearingRatio.Value.ToString());

                return true;
            }
            if (keyData == Keys.Q)
            {
                Console.WriteLine("You pressed Q key");
                trackBar_throttle.Value += 5;
                sendOverStreamCommand("N", trackBar_throttle.Value.ToString());

                return true;
            }
            if (keyData == Keys.A)
            {
                Console.WriteLine("You pressed A key");
                trackBar_throttle.Value -= 5;
                sendOverStreamCommand("A", trackBar_throttle.Value.ToString());

                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

      





      
    }
}
