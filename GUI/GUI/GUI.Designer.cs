namespace GUI
{
    partial class GUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GUI));
      this.tabControlImageList = new System.Windows.Forms.ImageList(this.components);
      this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
      this.joystickTimer = new System.Windows.Forms.Timer(this.components);
      this.lb_connectionStatus = new System.Windows.Forms.Label();
      this.comboBox_Comports = new System.Windows.Forms.ComboBox();
      this.btn_disconnect = new System.Windows.Forms.Button();
      this.btn_connect = new System.Windows.Forms.Button();
      this.Settings = new System.Windows.Forms.TabPage();
      this.checkBox_stearingOn = new System.Windows.Forms.CheckBox();
      this.label_ = new System.Windows.Forms.Label();
      this.label19 = new System.Windows.Forms.Label();
      this.textBox_calcRoll = new System.Windows.Forms.TextBox();
      this.textBox_calcPitch = new System.Windows.Forms.TextBox();
      this.label18 = new System.Windows.Forms.Label();
      this.label17 = new System.Windows.Forms.Label();
      this.textBox_setpointPitch = new System.Windows.Forms.TextBox();
      this.textBox_setpointRoll = new System.Windows.Forms.TextBox();
      this.textBox_sendingStream1 = new System.Windows.Forms.TextBox();
      this.label11 = new System.Windows.Forms.Label();
      this.headingIndicatorInstrumentControl2 = new AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl();
      this.attitudeIndicatorInstrumentControl2 = new AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl();
      this.label7 = new System.Windows.Forms.Label();
      this.textBox_bl = new System.Windows.Forms.TextBox();
      this.textBox_br = new System.Windows.Forms.TextBox();
      this.textBox_fl = new System.Windows.Forms.TextBox();
      this.textBox_fr = new System.Windows.Forms.TextBox();
      this.textBox_throttle = new System.Windows.Forms.TextBox();
      this.label6 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.progressBar_br = new System.Windows.Forms.ProgressBar();
      this.progressBar_fl = new System.Windows.Forms.ProgressBar();
      this.progressBar_fr = new System.Windows.Forms.ProgressBar();
      this.progressBar_bl = new System.Windows.Forms.ProgressBar();
      this.groupBox4 = new System.Windows.Forms.GroupBox();
      this.checkBox_sendDataToArduino = new System.Windows.Forms.CheckBox();
      this.checkBox_sendSocket = new System.Windows.Forms.CheckBox();
      this.tabControl_pid = new System.Windows.Forms.TabControl();
      this.Roll = new System.Windows.Forms.TabPage();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.textBox_rollPid_time = new System.Windows.Forms.TextBox();
      this.textBox_rollPid_limits = new System.Windows.Forms.TextBox();
      this.label13 = new System.Windows.Forms.Label();
      this.label12 = new System.Windows.Forms.Label();
      this.numericUpDown_rollPid_time = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_rollPid_limits = new System.Windows.Forms.NumericUpDown();
      this.lb_d = new System.Windows.Forms.Label();
      this.lb_i = new System.Windows.Forms.Label();
      this.lb_p = new System.Windows.Forms.Label();
      this.textBox_rollPid_kp = new System.Windows.Forms.TextBox();
      this.numericUpDown_rollPid_kp = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_rollPid_ki = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_rollPid_kd = new System.Windows.Forms.NumericUpDown();
      this.textBox_rollPid_ki = new System.Windows.Forms.TextBox();
      this.textBox_rollPid_kd = new System.Windows.Forms.TextBox();
      this.Pitch = new System.Windows.Forms.TabPage();
      this.groupBox5 = new System.Windows.Forms.GroupBox();
      this.textBox_pitchPid_time = new System.Windows.Forms.TextBox();
      this.textBox_pitchPid_limits = new System.Windows.Forms.TextBox();
      this.label9 = new System.Windows.Forms.Label();
      this.label10 = new System.Windows.Forms.Label();
      this.numericUpDown_pitchPid_time = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_pitchPid_limits = new System.Windows.Forms.NumericUpDown();
      this.label3 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.label16 = new System.Windows.Forms.Label();
      this.textBox_pitchPid_kp = new System.Windows.Forms.TextBox();
      this.numericUpDown_pitchPid_kp = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_pitchPid_ki = new System.Windows.Forms.NumericUpDown();
      this.numericUpDown_pitchPid_kd = new System.Windows.Forms.NumericUpDown();
      this.textBox_pitchPid_ki = new System.Windows.Forms.TextBox();
      this.textBox_pitchPid_kd = new System.Windows.Forms.TextBox();
      this.GPS = new System.Windows.Forms.TabPage();
      this.gMap = new GMap.NET.WindowsForms.GMapControl();
      this.headingIndicatorInstrumentControl1 = new AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl();
      this.attitudeIndicatorInstrumentControl1 = new AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl();
      this.Console = new System.Windows.Forms.TabPage();
      this.textBox_sendingStream2 = new System.Windows.Forms.TextBox();
      this.label14 = new System.Windows.Forms.Label();
      this.tabControl_socket_serial = new System.Windows.Forms.TabControl();
      this.Socket = new System.Windows.Forms.TabPage();
      this.textBox_socketRead = new System.Windows.Forms.TextBox();
      this.Serial = new System.Windows.Forms.TabPage();
      this.textBox_serialRead = new System.Windows.Forms.TextBox();
      this.button_clearSerial = new System.Windows.Forms.Button();
      this.IMU = new System.Windows.Forms.TabPage();
      this.zedGraphControl2 = new ZedGraph.ZedGraphControl();
      this.label8 = new System.Windows.Forms.Label();
      this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
      this.groupBox3 = new System.Windows.Forms.GroupBox();
      this.tabControl_graphControl = new System.Windows.Forms.TabControl();
      this.tabPage4 = new System.Windows.Forms.TabPage();
      this.checkedListBox_graph1 = new System.Windows.Forms.CheckedListBox();
      this.tabPage5 = new System.Windows.Forms.TabPage();
      this.checkedListBox_graph2 = new System.Windows.Forms.CheckedListBox();
      this.tabControl_mainControl = new System.Windows.Forms.TabControl();
      this.Joystick = new System.Windows.Forms.TabPage();
      this.label15 = new System.Windows.Forms.Label();
      this.textBox_joystick_yawVal = new System.Windows.Forms.TextBox();
      this.progressBar_joystick_yaw = new System.Windows.Forms.ProgressBar();
      this.button_joystick_connect = new System.Windows.Forms.Button();
      this.textBox_joystick_rollVal = new System.Windows.Forms.TextBox();
      this.textBox_joystick_pitchVal = new System.Windows.Forms.TextBox();
      this.textBox_joystick_throttleVal = new System.Windows.Forms.TextBox();
      this.btn_joystick_calibrate = new System.Windows.Forms.Button();
      this.label26 = new System.Windows.Forms.Label();
      this.label25 = new System.Windows.Forms.Label();
      this.label24 = new System.Windows.Forms.Label();
      this.progressBar_joystick_roll = new System.Windows.Forms.ProgressBar();
      this.progressBar_joystick_pitch = new System.Windows.Forms.ProgressBar();
      this.progressBar_joystick_throttle = new System.Windows.Forms.ProgressBar();
      this.label21 = new System.Windows.Forms.Label();
      this.label_joystick_connection = new System.Windows.Forms.Label();
      this.status = new System.Windows.Forms.Label();
      this.timer_socketReceive = new System.Windows.Forms.Timer(this.components);
      this.Settings.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.tabControl_pid.SuspendLayout();
      this.Roll.SuspendLayout();
      this.groupBox1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_time)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_limits)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_kp)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_ki)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_kd)).BeginInit();
      this.Pitch.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_time)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_limits)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_kp)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_ki)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_kd)).BeginInit();
      this.GPS.SuspendLayout();
      this.Console.SuspendLayout();
      this.tabControl_socket_serial.SuspendLayout();
      this.Socket.SuspendLayout();
      this.Serial.SuspendLayout();
      this.IMU.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.tabControl_graphControl.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.tabPage5.SuspendLayout();
      this.tabControl_mainControl.SuspendLayout();
      this.Joystick.SuspendLayout();
      this.SuspendLayout();
      // 
      // tabControlImageList
      // 
      this.tabControlImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("tabControlImageList.ImageStream")));
      this.tabControlImageList.TransparentColor = System.Drawing.Color.Transparent;
      this.tabControlImageList.Images.SetKeyName(0, "quadcopter-128.png");
      this.tabControlImageList.Images.SetKeyName(1, "terminal-512.png");
      this.tabControlImageList.Images.SetKeyName(2, "chart_stock_graph_growth-512.png");
      // 
      // serialPort1
      // 
      this.serialPort1.BaudRate = 115200;
      this.serialPort1.PortName = "COM3";
      // 
      // joystickTimer
      // 
      this.joystickTimer.Enabled = true;
      this.joystickTimer.Interval = 50;
      this.joystickTimer.Tick += new System.EventHandler(this.joystickTimer_Tick);
      // 
      // lb_connectionStatus
      // 
      this.lb_connectionStatus.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.lb_connectionStatus.AutoSize = true;
      this.lb_connectionStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
      this.lb_connectionStatus.Location = new System.Drawing.Point(880, 19);
      this.lb_connectionStatus.Name = "lb_connectionStatus";
      this.lb_connectionStatus.Size = new System.Drawing.Size(94, 17);
      this.lb_connectionStatus.TabIndex = 13;
      this.lb_connectionStatus.Text = "Disconnected";
      // 
      // comboBox_Comports
      // 
      this.comboBox_Comports.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.comboBox_Comports.FormattingEnabled = true;
      this.comboBox_Comports.Location = new System.Drawing.Point(980, 19);
      this.comboBox_Comports.Name = "comboBox_Comports";
      this.comboBox_Comports.Size = new System.Drawing.Size(121, 21);
      this.comboBox_Comports.TabIndex = 14;
      this.comboBox_Comports.Click += new System.EventHandler(this.comboBoxComports_Click);
      // 
      // btn_disconnect
      // 
      this.btn_disconnect.AccessibleRole = System.Windows.Forms.AccessibleRole.Sound;
      this.btn_disconnect.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.btn_disconnect.BackColor = System.Drawing.Color.White;
      this.btn_disconnect.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btn_disconnect.BackgroundImage")));
      this.btn_disconnect.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
      this.btn_disconnect.Location = new System.Drawing.Point(1107, 5);
      this.btn_disconnect.Name = "btn_disconnect";
      this.btn_disconnect.Size = new System.Drawing.Size(52, 46);
      this.btn_disconnect.TabIndex = 1;
      this.btn_disconnect.UseVisualStyleBackColor = false;
      this.btn_disconnect.Click += new System.EventHandler(this.btn_disconnect_Click);
      // 
      // btn_connect
      // 
      this.btn_connect.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.btn_connect.BackColor = System.Drawing.Color.White;
      this.btn_connect.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btn_connect.BackgroundImage")));
      this.btn_connect.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.btn_connect.Location = new System.Drawing.Point(1165, 5);
      this.btn_connect.Name = "btn_connect";
      this.btn_connect.Size = new System.Drawing.Size(49, 46);
      this.btn_connect.TabIndex = 9;
      this.btn_connect.UseVisualStyleBackColor = false;
      this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
      // 
      // Settings
      // 
      this.Settings.BackColor = System.Drawing.Color.DimGray;
      this.Settings.Controls.Add(this.checkBox_stearingOn);
      this.Settings.Controls.Add(this.label_);
      this.Settings.Controls.Add(this.label19);
      this.Settings.Controls.Add(this.textBox_calcRoll);
      this.Settings.Controls.Add(this.textBox_calcPitch);
      this.Settings.Controls.Add(this.label18);
      this.Settings.Controls.Add(this.label17);
      this.Settings.Controls.Add(this.textBox_setpointPitch);
      this.Settings.Controls.Add(this.textBox_setpointRoll);
      this.Settings.Controls.Add(this.textBox_sendingStream1);
      this.Settings.Controls.Add(this.label11);
      this.Settings.Controls.Add(this.headingIndicatorInstrumentControl2);
      this.Settings.Controls.Add(this.attitudeIndicatorInstrumentControl2);
      this.Settings.Controls.Add(this.label7);
      this.Settings.Controls.Add(this.textBox_bl);
      this.Settings.Controls.Add(this.textBox_br);
      this.Settings.Controls.Add(this.textBox_fl);
      this.Settings.Controls.Add(this.textBox_fr);
      this.Settings.Controls.Add(this.textBox_throttle);
      this.Settings.Controls.Add(this.label6);
      this.Settings.Controls.Add(this.label5);
      this.Settings.Controls.Add(this.label2);
      this.Settings.Controls.Add(this.label1);
      this.Settings.Controls.Add(this.progressBar_br);
      this.Settings.Controls.Add(this.progressBar_fl);
      this.Settings.Controls.Add(this.progressBar_fr);
      this.Settings.Controls.Add(this.progressBar_bl);
      this.Settings.Controls.Add(this.groupBox4);
      this.Settings.Controls.Add(this.tabControl_pid);
      this.Settings.Location = new System.Drawing.Point(4, 57);
      this.Settings.Name = "Settings";
      this.Settings.Size = new System.Drawing.Size(1213, 740);
      this.Settings.TabIndex = 3;
      this.Settings.Text = "Settings";
      // 
      // checkBox_stearingOn
      // 
      this.checkBox_stearingOn.AutoSize = true;
      this.checkBox_stearingOn.Location = new System.Drawing.Point(1061, 62);
      this.checkBox_stearingOn.Name = "checkBox_stearingOn";
      this.checkBox_stearingOn.Size = new System.Drawing.Size(99, 21);
      this.checkBox_stearingOn.TabIndex = 63;
      this.checkBox_stearingOn.Text = "Stearing";
      this.checkBox_stearingOn.UseVisualStyleBackColor = true;
      // 
      // label_
      // 
      this.label_.AutoSize = true;
      this.label_.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label_.Location = new System.Drawing.Point(826, 330);
      this.label_.Name = "label_";
      this.label_.Size = new System.Drawing.Size(62, 17);
      this.label_.TabIndex = 60;
      this.label_.Text = "Pitch:";
      // 
      // label19
      // 
      this.label19.AutoSize = true;
      this.label19.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label19.Location = new System.Drawing.Point(835, 362);
      this.label19.Name = "label19";
      this.label19.Size = new System.Drawing.Size(53, 17);
      this.label19.TabIndex = 59;
      this.label19.Text = "Roll:";
      // 
      // textBox_calcRoll
      // 
      this.textBox_calcRoll.Location = new System.Drawing.Point(894, 359);
      this.textBox_calcRoll.Name = "textBox_calcRoll";
      this.textBox_calcRoll.ReadOnly = true;
      this.textBox_calcRoll.Size = new System.Drawing.Size(112, 25);
      this.textBox_calcRoll.TabIndex = 58;
      // 
      // textBox_calcPitch
      // 
      this.textBox_calcPitch.Location = new System.Drawing.Point(894, 327);
      this.textBox_calcPitch.Name = "textBox_calcPitch";
      this.textBox_calcPitch.ReadOnly = true;
      this.textBox_calcPitch.Size = new System.Drawing.Size(112, 25);
      this.textBox_calcPitch.TabIndex = 57;
      // 
      // label18
      // 
      this.label18.AutoSize = true;
      this.label18.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label18.Location = new System.Drawing.Point(754, 425);
      this.label18.Name = "label18";
      this.label18.Size = new System.Drawing.Size(134, 17);
      this.label18.TabIndex = 55;
      this.label18.Text = "Setpoint Roll:";
      // 
      // label17
      // 
      this.label17.AutoSize = true;
      this.label17.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label17.Location = new System.Drawing.Point(745, 394);
      this.label17.Name = "label17";
      this.label17.Size = new System.Drawing.Size(143, 17);
      this.label17.TabIndex = 54;
      this.label17.Text = "Setpoint Pitch:";
      // 
      // textBox_setpointPitch
      // 
      this.textBox_setpointPitch.Location = new System.Drawing.Point(894, 391);
      this.textBox_setpointPitch.Name = "textBox_setpointPitch";
      this.textBox_setpointPitch.ReadOnly = true;
      this.textBox_setpointPitch.Size = new System.Drawing.Size(112, 25);
      this.textBox_setpointPitch.TabIndex = 53;
      // 
      // textBox_setpointRoll
      // 
      this.textBox_setpointRoll.Location = new System.Drawing.Point(894, 422);
      this.textBox_setpointRoll.Name = "textBox_setpointRoll";
      this.textBox_setpointRoll.ReadOnly = true;
      this.textBox_setpointRoll.Size = new System.Drawing.Size(112, 25);
      this.textBox_setpointRoll.TabIndex = 52;
      // 
      // textBox_sendingStream1
      // 
      this.textBox_sendingStream1.Location = new System.Drawing.Point(444, 410);
      this.textBox_sendingStream1.Name = "textBox_sendingStream1";
      this.textBox_sendingStream1.ReadOnly = true;
      this.textBox_sendingStream1.Size = new System.Drawing.Size(258, 25);
      this.textBox_sendingStream1.TabIndex = 34;
      // 
      // label11
      // 
      this.label11.AutoSize = true;
      this.label11.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label11.Location = new System.Drawing.Point(359, 413);
      this.label11.Name = "label11";
      this.label11.Size = new System.Drawing.Size(80, 17);
      this.label11.TabIndex = 50;
      this.label11.Text = "Sending:";
      // 
      // headingIndicatorInstrumentControl2
      // 
      this.headingIndicatorInstrumentControl2.Location = new System.Drawing.Point(8, 348);
      this.headingIndicatorInstrumentControl2.Name = "headingIndicatorInstrumentControl2";
      this.headingIndicatorInstrumentControl2.Size = new System.Drawing.Size(338, 341);
      this.headingIndicatorInstrumentControl2.TabIndex = 44;
      this.headingIndicatorInstrumentControl2.Text = "headingIndicatorInstrumentControl2";
      // 
      // attitudeIndicatorInstrumentControl2
      // 
      this.attitudeIndicatorInstrumentControl2.Location = new System.Drawing.Point(8, 5);
      this.attitudeIndicatorInstrumentControl2.Name = "attitudeIndicatorInstrumentControl2";
      this.attitudeIndicatorInstrumentControl2.Size = new System.Drawing.Size(338, 348);
      this.attitudeIndicatorInstrumentControl2.TabIndex = 43;
      this.attitudeIndicatorInstrumentControl2.Text = "attitudeIndicatorInstrumentControl2";
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label7.Location = new System.Drawing.Point(799, 456);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(89, 17);
      this.label7.TabIndex = 42;
      this.label7.Text = "Throttle:";
      // 
      // textBox_bl
      // 
      this.textBox_bl.Location = new System.Drawing.Point(579, 57);
      this.textBox_bl.Name = "textBox_bl";
      this.textBox_bl.ReadOnly = true;
      this.textBox_bl.Size = new System.Drawing.Size(112, 25);
      this.textBox_bl.TabIndex = 41;
      // 
      // textBox_br
      // 
      this.textBox_br.Location = new System.Drawing.Point(943, 60);
      this.textBox_br.Name = "textBox_br";
      this.textBox_br.ReadOnly = true;
      this.textBox_br.Size = new System.Drawing.Size(112, 25);
      this.textBox_br.TabIndex = 40;
      // 
      // textBox_fl
      // 
      this.textBox_fl.Location = new System.Drawing.Point(579, 26);
      this.textBox_fl.Name = "textBox_fl";
      this.textBox_fl.ReadOnly = true;
      this.textBox_fl.Size = new System.Drawing.Size(112, 25);
      this.textBox_fl.TabIndex = 39;
      // 
      // textBox_fr
      // 
      this.textBox_fr.Location = new System.Drawing.Point(943, 29);
      this.textBox_fr.Name = "textBox_fr";
      this.textBox_fr.ReadOnly = true;
      this.textBox_fr.Size = new System.Drawing.Size(112, 25);
      this.textBox_fr.TabIndex = 38;
      // 
      // textBox_throttle
      // 
      this.textBox_throttle.Location = new System.Drawing.Point(894, 453);
      this.textBox_throttle.Name = "textBox_throttle";
      this.textBox_throttle.ReadOnly = true;
      this.textBox_throttle.Size = new System.Drawing.Size(112, 25);
      this.textBox_throttle.TabIndex = 37;
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label6.Location = new System.Drawing.Point(714, 63);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(35, 17);
      this.label6.TabIndex = 35;
      this.label6.Text = "BR:";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label5.Location = new System.Drawing.Point(357, 31);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(35, 17);
      this.label5.TabIndex = 34;
      this.label5.Text = "FL:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label2.Location = new System.Drawing.Point(714, 34);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(35, 17);
      this.label2.TabIndex = 33;
      this.label2.Text = "FR:";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label1.Location = new System.Drawing.Point(357, 60);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(35, 17);
      this.label1.TabIndex = 22;
      this.label1.Text = "BL:";
      // 
      // progressBar_br
      // 
      this.progressBar_br.Location = new System.Drawing.Point(755, 60);
      this.progressBar_br.Maximum = 2000;
      this.progressBar_br.Minimum = 900;
      this.progressBar_br.Name = "progressBar_br";
      this.progressBar_br.Size = new System.Drawing.Size(172, 23);
      this.progressBar_br.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
      this.progressBar_br.TabIndex = 32;
      this.progressBar_br.Value = 900;
      // 
      // progressBar_fl
      // 
      this.progressBar_fl.Location = new System.Drawing.Point(398, 28);
      this.progressBar_fl.Maximum = 2000;
      this.progressBar_fl.Minimum = 900;
      this.progressBar_fl.Name = "progressBar_fl";
      this.progressBar_fl.Size = new System.Drawing.Size(172, 23);
      this.progressBar_fl.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
      this.progressBar_fl.TabIndex = 31;
      this.progressBar_fl.Value = 900;
      // 
      // progressBar_fr
      // 
      this.progressBar_fr.Location = new System.Drawing.Point(755, 31);
      this.progressBar_fr.Maximum = 2000;
      this.progressBar_fr.Minimum = 900;
      this.progressBar_fr.Name = "progressBar_fr";
      this.progressBar_fr.Size = new System.Drawing.Size(172, 23);
      this.progressBar_fr.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
      this.progressBar_fr.TabIndex = 30;
      this.progressBar_fr.Value = 900;
      // 
      // progressBar_bl
      // 
      this.progressBar_bl.Location = new System.Drawing.Point(398, 57);
      this.progressBar_bl.Maximum = 2000;
      this.progressBar_bl.Minimum = 900;
      this.progressBar_bl.Name = "progressBar_bl";
      this.progressBar_bl.Size = new System.Drawing.Size(172, 23);
      this.progressBar_bl.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
      this.progressBar_bl.TabIndex = 29;
      this.progressBar_bl.Value = 900;
      // 
      // groupBox4
      // 
      this.groupBox4.Controls.Add(this.checkBox_sendDataToArduino);
      this.groupBox4.Controls.Add(this.checkBox_sendSocket);
      this.groupBox4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.groupBox4.Location = new System.Drawing.Point(354, 103);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new System.Drawing.Size(348, 72);
      this.groupBox4.TabIndex = 28;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Settings:";
      // 
      // checkBox_sendDataToArduino
      // 
      this.checkBox_sendDataToArduino.AutoSize = true;
      this.checkBox_sendDataToArduino.Dock = System.Windows.Forms.DockStyle.Top;
      this.checkBox_sendDataToArduino.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.checkBox_sendDataToArduino.Location = new System.Drawing.Point(3, 42);
      this.checkBox_sendDataToArduino.Name = "checkBox_sendDataToArduino";
      this.checkBox_sendDataToArduino.Size = new System.Drawing.Size(342, 21);
      this.checkBox_sendDataToArduino.TabIndex = 26;
      this.checkBox_sendDataToArduino.Text = "Send over serial";
      this.checkBox_sendDataToArduino.UseVisualStyleBackColor = true;
      // 
      // checkBox_sendSocket
      // 
      this.checkBox_sendSocket.AutoSize = true;
      this.checkBox_sendSocket.Dock = System.Windows.Forms.DockStyle.Top;
      this.checkBox_sendSocket.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.checkBox_sendSocket.Location = new System.Drawing.Point(3, 21);
      this.checkBox_sendSocket.Name = "checkBox_sendSocket";
      this.checkBox_sendSocket.Size = new System.Drawing.Size(342, 21);
      this.checkBox_sendSocket.TabIndex = 27;
      this.checkBox_sendSocket.Text = "Send over socket";
      this.checkBox_sendSocket.UseVisualStyleBackColor = true;
      // 
      // tabControl_pid
      // 
      this.tabControl_pid.Controls.Add(this.Roll);
      this.tabControl_pid.Controls.Add(this.Pitch);
      this.tabControl_pid.Location = new System.Drawing.Point(354, 191);
      this.tabControl_pid.Name = "tabControl_pid";
      this.tabControl_pid.SelectedIndex = 0;
      this.tabControl_pid.Size = new System.Drawing.Size(355, 213);
      this.tabControl_pid.TabIndex = 0;
      // 
      // Roll
      // 
      this.Roll.BackColor = System.Drawing.Color.DimGray;
      this.Roll.Controls.Add(this.groupBox1);
      this.Roll.Location = new System.Drawing.Point(4, 26);
      this.Roll.Name = "Roll";
      this.Roll.Padding = new System.Windows.Forms.Padding(3);
      this.Roll.Size = new System.Drawing.Size(347, 183);
      this.Roll.TabIndex = 0;
      this.Roll.Text = "Roll";
      // 
      // groupBox1
      // 
      this.groupBox1.BackColor = System.Drawing.Color.DimGray;
      this.groupBox1.Controls.Add(this.textBox_rollPid_time);
      this.groupBox1.Controls.Add(this.textBox_rollPid_limits);
      this.groupBox1.Controls.Add(this.label13);
      this.groupBox1.Controls.Add(this.label12);
      this.groupBox1.Controls.Add(this.numericUpDown_rollPid_time);
      this.groupBox1.Controls.Add(this.numericUpDown_rollPid_limits);
      this.groupBox1.Controls.Add(this.lb_d);
      this.groupBox1.Controls.Add(this.lb_i);
      this.groupBox1.Controls.Add(this.lb_p);
      this.groupBox1.Controls.Add(this.textBox_rollPid_kp);
      this.groupBox1.Controls.Add(this.numericUpDown_rollPid_kp);
      this.groupBox1.Controls.Add(this.numericUpDown_rollPid_ki);
      this.groupBox1.Controls.Add(this.numericUpDown_rollPid_kd);
      this.groupBox1.Controls.Add(this.textBox_rollPid_ki);
      this.groupBox1.Controls.Add(this.textBox_rollPid_kd);
      this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.groupBox1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.groupBox1.Location = new System.Drawing.Point(3, 3);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(341, 177);
      this.groupBox1.TabIndex = 25;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "PID ROLL:";
      // 
      // textBox_rollPid_time
      // 
      this.textBox_rollPid_time.Location = new System.Drawing.Point(191, 143);
      this.textBox_rollPid_time.Name = "textBox_rollPid_time";
      this.textBox_rollPid_time.ReadOnly = true;
      this.textBox_rollPid_time.Size = new System.Drawing.Size(112, 25);
      this.textBox_rollPid_time.TabIndex = 27;
      // 
      // textBox_rollPid_limits
      // 
      this.textBox_rollPid_limits.Location = new System.Drawing.Point(191, 114);
      this.textBox_rollPid_limits.Name = "textBox_rollPid_limits";
      this.textBox_rollPid_limits.ReadOnly = true;
      this.textBox_rollPid_limits.Size = new System.Drawing.Size(112, 25);
      this.textBox_rollPid_limits.TabIndex = 26;
      // 
      // label13
      // 
      this.label13.AutoSize = true;
      this.label13.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label13.Location = new System.Drawing.Point(24, 147);
      this.label13.Name = "label13";
      this.label13.Size = new System.Drawing.Size(53, 17);
      this.label13.TabIndex = 25;
      this.label13.Text = "Time:";
      // 
      // label12
      // 
      this.label12.AutoSize = true;
      this.label12.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label12.Location = new System.Drawing.Point(6, 117);
      this.label12.Name = "label12";
      this.label12.Size = new System.Drawing.Size(71, 17);
      this.label12.TabIndex = 24;
      this.label12.Text = "Limits:";
      // 
      // numericUpDown_rollPid_time
      // 
      this.numericUpDown_rollPid_time.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_rollPid_time.Location = new System.Drawing.Point(83, 144);
      this.numericUpDown_rollPid_time.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_rollPid_time.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_rollPid_time.Name = "numericUpDown_rollPid_time";
      this.numericUpDown_rollPid_time.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_rollPid_time.TabIndex = 23;
      this.numericUpDown_rollPid_time.ValueChanged += new System.EventHandler(this.numericUpDown_rollPid_time_ValueChanged);
      // 
      // numericUpDown_rollPid_limits
      // 
      this.numericUpDown_rollPid_limits.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_rollPid_limits.Increment = new decimal(new int[] {
            2,
            0,
            0,
            0});
      this.numericUpDown_rollPid_limits.Location = new System.Drawing.Point(83, 114);
      this.numericUpDown_rollPid_limits.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_rollPid_limits.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_rollPid_limits.Name = "numericUpDown_rollPid_limits";
      this.numericUpDown_rollPid_limits.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_rollPid_limits.TabIndex = 22;
      this.numericUpDown_rollPid_limits.ValueChanged += new System.EventHandler(this.numericUpDown_rollPid_limits_ValueChanged);
      // 
      // lb_d
      // 
      this.lb_d.AutoSize = true;
      this.lb_d.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.lb_d.Location = new System.Drawing.Point(51, 88);
      this.lb_d.Name = "lb_d";
      this.lb_d.Size = new System.Drawing.Size(26, 17);
      this.lb_d.TabIndex = 12;
      this.lb_d.Text = "D:";
      // 
      // lb_i
      // 
      this.lb_i.AutoSize = true;
      this.lb_i.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.lb_i.Location = new System.Drawing.Point(51, 58);
      this.lb_i.Name = "lb_i";
      this.lb_i.Size = new System.Drawing.Size(26, 17);
      this.lb_i.TabIndex = 11;
      this.lb_i.Text = "I:";
      // 
      // lb_p
      // 
      this.lb_p.AutoSize = true;
      this.lb_p.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.lb_p.Location = new System.Drawing.Point(51, 30);
      this.lb_p.Name = "lb_p";
      this.lb_p.Size = new System.Drawing.Size(26, 17);
      this.lb_p.TabIndex = 10;
      this.lb_p.Text = "P:";
      // 
      // textBox_rollPid_kp
      // 
      this.textBox_rollPid_kp.Location = new System.Drawing.Point(191, 27);
      this.textBox_rollPid_kp.Name = "textBox_rollPid_kp";
      this.textBox_rollPid_kp.ReadOnly = true;
      this.textBox_rollPid_kp.Size = new System.Drawing.Size(112, 25);
      this.textBox_rollPid_kp.TabIndex = 13;
      // 
      // numericUpDown_rollPid_kp
      // 
      this.numericUpDown_rollPid_kp.DecimalPlaces = 2;
      this.numericUpDown_rollPid_kp.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_rollPid_kp.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_rollPid_kp.Location = new System.Drawing.Point(83, 27);
      this.numericUpDown_rollPid_kp.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_rollPid_kp.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_rollPid_kp.Name = "numericUpDown_rollPid_kp";
      this.numericUpDown_rollPid_kp.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_rollPid_kp.TabIndex = 6;
      this.numericUpDown_rollPid_kp.ValueChanged += new System.EventHandler(this.numericUpDown_pR_ValueChanged);
      // 
      // numericUpDown_rollPid_ki
      // 
      this.numericUpDown_rollPid_ki.DecimalPlaces = 2;
      this.numericUpDown_rollPid_ki.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
      this.numericUpDown_rollPid_ki.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_rollPid_ki.Location = new System.Drawing.Point(83, 55);
      this.numericUpDown_rollPid_ki.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_rollPid_ki.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_rollPid_ki.Name = "numericUpDown_rollPid_ki";
      this.numericUpDown_rollPid_ki.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_rollPid_ki.TabIndex = 5;
      this.numericUpDown_rollPid_ki.ValueChanged += new System.EventHandler(this.numericUpDown_iR_ValueChanged);
      // 
      // numericUpDown_rollPid_kd
      // 
      this.numericUpDown_rollPid_kd.DecimalPlaces = 2;
      this.numericUpDown_rollPid_kd.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
      this.numericUpDown_rollPid_kd.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_rollPid_kd.Location = new System.Drawing.Point(83, 84);
      this.numericUpDown_rollPid_kd.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_rollPid_kd.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_rollPid_kd.Name = "numericUpDown_rollPid_kd";
      this.numericUpDown_rollPid_kd.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_rollPid_kd.TabIndex = 4;
      this.numericUpDown_rollPid_kd.ValueChanged += new System.EventHandler(this.numericUpDown_dR_ValueChanged);
      // 
      // textBox_rollPid_ki
      // 
      this.textBox_rollPid_ki.Location = new System.Drawing.Point(191, 56);
      this.textBox_rollPid_ki.Name = "textBox_rollPid_ki";
      this.textBox_rollPid_ki.ReadOnly = true;
      this.textBox_rollPid_ki.Size = new System.Drawing.Size(112, 25);
      this.textBox_rollPid_ki.TabIndex = 15;
      // 
      // textBox_rollPid_kd
      // 
      this.textBox_rollPid_kd.Location = new System.Drawing.Point(191, 85);
      this.textBox_rollPid_kd.Name = "textBox_rollPid_kd";
      this.textBox_rollPid_kd.ReadOnly = true;
      this.textBox_rollPid_kd.Size = new System.Drawing.Size(112, 25);
      this.textBox_rollPid_kd.TabIndex = 14;
      // 
      // Pitch
      // 
      this.Pitch.BackColor = System.Drawing.Color.DimGray;
      this.Pitch.Controls.Add(this.groupBox5);
      this.Pitch.Location = new System.Drawing.Point(4, 26);
      this.Pitch.Name = "Pitch";
      this.Pitch.Padding = new System.Windows.Forms.Padding(3);
      this.Pitch.Size = new System.Drawing.Size(347, 183);
      this.Pitch.TabIndex = 1;
      this.Pitch.Text = "Pitch";
      // 
      // groupBox5
      // 
      this.groupBox5.BackColor = System.Drawing.Color.DimGray;
      this.groupBox5.Controls.Add(this.textBox_pitchPid_time);
      this.groupBox5.Controls.Add(this.textBox_pitchPid_limits);
      this.groupBox5.Controls.Add(this.label9);
      this.groupBox5.Controls.Add(this.label10);
      this.groupBox5.Controls.Add(this.numericUpDown_pitchPid_time);
      this.groupBox5.Controls.Add(this.numericUpDown_pitchPid_limits);
      this.groupBox5.Controls.Add(this.label3);
      this.groupBox5.Controls.Add(this.label4);
      this.groupBox5.Controls.Add(this.label16);
      this.groupBox5.Controls.Add(this.textBox_pitchPid_kp);
      this.groupBox5.Controls.Add(this.numericUpDown_pitchPid_kp);
      this.groupBox5.Controls.Add(this.numericUpDown_pitchPid_ki);
      this.groupBox5.Controls.Add(this.numericUpDown_pitchPid_kd);
      this.groupBox5.Controls.Add(this.textBox_pitchPid_ki);
      this.groupBox5.Controls.Add(this.textBox_pitchPid_kd);
      this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
      this.groupBox5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.groupBox5.Location = new System.Drawing.Point(3, 3);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new System.Drawing.Size(341, 177);
      this.groupBox5.TabIndex = 43;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "PID PITCH:";
      // 
      // textBox_pitchPid_time
      // 
      this.textBox_pitchPid_time.Location = new System.Drawing.Point(191, 142);
      this.textBox_pitchPid_time.Name = "textBox_pitchPid_time";
      this.textBox_pitchPid_time.Size = new System.Drawing.Size(112, 25);
      this.textBox_pitchPid_time.TabIndex = 33;
      // 
      // textBox_pitchPid_limits
      // 
      this.textBox_pitchPid_limits.Location = new System.Drawing.Point(191, 113);
      this.textBox_pitchPid_limits.Name = "textBox_pitchPid_limits";
      this.textBox_pitchPid_limits.Size = new System.Drawing.Size(112, 25);
      this.textBox_pitchPid_limits.TabIndex = 32;
      // 
      // label9
      // 
      this.label9.AutoSize = true;
      this.label9.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label9.Location = new System.Drawing.Point(24, 146);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(53, 17);
      this.label9.TabIndex = 31;
      this.label9.Text = "Time:";
      // 
      // label10
      // 
      this.label10.AutoSize = true;
      this.label10.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label10.Location = new System.Drawing.Point(6, 116);
      this.label10.Name = "label10";
      this.label10.Size = new System.Drawing.Size(71, 17);
      this.label10.TabIndex = 30;
      this.label10.Text = "Limits:";
      // 
      // numericUpDown_pitchPid_time
      // 
      this.numericUpDown_pitchPid_time.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_pitchPid_time.Location = new System.Drawing.Point(83, 143);
      this.numericUpDown_pitchPid_time.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_time.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_pitchPid_time.Name = "numericUpDown_pitchPid_time";
      this.numericUpDown_pitchPid_time.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_pitchPid_time.TabIndex = 29;
      this.numericUpDown_pitchPid_time.ValueChanged += new System.EventHandler(this.numericUpDown_pitchPid_time_ValueChanged);
      // 
      // numericUpDown_pitchPid_limits
      // 
      this.numericUpDown_pitchPid_limits.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_pitchPid_limits.Increment = new decimal(new int[] {
            2,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_limits.Location = new System.Drawing.Point(83, 113);
      this.numericUpDown_pitchPid_limits.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_limits.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_pitchPid_limits.Name = "numericUpDown_pitchPid_limits";
      this.numericUpDown_pitchPid_limits.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_pitchPid_limits.TabIndex = 28;
      this.numericUpDown_pitchPid_limits.ValueChanged += new System.EventHandler(this.numericUpDown_pitchPid_limits_ValueChanged);
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label3.Location = new System.Drawing.Point(51, 85);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(26, 17);
      this.label3.TabIndex = 12;
      this.label3.Text = "D:";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label4.Location = new System.Drawing.Point(51, 55);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(26, 17);
      this.label4.TabIndex = 11;
      this.label4.Text = "I:";
      // 
      // label16
      // 
      this.label16.AutoSize = true;
      this.label16.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label16.Location = new System.Drawing.Point(51, 27);
      this.label16.Name = "label16";
      this.label16.Size = new System.Drawing.Size(26, 17);
      this.label16.TabIndex = 10;
      this.label16.Text = "P:";
      // 
      // textBox_pitchPid_kp
      // 
      this.textBox_pitchPid_kp.Location = new System.Drawing.Point(191, 24);
      this.textBox_pitchPid_kp.Name = "textBox_pitchPid_kp";
      this.textBox_pitchPid_kp.Size = new System.Drawing.Size(112, 25);
      this.textBox_pitchPid_kp.TabIndex = 13;
      // 
      // numericUpDown_pitchPid_kp
      // 
      this.numericUpDown_pitchPid_kp.DecimalPlaces = 2;
      this.numericUpDown_pitchPid_kp.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.numericUpDown_pitchPid_kp.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_pitchPid_kp.Location = new System.Drawing.Point(83, 24);
      this.numericUpDown_pitchPid_kp.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_kp.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_pitchPid_kp.Name = "numericUpDown_pitchPid_kp";
      this.numericUpDown_pitchPid_kp.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_pitchPid_kp.TabIndex = 6;
      this.numericUpDown_pitchPid_kp.ValueChanged += new System.EventHandler(this.numericUpDown_pPitch_ValueChanged);
      // 
      // numericUpDown_pitchPid_ki
      // 
      this.numericUpDown_pitchPid_ki.DecimalPlaces = 2;
      this.numericUpDown_pitchPid_ki.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
      this.numericUpDown_pitchPid_ki.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_pitchPid_ki.Location = new System.Drawing.Point(83, 52);
      this.numericUpDown_pitchPid_ki.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_ki.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_pitchPid_ki.Name = "numericUpDown_pitchPid_ki";
      this.numericUpDown_pitchPid_ki.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_pitchPid_ki.TabIndex = 5;
      this.numericUpDown_pitchPid_ki.ValueChanged += new System.EventHandler(this.numericUpDown_iPitch_ValueChanged);
      // 
      // numericUpDown_pitchPid_kd
      // 
      this.numericUpDown_pitchPid_kd.DecimalPlaces = 2;
      this.numericUpDown_pitchPid_kd.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
      this.numericUpDown_pitchPid_kd.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numericUpDown_pitchPid_kd.Location = new System.Drawing.Point(83, 81);
      this.numericUpDown_pitchPid_kd.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
      this.numericUpDown_pitchPid_kd.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
      this.numericUpDown_pitchPid_kd.Name = "numericUpDown_pitchPid_kd";
      this.numericUpDown_pitchPid_kd.Size = new System.Drawing.Size(102, 24);
      this.numericUpDown_pitchPid_kd.TabIndex = 4;
      this.numericUpDown_pitchPid_kd.ValueChanged += new System.EventHandler(this.numericUpDown_dPitch_ValueChanged);
      // 
      // textBox_pitchPid_ki
      // 
      this.textBox_pitchPid_ki.Location = new System.Drawing.Point(191, 53);
      this.textBox_pitchPid_ki.Name = "textBox_pitchPid_ki";
      this.textBox_pitchPid_ki.Size = new System.Drawing.Size(112, 25);
      this.textBox_pitchPid_ki.TabIndex = 15;
      // 
      // textBox_pitchPid_kd
      // 
      this.textBox_pitchPid_kd.Location = new System.Drawing.Point(191, 82);
      this.textBox_pitchPid_kd.Name = "textBox_pitchPid_kd";
      this.textBox_pitchPid_kd.Size = new System.Drawing.Size(112, 25);
      this.textBox_pitchPid_kd.TabIndex = 14;
      // 
      // GPS
      // 
      this.GPS.BackColor = System.Drawing.Color.DimGray;
      this.GPS.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.GPS.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.GPS.Controls.Add(this.gMap);
      this.GPS.Controls.Add(this.headingIndicatorInstrumentControl1);
      this.GPS.Controls.Add(this.attitudeIndicatorInstrumentControl1);
      this.GPS.ImageIndex = 0;
      this.GPS.Location = new System.Drawing.Point(4, 57);
      this.GPS.Name = "GPS";
      this.GPS.Padding = new System.Windows.Forms.Padding(3);
      this.GPS.Size = new System.Drawing.Size(1213, 740);
      this.GPS.TabIndex = 2;
      // 
      // gMap
      // 
      this.gMap.Bearing = 0F;
      this.gMap.CanDragMap = true;
      this.gMap.GrayScaleMode = false;
      this.gMap.LevelsKeepInMemmory = 5;
      this.gMap.Location = new System.Drawing.Point(406, 40);
      this.gMap.MarkersEnabled = true;
      this.gMap.MaxZoom = 18;
      this.gMap.MinZoom = 2;
      this.gMap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.ViewCenter;
      this.gMap.Name = "gMap";
      this.gMap.NegativeMode = false;
      this.gMap.PolygonsEnabled = true;
      this.gMap.RetryLoadTile = 0;
      this.gMap.RoutesEnabled = true;
      this.gMap.ShowTileGridLines = false;
      this.gMap.Size = new System.Drawing.Size(296, 246);
      this.gMap.TabIndex = 20;
      this.gMap.Zoom = 16D;
      // 
      // headingIndicatorInstrumentControl1
      // 
      this.headingIndicatorInstrumentControl1.Location = new System.Drawing.Point(6, 342);
      this.headingIndicatorInstrumentControl1.Name = "headingIndicatorInstrumentControl1";
      this.headingIndicatorInstrumentControl1.Size = new System.Drawing.Size(338, 341);
      this.headingIndicatorInstrumentControl1.TabIndex = 19;
      this.headingIndicatorInstrumentControl1.Text = "headingIndicatorInstrumentControl1";
      // 
      // attitudeIndicatorInstrumentControl1
      // 
      this.attitudeIndicatorInstrumentControl1.Location = new System.Drawing.Point(6, 6);
      this.attitudeIndicatorInstrumentControl1.Name = "attitudeIndicatorInstrumentControl1";
      this.attitudeIndicatorInstrumentControl1.Size = new System.Drawing.Size(338, 348);
      this.attitudeIndicatorInstrumentControl1.TabIndex = 1;
      this.attitudeIndicatorInstrumentControl1.Text = "attitudeIndicatorInstrumentControl1";
      // 
      // Console
      // 
      this.Console.BackColor = System.Drawing.Color.DimGray;
      this.Console.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.Console.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.Console.Controls.Add(this.textBox_sendingStream2);
      this.Console.Controls.Add(this.label14);
      this.Console.Controls.Add(this.tabControl_socket_serial);
      this.Console.Controls.Add(this.button_clearSerial);
      this.Console.ForeColor = System.Drawing.SystemColors.HighlightText;
      this.Console.ImageIndex = 1;
      this.Console.Location = new System.Drawing.Point(4, 57);
      this.Console.Name = "Console";
      this.Console.Padding = new System.Windows.Forms.Padding(3);
      this.Console.Size = new System.Drawing.Size(1213, 740);
      this.Console.TabIndex = 1;
      // 
      // textBox_sendingStream2
      // 
      this.textBox_sendingStream2.Location = new System.Drawing.Point(92, 10);
      this.textBox_sendingStream2.Name = "textBox_sendingStream2";
      this.textBox_sendingStream2.ReadOnly = true;
      this.textBox_sendingStream2.Size = new System.Drawing.Size(1110, 25);
      this.textBox_sendingStream2.TabIndex = 51;
      // 
      // label14
      // 
      this.label14.AutoSize = true;
      this.label14.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
      this.label14.Location = new System.Drawing.Point(7, 13);
      this.label14.Name = "label14";
      this.label14.Size = new System.Drawing.Size(80, 17);
      this.label14.TabIndex = 52;
      this.label14.Text = "Sending:";
      // 
      // tabControl_socket_serial
      // 
      this.tabControl_socket_serial.Controls.Add(this.Socket);
      this.tabControl_socket_serial.Controls.Add(this.Serial);
      this.tabControl_socket_serial.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.tabControl_socket_serial.Location = new System.Drawing.Point(3, 70);
      this.tabControl_socket_serial.Name = "tabControl_socket_serial";
      this.tabControl_socket_serial.SelectedIndex = 0;
      this.tabControl_socket_serial.Size = new System.Drawing.Size(1203, 663);
      this.tabControl_socket_serial.TabIndex = 30;
      // 
      // Socket
      // 
      this.Socket.Controls.Add(this.textBox_socketRead);
      this.Socket.Location = new System.Drawing.Point(4, 26);
      this.Socket.Name = "Socket";
      this.Socket.Padding = new System.Windows.Forms.Padding(3);
      this.Socket.Size = new System.Drawing.Size(1195, 633);
      this.Socket.TabIndex = 1;
      this.Socket.Text = "Socket";
      this.Socket.UseVisualStyleBackColor = true;
      // 
      // textBox_socketRead
      // 
      this.textBox_socketRead.Dock = System.Windows.Forms.DockStyle.Fill;
      this.textBox_socketRead.Location = new System.Drawing.Point(3, 3);
      this.textBox_socketRead.Multiline = true;
      this.textBox_socketRead.Name = "textBox_socketRead";
      this.textBox_socketRead.ReadOnly = true;
      this.textBox_socketRead.Size = new System.Drawing.Size(1189, 627);
      this.textBox_socketRead.TabIndex = 26;
      // 
      // Serial
      // 
      this.Serial.Controls.Add(this.textBox_serialRead);
      this.Serial.Location = new System.Drawing.Point(4, 26);
      this.Serial.Name = "Serial";
      this.Serial.Padding = new System.Windows.Forms.Padding(3);
      this.Serial.Size = new System.Drawing.Size(1195, 633);
      this.Serial.TabIndex = 0;
      this.Serial.Text = "Serial";
      this.Serial.UseVisualStyleBackColor = true;
      // 
      // textBox_serialRead
      // 
      this.textBox_serialRead.Dock = System.Windows.Forms.DockStyle.Fill;
      this.textBox_serialRead.Location = new System.Drawing.Point(3, 3);
      this.textBox_serialRead.Multiline = true;
      this.textBox_serialRead.Name = "textBox_serialRead";
      this.textBox_serialRead.ReadOnly = true;
      this.textBox_serialRead.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBox_serialRead.Size = new System.Drawing.Size(1189, 627);
      this.textBox_serialRead.TabIndex = 23;
      // 
      // button_clearSerial
      // 
      this.button_clearSerial.ForeColor = System.Drawing.SystemColors.Desktop;
      this.button_clearSerial.Location = new System.Drawing.Point(1072, 41);
      this.button_clearSerial.Name = "button_clearSerial";
      this.button_clearSerial.Size = new System.Drawing.Size(134, 23);
      this.button_clearSerial.TabIndex = 29;
      this.button_clearSerial.Text = "Clear serial";
      this.button_clearSerial.UseVisualStyleBackColor = true;
      this.button_clearSerial.Click += new System.EventHandler(this.button_clearSerial_Click);
      // 
      // IMU
      // 
      this.IMU.BackColor = System.Drawing.Color.DimGray;
      this.IMU.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
      this.IMU.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.IMU.Controls.Add(this.zedGraphControl2);
      this.IMU.Controls.Add(this.label8);
      this.IMU.Controls.Add(this.zedGraphControl1);
      this.IMU.Controls.Add(this.groupBox3);
      this.IMU.ForeColor = System.Drawing.SystemColors.Window;
      this.IMU.ImageIndex = 2;
      this.IMU.Location = new System.Drawing.Point(4, 57);
      this.IMU.Name = "IMU";
      this.IMU.Size = new System.Drawing.Size(1213, 740);
      this.IMU.TabIndex = 0;
      // 
      // zedGraphControl2
      // 
      this.zedGraphControl2.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.zedGraphControl2.AutoSize = true;
      this.zedGraphControl2.Location = new System.Drawing.Point(2, 366);
      this.zedGraphControl2.Name = "zedGraphControl2";
      this.zedGraphControl2.ScrollGrace = 0D;
      this.zedGraphControl2.ScrollMaxX = 0D;
      this.zedGraphControl2.ScrollMaxY = 0D;
      this.zedGraphControl2.ScrollMaxY2 = 0D;
      this.zedGraphControl2.ScrollMinX = 0D;
      this.zedGraphControl2.ScrollMinY = 0D;
      this.zedGraphControl2.ScrollMinY2 = 0D;
      this.zedGraphControl2.Size = new System.Drawing.Size(920, 364);
      this.zedGraphControl2.TabIndex = 18;
      // 
      // label8
      // 
      this.label8.AccessibleName = "lb_axisValie";
      this.label8.AutoSize = true;
      this.label8.Location = new System.Drawing.Point(721, 12);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(0, 17);
      this.label8.TabIndex = 15;
      // 
      // zedGraphControl1
      // 
      this.zedGraphControl1.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.zedGraphControl1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
      this.zedGraphControl1.BackColor = System.Drawing.Color.LightGray;
      this.zedGraphControl1.ForeColor = System.Drawing.SystemColors.Control;
      this.zedGraphControl1.Location = new System.Drawing.Point(2, 3);
      this.zedGraphControl1.Name = "zedGraphControl1";
      this.zedGraphControl1.ScrollGrace = 0D;
      this.zedGraphControl1.ScrollMaxX = 0D;
      this.zedGraphControl1.ScrollMaxY = 0D;
      this.zedGraphControl1.ScrollMaxY2 = 0D;
      this.zedGraphControl1.ScrollMinX = 0D;
      this.zedGraphControl1.ScrollMinY = 0D;
      this.zedGraphControl1.ScrollMinY2 = 0D;
      this.zedGraphControl1.Size = new System.Drawing.Size(921, 357);
      this.zedGraphControl1.TabIndex = 0;
      // 
      // groupBox3
      // 
      this.groupBox3.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.groupBox3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
      this.groupBox3.Controls.Add(this.tabControl_graphControl);
      this.groupBox3.ForeColor = System.Drawing.SystemColors.Control;
      this.groupBox3.Location = new System.Drawing.Point(928, 3);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new System.Drawing.Size(275, 727);
      this.groupBox3.TabIndex = 21;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Graph settings:";
      // 
      // tabControl_graphControl
      // 
      this.tabControl_graphControl.Controls.Add(this.tabPage4);
      this.tabControl_graphControl.Controls.Add(this.tabPage5);
      this.tabControl_graphControl.Location = new System.Drawing.Point(3, 21);
      this.tabControl_graphControl.Name = "tabControl_graphControl";
      this.tabControl_graphControl.SelectedIndex = 0;
      this.tabControl_graphControl.Size = new System.Drawing.Size(269, 703);
      this.tabControl_graphControl.TabIndex = 29;
      this.tabControl_graphControl.TabStop = false;
      // 
      // tabPage4
      // 
      this.tabPage4.Controls.Add(this.checkedListBox_graph1);
      this.tabPage4.Location = new System.Drawing.Point(4, 26);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
      this.tabPage4.Size = new System.Drawing.Size(261, 673);
      this.tabPage4.TabIndex = 0;
      this.tabPage4.Text = "Graph1";
      this.tabPage4.UseVisualStyleBackColor = true;
      // 
      // checkedListBox_graph1
      // 
      this.checkedListBox_graph1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.checkedListBox_graph1.FormattingEnabled = true;
      this.checkedListBox_graph1.Items.AddRange(new object[] {
            "pTr",
            "iTr",
            "dTr",
            "roll",
            "pitch",
            "yaw",
            "bl",
            "br",
            "fl",
            "fr",
            "pTp",
            "iTp",
            "dTp"});
      this.checkedListBox_graph1.Location = new System.Drawing.Point(3, 3);
      this.checkedListBox_graph1.Name = "checkedListBox_graph1";
      this.checkedListBox_graph1.Size = new System.Drawing.Size(255, 667);
      this.checkedListBox_graph1.TabIndex = 28;
      this.checkedListBox_graph1.TabStop = false;
      // 
      // tabPage5
      // 
      this.tabPage5.Controls.Add(this.checkedListBox_graph2);
      this.tabPage5.Location = new System.Drawing.Point(4, 26);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
      this.tabPage5.Size = new System.Drawing.Size(261, 673);
      this.tabPage5.TabIndex = 1;
      this.tabPage5.Text = "Graph2";
      this.tabPage5.UseVisualStyleBackColor = true;
      // 
      // checkedListBox_graph2
      // 
      this.checkedListBox_graph2.Dock = System.Windows.Forms.DockStyle.Fill;
      this.checkedListBox_graph2.FormattingEnabled = true;
      this.checkedListBox_graph2.Items.AddRange(new object[] {
            "pTr",
            "iTr",
            "dTr",
            "roll",
            "pitch",
            "yaw",
            "bl",
            "br",
            "fl",
            "fr",
            "pTp",
            "iTp",
            "dTp"});
      this.checkedListBox_graph2.Location = new System.Drawing.Point(3, 3);
      this.checkedListBox_graph2.Name = "checkedListBox_graph2";
      this.checkedListBox_graph2.Size = new System.Drawing.Size(255, 667);
      this.checkedListBox_graph2.TabIndex = 29;
      this.checkedListBox_graph2.TabStop = false;
      // 
      // tabControl_mainControl
      // 
      this.tabControl_mainControl.Controls.Add(this.Settings);
      this.tabControl_mainControl.Controls.Add(this.Console);
      this.tabControl_mainControl.Controls.Add(this.IMU);
      this.tabControl_mainControl.Controls.Add(this.GPS);
      this.tabControl_mainControl.Controls.Add(this.Joystick);
      this.tabControl_mainControl.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tabControl_mainControl.Font = new System.Drawing.Font("Lucida Sans Typewriter", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.tabControl_mainControl.ImageList = this.tabControlImageList;
      this.tabControl_mainControl.ImeMode = System.Windows.Forms.ImeMode.AlphaFull;
      this.tabControl_mainControl.Location = new System.Drawing.Point(0, 0);
      this.tabControl_mainControl.Name = "tabControl_mainControl";
      this.tabControl_mainControl.SelectedIndex = 0;
      this.tabControl_mainControl.Size = new System.Drawing.Size(1221, 801);
      this.tabControl_mainControl.TabIndex = 2;
      // 
      // Joystick
      // 
      this.Joystick.BackColor = System.Drawing.Color.DimGray;
      this.Joystick.Controls.Add(this.label15);
      this.Joystick.Controls.Add(this.textBox_joystick_yawVal);
      this.Joystick.Controls.Add(this.progressBar_joystick_yaw);
      this.Joystick.Controls.Add(this.button_joystick_connect);
      this.Joystick.Controls.Add(this.textBox_joystick_rollVal);
      this.Joystick.Controls.Add(this.textBox_joystick_pitchVal);
      this.Joystick.Controls.Add(this.textBox_joystick_throttleVal);
      this.Joystick.Controls.Add(this.btn_joystick_calibrate);
      this.Joystick.Controls.Add(this.label26);
      this.Joystick.Controls.Add(this.label25);
      this.Joystick.Controls.Add(this.label24);
      this.Joystick.Controls.Add(this.progressBar_joystick_roll);
      this.Joystick.Controls.Add(this.progressBar_joystick_pitch);
      this.Joystick.Controls.Add(this.progressBar_joystick_throttle);
      this.Joystick.Controls.Add(this.label21);
      this.Joystick.Controls.Add(this.label_joystick_connection);
      this.Joystick.Location = new System.Drawing.Point(4, 57);
      this.Joystick.Name = "Joystick";
      this.Joystick.Padding = new System.Windows.Forms.Padding(3);
      this.Joystick.Size = new System.Drawing.Size(1213, 740);
      this.Joystick.TabIndex = 4;
      this.Joystick.Text = "Joystick";
      // 
      // label15
      // 
      this.label15.AutoSize = true;
      this.label15.Location = new System.Drawing.Point(84, 113);
      this.label15.Name = "label15";
      this.label15.Size = new System.Drawing.Size(44, 17);
      this.label15.TabIndex = 33;
      this.label15.Text = "Yaw:";
      // 
      // textBox_joystick_yawVal
      // 
      this.textBox_joystick_yawVal.Location = new System.Drawing.Point(560, 110);
      this.textBox_joystick_yawVal.Name = "textBox_joystick_yawVal";
      this.textBox_joystick_yawVal.ReadOnly = true;
      this.textBox_joystick_yawVal.Size = new System.Drawing.Size(100, 25);
      this.textBox_joystick_yawVal.TabIndex = 32;
      // 
      // progressBar_joystick_yaw
      // 
      this.progressBar_joystick_yaw.Location = new System.Drawing.Point(134, 112);
      this.progressBar_joystick_yaw.Maximum = 410;
      this.progressBar_joystick_yaw.Name = "progressBar_joystick_yaw";
      this.progressBar_joystick_yaw.Size = new System.Drawing.Size(420, 23);
      this.progressBar_joystick_yaw.TabIndex = 31;
      // 
      // button_joystick_connect
      // 
      this.button_joystick_connect.Location = new System.Drawing.Point(1058, 41);
      this.button_joystick_connect.Name = "button_joystick_connect";
      this.button_joystick_connect.Size = new System.Drawing.Size(113, 59);
      this.button_joystick_connect.TabIndex = 30;
      this.button_joystick_connect.Text = "Joystick Connect";
      this.button_joystick_connect.UseVisualStyleBackColor = true;
      this.button_joystick_connect.Click += new System.EventHandler(this.button_joystick_connect_Click);
      // 
      // textBox_joystick_rollVal
      // 
      this.textBox_joystick_rollVal.Location = new System.Drawing.Point(560, 50);
      this.textBox_joystick_rollVal.Name = "textBox_joystick_rollVal";
      this.textBox_joystick_rollVal.ReadOnly = true;
      this.textBox_joystick_rollVal.Size = new System.Drawing.Size(100, 25);
      this.textBox_joystick_rollVal.TabIndex = 29;
      // 
      // textBox_joystick_pitchVal
      // 
      this.textBox_joystick_pitchVal.Location = new System.Drawing.Point(560, 81);
      this.textBox_joystick_pitchVal.Name = "textBox_joystick_pitchVal";
      this.textBox_joystick_pitchVal.ReadOnly = true;
      this.textBox_joystick_pitchVal.Size = new System.Drawing.Size(100, 25);
      this.textBox_joystick_pitchVal.TabIndex = 28;
      // 
      // textBox_joystick_throttleVal
      // 
      this.textBox_joystick_throttleVal.Location = new System.Drawing.Point(560, 19);
      this.textBox_joystick_throttleVal.Name = "textBox_joystick_throttleVal";
      this.textBox_joystick_throttleVal.ReadOnly = true;
      this.textBox_joystick_throttleVal.Size = new System.Drawing.Size(100, 25);
      this.textBox_joystick_throttleVal.TabIndex = 27;
      // 
      // btn_joystick_calibrate
      // 
      this.btn_joystick_calibrate.Location = new System.Drawing.Point(1058, 106);
      this.btn_joystick_calibrate.Name = "btn_joystick_calibrate";
      this.btn_joystick_calibrate.Size = new System.Drawing.Size(113, 59);
      this.btn_joystick_calibrate.TabIndex = 16;
      this.btn_joystick_calibrate.Text = "Calibrate";
      this.btn_joystick_calibrate.UseVisualStyleBackColor = true;
      this.btn_joystick_calibrate.Click += new System.EventHandler(this.btn_joystick_calibrate_Click);
      // 
      // label26
      // 
      this.label26.AutoSize = true;
      this.label26.Location = new System.Drawing.Point(39, 27);
      this.label26.Name = "label26";
      this.label26.Size = new System.Drawing.Size(89, 17);
      this.label26.TabIndex = 15;
      this.label26.Text = "Throttle:";
      // 
      // label25
      // 
      this.label25.AutoSize = true;
      this.label25.Location = new System.Drawing.Point(75, 56);
      this.label25.Name = "label25";
      this.label25.Size = new System.Drawing.Size(53, 17);
      this.label25.TabIndex = 14;
      this.label25.Text = "Roll:";
      // 
      // label24
      // 
      this.label24.AutoSize = true;
      this.label24.Location = new System.Drawing.Point(66, 85);
      this.label24.Name = "label24";
      this.label24.Size = new System.Drawing.Size(62, 17);
      this.label24.TabIndex = 13;
      this.label24.Text = "Pitch:";
      // 
      // progressBar_joystick_roll
      // 
      this.progressBar_joystick_roll.Location = new System.Drawing.Point(134, 50);
      this.progressBar_joystick_roll.Maximum = 300;
      this.progressBar_joystick_roll.Name = "progressBar_joystick_roll";
      this.progressBar_joystick_roll.Size = new System.Drawing.Size(420, 23);
      this.progressBar_joystick_roll.TabIndex = 12;
      // 
      // progressBar_joystick_pitch
      // 
      this.progressBar_joystick_pitch.Location = new System.Drawing.Point(134, 81);
      this.progressBar_joystick_pitch.Maximum = 300;
      this.progressBar_joystick_pitch.Name = "progressBar_joystick_pitch";
      this.progressBar_joystick_pitch.Size = new System.Drawing.Size(420, 23);
      this.progressBar_joystick_pitch.TabIndex = 11;
      // 
      // progressBar_joystick_throttle
      // 
      this.progressBar_joystick_throttle.Location = new System.Drawing.Point(134, 21);
      this.progressBar_joystick_throttle.Maximum = 2200;
      this.progressBar_joystick_throttle.Minimum = 1000;
      this.progressBar_joystick_throttle.Name = "progressBar_joystick_throttle";
      this.progressBar_joystick_throttle.Size = new System.Drawing.Size(420, 23);
      this.progressBar_joystick_throttle.TabIndex = 9;
      this.progressBar_joystick_throttle.Value = 1000;
      // 
      // label21
      // 
      this.label21.AutoSize = true;
      this.label21.Location = new System.Drawing.Point(876, 21);
      this.label21.Name = "label21";
      this.label21.Size = new System.Drawing.Size(152, 17);
      this.label21.TabIndex = 8;
      this.label21.Text = "Joystick status:";
      // 
      // label_joystick_connection
      // 
      this.label_joystick_connection.AutoSize = true;
      this.label_joystick_connection.Location = new System.Drawing.Point(1055, 21);
      this.label_joystick_connection.Name = "label_joystick_connection";
      this.label_joystick_connection.Size = new System.Drawing.Size(116, 17);
      this.label_joystick_connection.TabIndex = 7;
      this.label_joystick_connection.Text = "Disconnected";
      // 
      // status
      // 
      this.status.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.status.AutoSize = true;
      this.status.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.status.Location = new System.Drawing.Point(826, 19);
      this.status.Name = "status";
      this.status.Size = new System.Drawing.Size(48, 16);
      this.status.TabIndex = 12;
      this.status.Text = "Status:";
      // 
      // timer_socketReceive
      // 
      this.timer_socketReceive.Interval = 20;
      this.timer_socketReceive.Tick += new System.EventHandler(this.timer_socketReceive_Tick);
      // 
      // GUI
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.DarkGray;
      this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
      this.ClientSize = new System.Drawing.Size(1221, 801);
      this.Controls.Add(this.comboBox_Comports);
      this.Controls.Add(this.btn_disconnect);
      this.Controls.Add(this.btn_connect);
      this.Controls.Add(this.lb_connectionStatus);
      this.Controls.Add(this.status);
      this.Controls.Add(this.tabControl_mainControl);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Name = "GUI";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "ArduinoDebug";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.Settings.ResumeLayout(false);
      this.Settings.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.tabControl_pid.ResumeLayout(false);
      this.Roll.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_time)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_limits)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_kp)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_ki)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_rollPid_kd)).EndInit();
      this.Pitch.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_time)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_limits)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_kp)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_ki)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pitchPid_kd)).EndInit();
      this.GPS.ResumeLayout(false);
      this.Console.ResumeLayout(false);
      this.Console.PerformLayout();
      this.tabControl_socket_serial.ResumeLayout(false);
      this.Socket.ResumeLayout(false);
      this.Socket.PerformLayout();
      this.Serial.ResumeLayout(false);
      this.Serial.PerformLayout();
      this.IMU.ResumeLayout(false);
      this.IMU.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.tabControl_graphControl.ResumeLayout(false);
      this.tabPage4.ResumeLayout(false);
      this.tabPage5.ResumeLayout(false);
      this.tabControl_mainControl.ResumeLayout(false);
      this.Joystick.ResumeLayout(false);
      this.Joystick.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer joystickTimer;
        private System.Windows.Forms.Label lb_connectionStatus;
        private System.Windows.Forms.ComboBox comboBox_Comports;
        private System.Windows.Forms.ImageList tabControlImageList;
        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.Button btn_disconnect;
        private System.Windows.Forms.TabPage Settings;
        private System.Windows.Forms.CheckBox checkBox_sendSocket;
        private System.Windows.Forms.TabControl tabControl_pid;
        private System.Windows.Forms.TabPage Roll;
        private System.Windows.Forms.TabPage Pitch;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox textBox_pitchPid_kp;
        private System.Windows.Forms.NumericUpDown numericUpDown_pitchPid_kp;
        private System.Windows.Forms.NumericUpDown numericUpDown_pitchPid_ki;
        private System.Windows.Forms.NumericUpDown numericUpDown_pitchPid_kd;
        private System.Windows.Forms.TextBox textBox_pitchPid_ki;
        private System.Windows.Forms.TextBox textBox_pitchPid_kd;
        private System.Windows.Forms.CheckBox checkBox_sendDataToArduino;
        private System.Windows.Forms.TabPage GPS;
        private GMap.NET.WindowsForms.GMapControl gMap;
        private AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl headingIndicatorInstrumentControl1;
        private AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl attitudeIndicatorInstrumentControl1;
        private System.Windows.Forms.TabPage Console;
        private System.Windows.Forms.TabPage IMU;
        private ZedGraph.ZedGraphControl zedGraphControl2;
        private System.Windows.Forms.Label label8;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.TabControl tabControl_graphControl;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.CheckedListBox checkedListBox_graph1;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabControl tabControl_mainControl;
        private System.Windows.Forms.Label status;
        public System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TabPage Joystick;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lb_d;
        private System.Windows.Forms.Label lb_i;
        private System.Windows.Forms.Label lb_p;
        private System.Windows.Forms.TextBox textBox_rollPid_kp;
        private System.Windows.Forms.NumericUpDown numericUpDown_rollPid_kp;
        private System.Windows.Forms.NumericUpDown numericUpDown_rollPid_ki;
        private System.Windows.Forms.NumericUpDown numericUpDown_rollPid_kd;
        private System.Windows.Forms.TextBox textBox_rollPid_ki;
        private System.Windows.Forms.TextBox textBox_rollPid_kd;
        private System.Windows.Forms.CheckedListBox checkedListBox_graph2;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar progressBar_br;
        private System.Windows.Forms.ProgressBar progressBar_fl;
        private System.Windows.Forms.ProgressBar progressBar_fr;
        private System.Windows.Forms.ProgressBar progressBar_bl;
        private System.Windows.Forms.TextBox textBox_throttle;
        private System.Windows.Forms.TextBox textBox_bl;
        private System.Windows.Forms.TextBox textBox_br;
        private System.Windows.Forms.TextBox textBox_fl;
        private System.Windows.Forms.TextBox textBox_fr;
        private System.Windows.Forms.Button button_clearSerial;
        private System.Windows.Forms.Label label7;
        private AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl attitudeIndicatorInstrumentControl2;
        private AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl headingIndicatorInstrumentControl2;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.NumericUpDown numericUpDown_rollPid_time;
        private System.Windows.Forms.NumericUpDown numericUpDown_rollPid_limits;
        private System.Windows.Forms.TextBox textBox_rollPid_time;
        private System.Windows.Forms.TextBox textBox_rollPid_limits;
        private System.Windows.Forms.TextBox textBox_pitchPid_time;
        private System.Windows.Forms.TextBox textBox_pitchPid_limits;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown numericUpDown_pitchPid_time;
        private System.Windows.Forms.NumericUpDown numericUpDown_pitchPid_limits;
        private System.Windows.Forms.TextBox textBox_sendingStream1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TabControl tabControl_socket_serial;
        private System.Windows.Forms.TabPage Socket;
        private System.Windows.Forms.TextBox textBox_socketRead;
        private System.Windows.Forms.TabPage Serial;
        private System.Windows.Forms.TextBox textBox_serialRead;
        private System.Windows.Forms.TextBox textBox_sendingStream2;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBox_setpointPitch;
        private System.Windows.Forms.TextBox textBox_setpointRoll;
        private System.Windows.Forms.Label label_;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox textBox_calcRoll;
        private System.Windows.Forms.TextBox textBox_calcPitch;
        private System.Windows.Forms.CheckBox checkBox_stearingOn;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label_joystick_connection;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.ProgressBar progressBar_joystick_roll;
        private System.Windows.Forms.ProgressBar progressBar_joystick_pitch;
        private System.Windows.Forms.ProgressBar progressBar_joystick_throttle;
        private System.Windows.Forms.Button btn_joystick_calibrate;
        private System.Windows.Forms.TextBox textBox_joystick_rollVal;
        private System.Windows.Forms.TextBox textBox_joystick_pitchVal;
        private System.Windows.Forms.TextBox textBox_joystick_throttleVal;
        private System.Windows.Forms.Button button_joystick_connect;
        private System.Windows.Forms.Timer timer_socketReceive;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox textBox_joystick_yawVal;
        private System.Windows.Forms.ProgressBar progressBar_joystick_yaw;
    }
}

