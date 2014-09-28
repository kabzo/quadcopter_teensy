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
using System.Windows.Input;



namespace GUI {
  public partial class GUI : Form {
    private Hashtable hashtable = new Hashtable();

    private Graph graph1, graph2;

    /********************************SOCKET COMMUNICATION********************************/
    private TcpListener tcpListener;
    private Thread listenThread;
    volatile NetworkStream clientStream;
    volatile private Boolean isAbortThreadRequest = false;
    /********************************SOCKET COMMUNICATION********************************/

    private const int faktor_serial = 100;
    private int firstTimeSet = 0;
    int x_pos;
    int y_pos;
    int roll; int pitch;


    public GUI() {
      InitializeComponent();

      x_pos = panel1.Width / 2;
      y_pos = panel1.Height / 2;

      string[] ports = SerialPort.GetPortNames();
      foreach (string s in ports) comboBox_Comports.Items.Add(s);
      comboBox_Comports.Items.Add("Socket");

      /********************************PID ROLL********************************/
      hashtable.Add("pR", 0);
      hashtable.Add("iR", 0);
      hashtable.Add("dR", 0);
      hashtable.Add("limR", 0);
      hashtable.Add("timeR", 0);

      hashtable.Add("pTr", 0);
      hashtable.Add("iTr", 0);
      hashtable.Add("dTr", 0);
      /********************************PID ROLL********************************/

      /********************************PID PITCH********************************/
      hashtable.Add("pP", 0);
      hashtable.Add("iP", 0);
      hashtable.Add("dP", 0);
      hashtable.Add("limP", 0);
      hashtable.Add("timeP", 0);

      hashtable.Add("pTp", 0);
      hashtable.Add("iTp", 0);
      hashtable.Add("dTp", 0);
      /********************************PID PITCH********************************/

      /********************************PID YAW********************************/
      hashtable.Add("pY", 0);
      hashtable.Add("iY", 0);
      hashtable.Add("dY", 0);
      /********************************PID YAW********************************/

      /********************************FLIGHT CONTROLL********************************/
      hashtable.Add("roll", 0);
      hashtable.Add("pitch", 0);
      hashtable.Add("yaw", 0);

      hashtable.Add("fl", 900); //motors names
      hashtable.Add("fr", 900);
      hashtable.Add("bl", 900);
      hashtable.Add("br", 900);

      hashtable.Add("setR", 0);
      hashtable.Add("setP", 0);
      hashtable.Add("setY", 0);

      hashtable.Add("e", 0);  //throttle
      /********************************FLIGHT CONTROLL********************************/
    }

    private void Form1_Load(object sender, EventArgs e) {
      graph1 = new Graph(zedGraphControl1, "Graph1", "Time", "", "", "", "");
      graph2 = new Graph(zedGraphControl2, "Graph2", "Time", "", "", "", "");

      gMap.MapProvider = GMap.NET.MapProviders.GoogleMapProvider.Instance;
      GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerOnly;
      gMap.Position = new GMap.NET.PointLatLng(48.209206, 16.372778);

      timer1.Start();
    }

    private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e) {
      string line;
      try {
        line = serialPort1.ReadLine();
        this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
      } catch (Exception ex) { MessageBox.Show("Serialport readline: " + ex.Message); }
    }

    private delegate void LineReceivedEvent(string line);

    private void addValuesTextBox() {
      try {
        if (Convert.ToInt32(hashtable["bl"]) != 0) {
          progressBar_bl.Value = Convert.ToInt32(hashtable["bl"]);
          progressBar_br.Value = Convert.ToInt32(hashtable["br"]);
          progressBar_fl.Value = Convert.ToInt32(hashtable["fl"]);
          progressBar_fr.Value = Convert.ToInt32(hashtable["fr"]);
        }
      } catch (Exception e) { MessageBox.Show("Progressbar" + e.Message); }


      textBox_br.Text = hashtable["br"].ToString();
      textBox_bl.Text = hashtable["bl"].ToString();
      textBox_fl.Text = hashtable["fl"].ToString();
      textBox_fr.Text = hashtable["fr"].ToString();

      textBox_throttle.Text = hashtable["e"].ToString(); //throttle

      textBox_rollPid_kp.Text = hashtable["pR"].ToString();
      textBox_rollPid_ki.Text = hashtable["iR"].ToString();
      textBox_rollPid_kd.Text = hashtable["dR"].ToString();
      textBox_rollPid_limits.Text = hashtable["limR"].ToString();
      textBox_rollPid_time.Text = hashtable["timeR"].ToString();

      textBox_pitchPid_kp.Text = hashtable["pP"].ToString();
      textBox_pitchPid_ki.Text = hashtable["iP"].ToString();
      textBox_pitchPid_kd.Text = hashtable["dP"].ToString();
      textBox_pitchPid_limits.Text = hashtable["limP"].ToString();
      textBox_pitchPid_time.Text = hashtable["timeP"].ToString();

      textBox_setpointPitch.Text = hashtable["setP"].ToString();
      textBox_setpointRoll.Text = hashtable["setR"].ToString();

      if (firstTimeSet < 30) {
        numericUpDown_pitchPid_kp.Value = Convert.ToDecimal(hashtable["pP"]);
        numericUpDown_pitchPid_ki.Value = Convert.ToDecimal(hashtable["iP"]);
        numericUpDown_pitchPid_kd.Value = Convert.ToDecimal(hashtable["dP"]);
        numericUpDown_pitchPid_limits.Value = Convert.ToDecimal(hashtable["limP"]);
        numericUpDown_pitchPid_time.Value = Convert.ToDecimal(hashtable["timeP"]);

        numericUpDown_rollPid_kp.Value = Convert.ToDecimal(hashtable["pR"]);
        numericUpDown_rollPid_ki.Value = Convert.ToDecimal(hashtable["iR"]);
        numericUpDown_rollPid_kd.Value = Convert.ToDecimal(hashtable["dR"]);
        numericUpDown_rollPid_limits.Value = Convert.ToDecimal(hashtable["limR"]);
        numericUpDown_rollPid_time.Value = Convert.ToDecimal(hashtable["timeR"]);
        firstTimeSet++;

      }

    }

    private void LineReceived(string line) {

      if (!line.Contains("?") && line != "\r" && line != "" && !line.Contains(",")) {
        if (serialPort1.IsOpen) {
          textBox_serialRead.AppendText(line.ToString());
          textBox_serialRead.AppendText(Environment.NewLine);
        }
        if (listenThread != null)
          if (listenThread.IsAlive) {
            textBox_socketRead.AppendText(line.ToString());
            textBox_socketRead.AppendText(Environment.NewLine);
          }

      } else {
        string[] dataSplitedGroups = null;
        string[] dataSplitedValues;

        dataSplitedGroups = line.Trim().Split(',');

        foreach (string s in dataSplitedGroups) {
          dataSplitedValues = s.Split('/');
          if (hashtable.Contains(dataSplitedValues[0])) {
            double valDouble;
            try {
              string number = dataSplitedValues[1];
              valDouble = double.Parse(number, System.Globalization.CultureInfo.InvariantCulture);
              hashtable[dataSplitedValues[0]] = valDouble;
            } catch (Exception e) { MessageBox.Show("Splitter: " + e.Message); }

          }
        }
      }
      addValuesTextBox();
      actualizate_Parameters();

    }

    private void timer1_Tick(object sender, EventArgs e) {
      //Hashtable hashTableGraph1 = new Hashtable();
      //Hashtable hashTableGraph2 = new Hashtable();

      //foreach (object s in checkedListBox_graph1.CheckedItems)
      //    hashTableGraph1.Add(s.ToString(), hashtable[s.ToString()]);
      //foreach (object s in checkedListBox_graph2.CheckedItems)
      //    hashTableGraph2.Add(s.ToString(), hashtable[s.ToString()]);

      //graph1.drawGraph(hashTableGraph1);
      //graph2.drawGraph(hashTableGraph2);



      //// attitudeIndicatorInstrumentControl1.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));
      //attitudeIndicatorInstrumentControl2.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["roll"]), Convert.ToDouble(hashtable["pitch"]));

      //// headingIndicatorInstrumentControl1.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
      //headingIndicatorInstrumentControl2.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);


    }

    private void actualizate_Parameters() {
      Hashtable hashTableGraph1 = new Hashtable();
      Hashtable hashTableGraph2 = new Hashtable();

      foreach (object s in checkedListBox_graph1.CheckedItems)
        hashTableGraph1.Add(s.ToString(), hashtable[s.ToString()]);
      foreach (object s in checkedListBox_graph2.CheckedItems)
        hashTableGraph2.Add(s.ToString(), hashtable[s.ToString()]);

      graph1.drawGraph(hashTableGraph1);
      graph2.drawGraph(hashTableGraph2);



      // attitudeIndicatorInstrumentControl1.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));
      attitudeIndicatorInstrumentControl2.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["roll"]), Convert.ToDouble(hashtable["pitch"]));

      // headingIndicatorInstrumentControl1.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
      headingIndicatorInstrumentControl2.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
    }

    private void btn_connect_Click(object sender, EventArgs e) {
      textBox_serialRead.Clear();
      textBox_socketRead.Clear();
      String comPort = Convert.ToString(comboBox_Comports.SelectedItem);
      switch (comPort) {
        case "Socket": {
          this.tcpListener = new TcpListener(IPAddress.Any, 6000);
          this.listenThread = new Thread(new ThreadStart(ListenForClients));
          this.listenThread.Start();
          if (this.listenThread.IsAlive) {
            btn_connect.Enabled = false;
            btn_disconnect.Enabled = true;
          }
          break;
        }
        default: {
          try {
            if (!serialPort1.IsOpen) {
              serialPort1.DtrEnable = true;
              serialPort1.PortName = comPort;
              serialPort1.Open();
              serialPort1.DataReceived += serialPort1_DataReceived;
            }
            if (serialPort1.IsOpen) {
              lb_connectionStatus.Text = "Connected";
              btn_disconnect.Enabled = true;
              btn_connect.Enabled = false;
            }
          } catch (Exception ex) { MessageBox.Show("Unable to connect: " + ex.Message); }

          break;
        }
      }
    }

    private void btn_disconnect_Click(object sender, EventArgs e) {
      if (serialPort1.IsOpen) serialPort1.Close();
      if (listenThread != null) {
        if (listenThread.IsAlive) {
          isAbortThreadRequest = true;
          btn_connect.Enabled = true;
          btn_disconnect.Enabled = false;
          lb_connectionStatus.Text = "Disconnected";
        }

        if (!serialPort1.IsOpen && !listenThread.IsAlive) {
          btn_connect.Enabled = true;
          btn_disconnect.Enabled = false;
          lb_connectionStatus.Text = "Disconnected";
        }
      } else {
        if (!serialPort1.IsOpen) {
          btn_connect.Enabled = true;
          btn_disconnect.Enabled = false;
          lb_connectionStatus.Text = "Disconnected";
        }
      }
    }

    private void HandleClientComm(object client) {
      TcpClient tcpClient = (TcpClient)client;
      this.clientStream = tcpClient.GetStream();

      byte[] message = new byte[4096];
      int bytesRead;

      while (true) {
        if (isAbortThreadRequest) {
          tcpClient.Close();
          this.clientStream.Close();
          break;
        }
        bytesRead = 0;

        try {
          //blocks until a client sends a message
          bytesRead = clientStream.Read(message, 0, 4096);
        } catch {
          //a socket error has occured
          break;
        }

        if (bytesRead == 0) {
          //the client has disconnected from the server
          break;
        }

        //message has successfully been received
        ASCIIEncoding encoder = new ASCIIEncoding();
        // Console.WriteLine(encoder.GetString(message, 0, bytesRead));
        try {
          string line = encoder.GetString(message, 0, bytesRead);
          if (InvokeRequired) {
            this.Invoke(new Action(() => LineReceived(line)));

          }
          //if (textBox_socketRead.InvokeRequired)
          //    textBox_socketRead.Invoke((MethodInvoker)delegate
          //    {
          //        textBox_socketRead.AppendText(encoder.GetString(message, 0, bytesRead));
          //        textBox_socketRead.AppendText(Environment.NewLine);
          //    });
          //else
          //{
          //    textBox_socketRead.AppendText(encoder.GetString(message, 0, bytesRead));
          //    textBox_socketRead.AppendText(Environment.NewLine);
          //}
          //LineReceived(line)
        } catch (Exception e) {

          MessageBox.Show("Socket line received:" + e.Message);
        }
      }

      tcpClient.Close();
    }

    private void ListenForClients() {
      this.tcpListener.Start();
      //  Console.WriteLine("tcplistener started");
      while (true) {
        //blocks until a client has connected to the server
        TcpClient client = this.tcpListener.AcceptTcpClient();
        // Console.WriteLine("tcplistener connected");
        if (lb_connectionStatus.InvokeRequired) lb_connectionStatus.Invoke((MethodInvoker)delegate {
            lb_connectionStatus.Text = "Connected";
          }
             );
        else {
          lb_connectionStatus.Text = "Connected";
        }

        //create a thread to handle communication 
        //with connected client
        Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
        clientThread.Start(client);
        if (isAbortThreadRequest) {
          this.tcpListener.Stop();
          clientThread.Abort();
          client.Close();
          break;
        }        
      }
    }

    private void comboBoxComports_Click(object sender, EventArgs e) {
      comboBox_Comports.Items.Clear();
      string[] ports = null;
      ports = SerialPort.GetPortNames();
      foreach (string s in ports) comboBox_Comports.Items.Add(s);
      comboBox_Comports.Items.Add("Socket");
    }

    private void sendStringSerial(SerialPort serialPort, string str) {

      if (serialPort.IsOpen)
        serialPort.WriteLine(str.ToString());
      textBox_sendingStream1.Text = str;
      textBox_sendingStream2.Text = str;
    }

    private void sendStringSocket(String str) {
      try {
        if (listenThread.IsAlive) {
          byte[] msgBuffer = Encoding.ASCII.GetBytes(str);
          this.clientStream.Write(msgBuffer, 0, msgBuffer.Length);
        }
        textBox_sendingStream1.Text = str;
        textBox_sendingStream2.Text = str;
      } catch (Exception e) {

        MessageBox.Show("Socket sending message:" + e.Message);
      }
    }

    private void sendOverStreamCommand(string str, string value) {
      string dataSend = "";
      dataSend += str + (Convert.ToDouble(value) * faktor_serial).ToString();
      // Console.WriteLine(dataSend);

      if (checkBox_sendSocket.Checked)
        sendStringSocket(dataSend);
      if (checkBox_sendDataToArduino.Checked)
        sendStringSerial(serialPort1, dataSend);
    }

    private void sendOverStreamCommandControl(string str, string value1, string value2, string value3) {
      string dataSend = "";
      dataSend += str + "/"
          + (Convert.ToDouble(value1)).ToString() + "/"
          + (Convert.ToDouble(value2)).ToString() + "/"
          + (Convert.ToDouble(value3)).ToString();
      System.Console.WriteLine(dataSend);
      if (checkBox_sendSocket.Checked)
        sendStringSocket(dataSend);
      if (checkBox_sendDataToArduino.Checked)
        sendStringSerial(serialPort1, dataSend);
    }
    /********************************PID PARAMETERS********************************/
    /********************************PID ROLL********************************/

    private void numericUpDown_pR_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("P", numericUpDown_rollPid_kp.Value.ToString());
    }

    private void numericUpDown_iR_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("I", numericUpDown_rollPid_ki.Value.ToString());
    }

    private void numericUpDown_dR_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("D", numericUpDown_rollPid_kd.Value.ToString());
    }

    private void numericUpDown_rollPid_limits_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("X", numericUpDown_rollPid_limits.Value.ToString());
    }

    private void numericUpDown_rollPid_time_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("Y", numericUpDown_rollPid_time.Value.ToString());
    }
    /********************************PID ROLL********************************/


    /********************************PID PITCH********************************/

    private void numericUpDown_pPitch_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("Q", numericUpDown_pitchPid_kp.Value.ToString());
    }

    private void numericUpDown_iPitch_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("R", numericUpDown_pitchPid_ki.Value.ToString());
    }

    private void numericUpDown_dPitch_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("W", numericUpDown_pitchPid_kd.Value.ToString());
    }

    private void numericUpDown_pitchPid_limits_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("B", numericUpDown_pitchPid_limits.Value.ToString());

    }

    private void numericUpDown_pitchPid_time_ValueChanged(object sender, EventArgs e) {
      sendOverStreamCommand("N", numericUpDown_pitchPid_time.Value.ToString());
    }
    /********************************PID PITCH********************************/

    /********************************FLIGHT CONTROLL********************************/
    private void trackBar_throttle_Scroll(object sender, EventArgs e) {
      sendOverStreamCommandControl("C", roll.ToString(), pitch.ToString(), trackBar_throttle.Value.ToString());

    }

    private void button_clearSerial_Click(object sender, EventArgs e) {
      textBox_serialRead.Clear();
      textBox_socketRead.Clear();
    }


    private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
      if (serialPort1.IsOpen) serialPort1.Close();
      if (listenThread != null)
        if (listenThread.IsAlive) {
          this.tcpListener = null;
          isAbortThreadRequest = true;
        }
    }

    protected override bool ProcessCmdKey(ref Message msg, Keys keyData) {
      if (keyData == Keys.Q) {
        //Console.WriteLine("You pressed Q key");
        if ((trackBar_throttle.Value + numericUpDown_throttleRating.Value) <= trackBar_throttle.Maximum) {
          trackBar_throttle.Value += Convert.ToInt32(numericUpDown_throttleRating.Value);
          sendOverStreamCommandControl("C", roll.ToString(), pitch.ToString(), trackBar_throttle.Value.ToString());
        }
        return true;
      }
      if (keyData == Keys.A) {
        // Console.WriteLine("You pressed A key");
        if ((trackBar_throttle.Value - Convert.ToInt32(numericUpDown_throttleRating.Value)) >= trackBar_throttle.Minimum) {
          trackBar_throttle.Value -= Convert.ToInt32(numericUpDown_throttleRating.Value);
          sendOverStreamCommandControl("C", roll.ToString(), pitch.ToString(), trackBar_throttle.Value.ToString());
        }
        return true;
      }
      return base.ProcessCmdKey(ref msg, keyData);
    }

    private decimal Map(decimal value, decimal fromSource, decimal toSource, decimal fromTarget, decimal toTarget) {
      return Math.Round((value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget);
    }


    private void panel1_MouseMove(object sender, MouseEventArgs e) {

      if (!checkBox_stearingOn.Checked) return;

      if (e.Button == MouseButtons.Left) {
        if (e.X >= 0 && e.Y >= 0 && e.X <= panel1.Size.Width && e.Y <= panel1.Size.Height) {
          roll = Decimal.ToInt16(Map(e.X, 0, panel1.Size.Width, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
          pitch = Decimal.ToInt16(Map(e.Y, 0, panel1.Size.Height, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
          x_pos = e.X;
          y_pos = e.Y;
        } else {
          x_pos = panel1.Size.Width / 2;
          y_pos = panel1.Size.Height / 2;
          roll = Decimal.ToInt16(Map(x_pos, 0, panel1.Size.Width, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
          pitch = Decimal.ToInt16(Map(y_pos, 0, panel1.Size.Height, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
        }

      } else {
        x_pos = panel1.Size.Width / 2;
        y_pos = panel1.Size.Height / 2;
        roll = Decimal.ToInt16(Map(x_pos, 0, panel1.Size.Width, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
        pitch = Decimal.ToInt16(Map(y_pos, 0, panel1.Size.Height, -numericUpDown_stearingLimits.Value, numericUpDown_stearingLimits.Value));
      }
      panel1.Invalidate();

      textBox_calcPitch.Text = pitch.ToString();
      textBox_calcRoll.Text = roll.ToString();
      sendOverStreamCommandControl("C", roll.ToString(), pitch.ToString(), trackBar_throttle.Value.ToString());

    }

    private void panel1_Paint(object sender, PaintEventArgs e) {

      Graphics g = panel1.CreateGraphics();
      g.DrawLine(new Pen(Color.Black, 1), panel1.Width / 2, 0, panel1.Width / 2, panel1.Height);
      g.DrawLine(new Pen(Color.Black, 1), 0, panel1.Height / 2, panel1.Width, panel1.Height / 2);
      System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.DarkGray);
      g.FillEllipse(myBrush, x_pos - 10, y_pos - 10, 20, 20);



    }






    /********************************FLIGHT CONTROLL********************************/


  }
}
