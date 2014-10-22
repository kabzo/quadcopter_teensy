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
using Microsoft.DirectX.DirectInput;


namespace GUI {
  public partial class GUI : Form {
    private Hashtable hashtable = new Hashtable();

    private Graph graph1, graph2;

    private SocketGUI socketGui;

    private bool firstTimeSet = false;
    
    private Joystick jst;

    public GUI() {
      InitializeComponent();

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

      hashtable.Add("fl", 1000); //motors names
      hashtable.Add("fr", 1000);
      hashtable.Add("bl", 1000);
      hashtable.Add("br", 1000);

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

    }

    private decimal Map(decimal value, decimal fromSource, decimal toSource, decimal fromTarget, decimal toTarget) {
      return Math.Round((value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget);
    }

    private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e) {
      string line;
      if (serialPort1.IsOpen) {
        try {
          line = serialPort1.ReadLine();
          this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
        } catch (Exception ex) { System.Console.WriteLine("Serialport readline: " + ex.Message); }
      }
    }

    private delegate void LineReceivedEvent(string line);

    private void addValuesTextBox() {

      if (Convert.ToInt32(hashtable["bl"]) >= progressBar_bl.Minimum && Convert.ToInt32(hashtable["bl"]) <= progressBar_bl.Maximum)
        progressBar_bl.Value = Convert.ToInt32(hashtable["bl"]);
      if (Convert.ToInt32(hashtable["br"]) >= progressBar_br.Minimum && Convert.ToInt32(hashtable["br"]) <= progressBar_br.Maximum)
        progressBar_br.Value = Convert.ToInt32(hashtable["br"]);
      if (Convert.ToInt32(hashtable["fl"]) >= progressBar_fl.Minimum && Convert.ToInt32(hashtable["fl"]) <= progressBar_fl.Maximum)
        progressBar_fl.Value = Convert.ToInt32(hashtable["fl"]);
      if (Convert.ToInt32(hashtable["fr"]) >= progressBar_fr.Minimum && Convert.ToInt32(hashtable["fr"]) <= progressBar_fr.Maximum)
        progressBar_fr.Value = Convert.ToInt32(hashtable["fr"]);

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

      if (firstTimeSet ) {
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
      }
    }

    public void LineReceived(string line) {
      if (!line.Contains("?") && line != "\r" && line != "" && !line.Contains(",") && !line.Equals("-\r")) {
        if (serialPort1.IsOpen) {
          textBox_serialRead.AppendText(line.ToString());
          textBox_serialRead.AppendText(Environment.NewLine);
        }
      } else {
        if (line.Equals("-\r")) {
          System.Console.WriteLine("Settings parameters");
          if (firstTimeSet)
            firstTimeSet = false;
          else
            firstTimeSet = true;
        }
        string[] dataSplitedGroups = null;
        string[] dataSplitedValues = null;

        dataSplitedGroups = line.Trim().Split(',');

        foreach (string s in dataSplitedGroups) {
          dataSplitedValues = s.Split('/');
          if (hashtable.Contains(dataSplitedValues[0])) {
            double valDouble;
            try {
              string number = dataSplitedValues[1];
              valDouble = double.Parse(number, System.Globalization.CultureInfo.InvariantCulture);
              hashtable[dataSplitedValues[0]] = valDouble;
            } catch (Exception e) {System.Console.WriteLine("Splitter: " + e.Message);}

          }
        }
      }
      addValuesTextBox();
      actualizate_Parameters();

    }

    private void actualizate_Parameters() {

      if (tabControl_mainControl.SelectedIndex == 2) {
        Hashtable hashTableGraph1 = new Hashtable();
        Hashtable hashTableGraph2 = new Hashtable();

        foreach (object s in checkedListBox_graph1.CheckedItems)
          hashTableGraph1.Add(s.ToString(), hashtable[s.ToString()]);
        foreach (object s in checkedListBox_graph2.CheckedItems)
          hashTableGraph2.Add(s.ToString(), hashtable[s.ToString()]);

        graph1.drawGraph(hashTableGraph1);
        graph2.drawGraph(hashTableGraph2);
      }
      if (tabControl_mainControl.SelectedIndex == 0) {
        attitudeIndicatorInstrumentControl2.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));
        headingIndicatorInstrumentControl2.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
      }

      if (tabControl_mainControl.SelectedIndex == 3) {
        // attitudeIndicatorInstrumentControl1.SetAttitudeIndicatorParameters(Convert.ToDouble(hashtable["pitch"]), Convert.ToDouble(hashtable["roll"]));
        // headingIndicatorInstrumentControl1.SetHeadingIndicatorParameters(Convert.ToInt32(hashtable["yaw"]) + 180);
      }

    }

    private void btn_connect_Click(object sender, EventArgs e) {
      textBox_serialRead.Clear();
      textBox_socketRead.Clear();
      String comPort = Convert.ToString(comboBox_Comports.SelectedItem);
      switch (comPort) {
        case "Socket": {
          socketGui = new SocketGUI();
          System.Console.WriteLine(socketGui.connected);
          timer_socketReceive.Start();
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
     
      if (serialPort1.IsOpen) {
        serialPort1.Close();
        btn_connect.Enabled = true;
        btn_disconnect.Enabled = false;
        lb_connectionStatus.Text = "Disconnected";
      }
      if (socketGui != null)
        socketGui.stopSocket();

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
        serialPort.Write(str.ToString());
    }

    private void sendStringSocket(String str) {
      socketGui.sendStringSocket(str);
    }

    private void sendOverStreamCommand(string str, string value, int faktor = 100) {
      string dataSend = "";
      dataSend += str + (Convert.ToDouble(value) * faktor).ToString() + "|";
      // System.Console.WriteLine(dataSend);
      if (checkBox_sendSocket.Checked)
        sendStringSocket(dataSend);
      if (checkBox_sendDataToArduino.Checked)
        sendStringSerial(serialPort1, dataSend);
      textBox_sendingStream1.Text = dataSend;
      textBox_sendingStream2.Text = dataSend;
    }

    private void sendOverStreamCommandControl(string str, string value1, string value2, string value3,string value4) {
      string dataSend = "";
      dataSend += str
          + (Convert.ToDouble(value1)).ToString() + "/"
          + (Convert.ToDouble(value2)).ToString() + "/"
          + (Convert.ToDouble(value3)).ToString() + "/"
          + (Convert.ToDouble(value4)).ToString() + "/|";
      //System.Console.WriteLine(System.Text.ASCIIEncoding.ASCII.GetByteCount(dataSend));


      if (checkBox_sendSocket.Checked)
        sendStringSocket(dataSend);
      if (checkBox_sendDataToArduino.Checked)
        sendStringSerial(serialPort1, dataSend);
      textBox_sendingStream1.Text = dataSend;
      textBox_sendingStream2.Text = dataSend;
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

    private void button_clearSerial_Click(object sender, EventArgs e) {
      textBox_serialRead.Clear();
      textBox_socketRead.Clear();
    }

    private void btn_joystick_calibrate_Click(object sender, EventArgs e) {
      if (jst != null) {
        joystickTimer.Stop();

        int repeat = 350000;
        int[] valueX = new int[repeat];
        int[] valueY = new int[repeat];
        int[] valueZ = new int[repeat];
        int[] valueRy = new int[repeat];


        for (int i = 0; i < repeat; i++) {
          jst.UpdateStatus();

          valueX[i] = jst.AxisX;
          valueY[i] = jst.AxisY;
          valueZ[i] = jst.AxisZ;
          valueRy[i] = jst.AxisRy;
        }
        jst.rollMax = valueX.Max();
        jst.rollMin = valueX.Min();

        jst.pitchMax = valueY.Max();
        jst.pitchMin = valueY.Min();

        jst.throttleMax = valueZ.Max();
        jst.throttleMin = valueZ.Min();

        jst.yawMax = valueRy.Max();
        jst.yawMin = valueRy.Min();

        joystickTimer.Start();
      }
    }

    private void button_joystick_connect_Click(object sender, EventArgs e) {
      if (jst == null) {
        jst = new Joystick(this.Handle);
        string[] sticks = jst.FindJoysticks();
        if (sticks != null) {
          jst.AcquireJoystick(sticks[0]);
          joystickTimer.Start();
          button_joystick_connect.Text = "Disconnect";
          if (jst != null) label_joystick_connection.Text = "Connected";
        }
      } else {
        joystickTimer.Stop();
        jst = null;
        button_joystick_connect.Text = "Connect";

      }
    }

    private void joystickTimer_Tick(object sender, EventArgs e) {
      if (jst != null) {
        jst.UpdateStatus();
            
        progressBar_joystick_throttle.Value = jst.throttle;
        
        progressBar_joystick_pitch.Value = jst.pitch + 100;
        progressBar_joystick_roll.Value = jst.roll + 100;
        progressBar_joystick_yaw.Value = jst.yaw + 180;

        textBox_joystick_throttleVal.Text = jst.throttle.ToString();
        textBox_joystick_rollVal.Text = jst.roll.ToString();
        textBox_joystick_pitchVal.Text = jst.pitch.ToString();
        textBox_joystick_yawVal.Text = jst.yaw.ToString();

        if (jst.oldZ != jst.AxisZ || jst.oldX != jst.AxisX || jst.oldY != jst.AxisY || jst.oldRy != jst.AxisRy) {
          sendOverStreamCommandControl("K", jst.throttle.ToString(), jst.roll.ToString(), jst.pitch.ToString(),jst.yaw.ToString());
          jst.oldZ = jst.AxisZ;
          jst.oldX = jst.AxisX;
          jst.oldY = jst.AxisY;
          jst.oldRy = jst.AxisRy;
        }

        //if (jst.oldZ != jst.AxisZ) {
        //  sendOverStreamCommand("T", jst.throttle.ToString(), 1);
        //  jst.oldZ = jst.AxisZ;
        //}
        //if (jst.oldX != jst.AxisX) {
        //  sendOverStreamCommand("L", jst.roll.ToString(), 1);
        //  jst.oldX = jst.AxisX;
        //}
        //if (jst.oldY != jst.AxisY) {
        //  sendOverStreamCommand("U", jst.pitch.ToString(), 1);
        //  jst.oldY = jst.AxisY;
        //}

      }
    }

    private void timer_socketReceive_Tick(object sender, EventArgs e) {
      if (socketGui.connected) {
        btn_connect.Enabled = false;
        btn_disconnect.Enabled = true;
        lb_connectionStatus.Text = "Connected";
      }
      if (socketGui.dataReceived) {
        string line = socketGui.socketStringReceiver;
        socketGui.dataReceived = false;
        if (!line.Contains("?") && line != "\r" && line != "" && !line.Contains(",")) {
          textBox_socketRead.AppendText(line.ToString());
          textBox_socketRead.AppendText(Environment.NewLine);
        } else {
          LineReceived(line);
        }
      }
      /********************************FLIGHT CONTROLL********************************/
    }

  }
}
