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
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lb_connectionStatus = new System.Windows.Forms.Label();
            this.comboBox_Comports = new System.Windows.Forms.ComboBox();
            this.btn_serialDisconnect = new System.Windows.Forms.Button();
            this.btn_ConnectSerial = new System.Windows.Forms.Button();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.numericUpDown_stearingRatio = new System.Windows.Forms.NumericUpDown();
            this.btn_right = new System.Windows.Forms.Button();
            this.brn_down = new System.Windows.Forms.Button();
            this.btn_left = new System.Windows.Forms.Button();
            this.btn_up = new System.Windows.Forms.Button();
            this.headingIndicatorInstrumentControl2 = new AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl();
            this.attitudeIndicatorInstrumentControl2 = new AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_bl = new System.Windows.Forms.TextBox();
            this.textBox_br = new System.Windows.Forms.TextBox();
            this.textBox_fl = new System.Windows.Forms.TextBox();
            this.textBox_fr = new System.Windows.Forms.TextBox();
            this.textBox_e = new System.Windows.Forms.TextBox();
            this.trackBar_throttle = new System.Windows.Forms.TrackBar();
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
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.Roll = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lb_d = new System.Windows.Forms.Label();
            this.lb_i = new System.Windows.Forms.Label();
            this.lb_p = new System.Windows.Forms.Label();
            this.textBox_pR = new System.Windows.Forms.TextBox();
            this.textBox_dTr = new System.Windows.Forms.TextBox();
            this.textBox_pTr = new System.Windows.Forms.TextBox();
            this.numericUpDown_pR = new System.Windows.Forms.NumericUpDown();
            this.textBox_iTr = new System.Windows.Forms.TextBox();
            this.numericUpDown_iR = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_dR = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.textBox_iR = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_dR = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.Pitch = new System.Windows.Forms.TabPage();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.textBox_pP = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.numericUpDown_pPitch = new System.Windows.Forms.NumericUpDown();
            this.textBox11 = new System.Windows.Forms.TextBox();
            this.numericUpDown_iPitch = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_dPitch = new System.Windows.Forms.NumericUpDown();
            this.label17 = new System.Windows.Forms.Label();
            this.textBox_iP = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.textBox_dP = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.gMap = new GMap.NET.WindowsForms.GMapControl();
            this.headingIndicatorInstrumentControl1 = new AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl();
            this.attitudeIndicatorInstrumentControl1 = new AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button_clearSerial = new System.Windows.Forms.Button();
            this.SocketRead = new System.Windows.Forms.GroupBox();
            this.textBox_socketRead = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox_SerialPrint = new System.Windows.Forms.TextBox();
            this.IMU = new System.Windows.Forms.TabPage();
            this.zedGraphControl2 = new ZedGraph.ZedGraphControl();
            this.label8 = new System.Windows.Forms.Label();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tabControl3 = new System.Windows.Forms.TabControl();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.checkedListBox_graph1 = new System.Windows.Forms.CheckedListBox();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.checkedListBox_graph2 = new System.Windows.Forms.CheckedListBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.status = new System.Windows.Forms.Label();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_stearingRatio)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_throttle)).BeginInit();
            this.groupBox4.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.Roll.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_iR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_dR)).BeginInit();
            this.Pitch.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pPitch)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_iPitch)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_dPitch)).BeginInit();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SocketRead.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.IMU.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabControl3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabControl1.SuspendLayout();
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
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 40;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
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
            // btn_serialDisconnect
            // 
            this.btn_serialDisconnect.AccessibleRole = System.Windows.Forms.AccessibleRole.Sound;
            this.btn_serialDisconnect.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btn_serialDisconnect.BackColor = System.Drawing.Color.White;
            this.btn_serialDisconnect.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btn_serialDisconnect.BackgroundImage")));
            this.btn_serialDisconnect.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btn_serialDisconnect.Location = new System.Drawing.Point(1107, 5);
            this.btn_serialDisconnect.Name = "btn_serialDisconnect";
            this.btn_serialDisconnect.Size = new System.Drawing.Size(52, 46);
            this.btn_serialDisconnect.TabIndex = 1;
            this.btn_serialDisconnect.UseVisualStyleBackColor = false;
            this.btn_serialDisconnect.Click += new System.EventHandler(this.btn_serialDisconnect_Click);
            // 
            // btn_ConnectSerial
            // 
            this.btn_ConnectSerial.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btn_ConnectSerial.BackColor = System.Drawing.Color.White;
            this.btn_ConnectSerial.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btn_ConnectSerial.BackgroundImage")));
            this.btn_ConnectSerial.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btn_ConnectSerial.Location = new System.Drawing.Point(1165, 5);
            this.btn_ConnectSerial.Name = "btn_ConnectSerial";
            this.btn_ConnectSerial.Size = new System.Drawing.Size(49, 46);
            this.btn_ConnectSerial.TabIndex = 9;
            this.btn_ConnectSerial.UseVisualStyleBackColor = false;
            this.btn_ConnectSerial.Click += new System.EventHandler(this.btn_ConnectSerial_Click);
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.Color.DimGray;
            this.tabPage3.Controls.Add(this.numericUpDown_stearingRatio);
            this.tabPage3.Controls.Add(this.btn_right);
            this.tabPage3.Controls.Add(this.brn_down);
            this.tabPage3.Controls.Add(this.btn_left);
            this.tabPage3.Controls.Add(this.btn_up);
            this.tabPage3.Controls.Add(this.headingIndicatorInstrumentControl2);
            this.tabPage3.Controls.Add(this.attitudeIndicatorInstrumentControl2);
            this.tabPage3.Controls.Add(this.label7);
            this.tabPage3.Controls.Add(this.textBox_bl);
            this.tabPage3.Controls.Add(this.textBox_br);
            this.tabPage3.Controls.Add(this.textBox_fl);
            this.tabPage3.Controls.Add(this.textBox_fr);
            this.tabPage3.Controls.Add(this.textBox_e);
            this.tabPage3.Controls.Add(this.trackBar_throttle);
            this.tabPage3.Controls.Add(this.label6);
            this.tabPage3.Controls.Add(this.label5);
            this.tabPage3.Controls.Add(this.label2);
            this.tabPage3.Controls.Add(this.label1);
            this.tabPage3.Controls.Add(this.progressBar_br);
            this.tabPage3.Controls.Add(this.progressBar_fl);
            this.tabPage3.Controls.Add(this.progressBar_fr);
            this.tabPage3.Controls.Add(this.progressBar_bl);
            this.tabPage3.Controls.Add(this.groupBox4);
            this.tabPage3.Controls.Add(this.tabControl2);
            this.tabPage3.Location = new System.Drawing.Point(4, 57);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(1213, 740);
            this.tabPage3.TabIndex = 3;
            this.tabPage3.Text = "Settings";
            // 
            // numericUpDown_stearingRatio
            // 
            this.numericUpDown_stearingRatio.Location = new System.Drawing.Point(962, 460);
            this.numericUpDown_stearingRatio.Name = "numericUpDown_stearingRatio";
            this.numericUpDown_stearingRatio.Size = new System.Drawing.Size(120, 25);
            this.numericUpDown_stearingRatio.TabIndex = 49;
            this.numericUpDown_stearingRatio.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // btn_right
            // 
            this.btn_right.Location = new System.Drawing.Point(1059, 393);
            this.btn_right.Name = "btn_right";
            this.btn_right.Size = new System.Drawing.Size(75, 61);
            this.btn_right.TabIndex = 48;
            this.btn_right.Text = "RIGHT";
            this.btn_right.UseVisualStyleBackColor = true;
            this.btn_right.Click += new System.EventHandler(this.btn_right_Click);
            // 
            // brn_down
            // 
            this.brn_down.Location = new System.Drawing.Point(977, 393);
            this.brn_down.Name = "brn_down";
            this.brn_down.Size = new System.Drawing.Size(75, 61);
            this.brn_down.TabIndex = 47;
            this.brn_down.Text = "DOWN";
            this.brn_down.UseVisualStyleBackColor = true;
            this.brn_down.Click += new System.EventHandler(this.brn_down_Click);
            // 
            // btn_left
            // 
            this.btn_left.Location = new System.Drawing.Point(896, 393);
            this.btn_left.Name = "btn_left";
            this.btn_left.Size = new System.Drawing.Size(75, 61);
            this.btn_left.TabIndex = 46;
            this.btn_left.Text = "LEFT";
            this.btn_left.UseVisualStyleBackColor = true;
            this.btn_left.Click += new System.EventHandler(this.btn_left_Click);
            // 
            // btn_up
            // 
            this.btn_up.Location = new System.Drawing.Point(977, 326);
            this.btn_up.Name = "btn_up";
            this.btn_up.Size = new System.Drawing.Size(75, 61);
            this.btn_up.TabIndex = 45;
            this.btn_up.Text = "UP";
            this.btn_up.UseVisualStyleBackColor = true;
            this.btn_up.Click += new System.EventHandler(this.btn_up_Click);
            // 
            // headingIndicatorInstrumentControl2
            // 
            this.headingIndicatorInstrumentControl2.Location = new System.Drawing.Point(364, 269);
            this.headingIndicatorInstrumentControl2.Name = "headingIndicatorInstrumentControl2";
            this.headingIndicatorInstrumentControl2.Size = new System.Drawing.Size(338, 341);
            this.headingIndicatorInstrumentControl2.TabIndex = 44;
            this.headingIndicatorInstrumentControl2.Text = "headingIndicatorInstrumentControl2";
            // 
            // attitudeIndicatorInstrumentControl2
            // 
            this.attitudeIndicatorInstrumentControl2.Location = new System.Drawing.Point(7, 269);
            this.attitudeIndicatorInstrumentControl2.Name = "attitudeIndicatorInstrumentControl2";
            this.attitudeIndicatorInstrumentControl2.Size = new System.Drawing.Size(338, 348);
            this.attitudeIndicatorInstrumentControl2.TabIndex = 43;
            this.attitudeIndicatorInstrumentControl2.Text = "attitudeIndicatorInstrumentControl2";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label7.Location = new System.Drawing.Point(1006, 94);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 17);
            this.label7.TabIndex = 42;
            this.label7.Text = "EL:";
            // 
            // textBox_bl
            // 
            this.textBox_bl.Location = new System.Drawing.Point(711, 60);
            this.textBox_bl.Name = "textBox_bl";
            this.textBox_bl.Size = new System.Drawing.Size(112, 25);
            this.textBox_bl.TabIndex = 41;
            // 
            // textBox_br
            // 
            this.textBox_br.Location = new System.Drawing.Point(1068, 60);
            this.textBox_br.Name = "textBox_br";
            this.textBox_br.Size = new System.Drawing.Size(112, 25);
            this.textBox_br.TabIndex = 40;
            // 
            // textBox_fl
            // 
            this.textBox_fl.Location = new System.Drawing.Point(711, 29);
            this.textBox_fl.Name = "textBox_fl";
            this.textBox_fl.Size = new System.Drawing.Size(112, 25);
            this.textBox_fl.TabIndex = 39;
            // 
            // textBox_fr
            // 
            this.textBox_fr.Location = new System.Drawing.Point(1068, 29);
            this.textBox_fr.Name = "textBox_fr";
            this.textBox_fr.Size = new System.Drawing.Size(112, 25);
            this.textBox_fr.TabIndex = 38;
            // 
            // textBox_e
            // 
            this.textBox_e.Location = new System.Drawing.Point(1047, 91);
            this.textBox_e.Name = "textBox_e";
            this.textBox_e.Size = new System.Drawing.Size(112, 25);
            this.textBox_e.TabIndex = 37;
            // 
            // trackBar_throttle
            // 
            this.trackBar_throttle.Location = new System.Drawing.Point(1165, 91);
            this.trackBar_throttle.Maximum = 1500;
            this.trackBar_throttle.Minimum = 900;
            this.trackBar_throttle.Name = "trackBar_throttle";
            this.trackBar_throttle.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBar_throttle.Size = new System.Drawing.Size(45, 522);
            this.trackBar_throttle.SmallChange = 5;
            this.trackBar_throttle.TabIndex = 36;
            this.trackBar_throttle.Value = 1100;
            this.trackBar_throttle.Scroll += new System.EventHandler(this.trackBar_throttle_Scroll);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label6.Location = new System.Drawing.Point(839, 63);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 17);
            this.label6.TabIndex = 35;
            this.label6.Text = "BR:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label5.Location = new System.Drawing.Point(489, 34);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 17);
            this.label5.TabIndex = 34;
            this.label5.Text = "FL:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(839, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 17);
            this.label2.TabIndex = 33;
            this.label2.Text = "FR:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(489, 63);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 17);
            this.label1.TabIndex = 22;
            this.label1.Text = "BL:";
            // 
            // progressBar_br
            // 
            this.progressBar_br.Location = new System.Drawing.Point(880, 60);
            this.progressBar_br.Maximum = 2000;
            this.progressBar_br.Minimum = 1000;
            this.progressBar_br.Name = "progressBar_br";
            this.progressBar_br.Size = new System.Drawing.Size(172, 23);
            this.progressBar_br.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar_br.TabIndex = 32;
            this.progressBar_br.Value = 1000;
            // 
            // progressBar_fl
            // 
            this.progressBar_fl.Location = new System.Drawing.Point(530, 31);
            this.progressBar_fl.Maximum = 2000;
            this.progressBar_fl.Minimum = 1000;
            this.progressBar_fl.Name = "progressBar_fl";
            this.progressBar_fl.Size = new System.Drawing.Size(172, 23);
            this.progressBar_fl.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar_fl.TabIndex = 31;
            this.progressBar_fl.Value = 1000;
            // 
            // progressBar_fr
            // 
            this.progressBar_fr.Location = new System.Drawing.Point(880, 31);
            this.progressBar_fr.Maximum = 2000;
            this.progressBar_fr.Minimum = 1000;
            this.progressBar_fr.Name = "progressBar_fr";
            this.progressBar_fr.Size = new System.Drawing.Size(172, 23);
            this.progressBar_fr.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar_fr.TabIndex = 30;
            this.progressBar_fr.Value = 1000;
            // 
            // progressBar_bl
            // 
            this.progressBar_bl.Location = new System.Drawing.Point(530, 60);
            this.progressBar_bl.Maximum = 2000;
            this.progressBar_bl.Minimum = 1000;
            this.progressBar_bl.Name = "progressBar_bl";
            this.progressBar_bl.Size = new System.Drawing.Size(172, 23);
            this.progressBar_bl.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar_bl.TabIndex = 29;
            this.progressBar_bl.Value = 1000;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.checkBox_sendDataToArduino);
            this.groupBox4.Controls.Add(this.checkBox_sendSocket);
            this.groupBox4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox4.Location = new System.Drawing.Point(10, 173);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(439, 80);
            this.groupBox4.TabIndex = 28;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Settings:";
            // 
            // checkBox_sendDataToArduino
            // 
            this.checkBox_sendDataToArduino.AutoSize = true;
            this.checkBox_sendDataToArduino.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.checkBox_sendDataToArduino.Location = new System.Drawing.Point(14, 24);
            this.checkBox_sendDataToArduino.Name = "checkBox_sendDataToArduino";
            this.checkBox_sendDataToArduino.Size = new System.Drawing.Size(162, 21);
            this.checkBox_sendDataToArduino.TabIndex = 26;
            this.checkBox_sendDataToArduino.Text = "Send to Arduino";
            this.checkBox_sendDataToArduino.UseVisualStyleBackColor = true;
            // 
            // checkBox_sendSocket
            // 
            this.checkBox_sendSocket.AutoSize = true;
            this.checkBox_sendSocket.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.checkBox_sendSocket.Location = new System.Drawing.Point(14, 51);
            this.checkBox_sendSocket.Name = "checkBox_sendSocket";
            this.checkBox_sendSocket.Size = new System.Drawing.Size(171, 21);
            this.checkBox_sendSocket.TabIndex = 27;
            this.checkBox_sendSocket.Text = "Send over Socket";
            this.checkBox_sendSocket.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.Roll);
            this.tabControl2.Controls.Add(this.Pitch);
            this.tabControl2.Location = new System.Drawing.Point(3, 3);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(453, 164);
            this.tabControl2.TabIndex = 0;
            // 
            // Roll
            // 
            this.Roll.BackColor = System.Drawing.Color.DimGray;
            this.Roll.Controls.Add(this.groupBox1);
            this.Roll.Location = new System.Drawing.Point(4, 26);
            this.Roll.Name = "Roll";
            this.Roll.Padding = new System.Windows.Forms.Padding(3);
            this.Roll.Size = new System.Drawing.Size(445, 134);
            this.Roll.TabIndex = 0;
            this.Roll.Text = "Roll";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.DimGray;
            this.groupBox1.Controls.Add(this.lb_d);
            this.groupBox1.Controls.Add(this.lb_i);
            this.groupBox1.Controls.Add(this.lb_p);
            this.groupBox1.Controls.Add(this.textBox_pR);
            this.groupBox1.Controls.Add(this.textBox_dTr);
            this.groupBox1.Controls.Add(this.textBox_pTr);
            this.groupBox1.Controls.Add(this.numericUpDown_pR);
            this.groupBox1.Controls.Add(this.textBox_iTr);
            this.groupBox1.Controls.Add(this.numericUpDown_iR);
            this.groupBox1.Controls.Add(this.numericUpDown_dR);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.textBox_iR);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.textBox_dR);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(439, 128);
            this.groupBox1.TabIndex = 25;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "PID ROLL:";
            // 
            // lb_d
            // 
            this.lb_d.AutoSize = true;
            this.lb_d.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lb_d.Location = new System.Drawing.Point(11, 88);
            this.lb_d.Name = "lb_d";
            this.lb_d.Size = new System.Drawing.Size(26, 17);
            this.lb_d.TabIndex = 12;
            this.lb_d.Text = "D:";
            // 
            // lb_i
            // 
            this.lb_i.AutoSize = true;
            this.lb_i.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lb_i.Location = new System.Drawing.Point(11, 58);
            this.lb_i.Name = "lb_i";
            this.lb_i.Size = new System.Drawing.Size(26, 17);
            this.lb_i.TabIndex = 11;
            this.lb_i.Text = "I:";
            // 
            // lb_p
            // 
            this.lb_p.AutoSize = true;
            this.lb_p.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lb_p.Location = new System.Drawing.Point(11, 30);
            this.lb_p.Name = "lb_p";
            this.lb_p.Size = new System.Drawing.Size(26, 17);
            this.lb_p.TabIndex = 10;
            this.lb_p.Text = "P:";
            // 
            // textBox_pR
            // 
            this.textBox_pR.Location = new System.Drawing.Point(151, 27);
            this.textBox_pR.Name = "textBox_pR";
            this.textBox_pR.Size = new System.Drawing.Size(112, 25);
            this.textBox_pR.TabIndex = 13;
            // 
            // textBox_dTr
            // 
            this.textBox_dTr.Location = new System.Drawing.Point(347, 83);
            this.textBox_dTr.Name = "textBox_dTr";
            this.textBox_dTr.Size = new System.Drawing.Size(67, 25);
            this.textBox_dTr.TabIndex = 19;
            // 
            // textBox_pTr
            // 
            this.textBox_pTr.Location = new System.Drawing.Point(347, 26);
            this.textBox_pTr.Name = "textBox_pTr";
            this.textBox_pTr.Size = new System.Drawing.Size(67, 25);
            this.textBox_pTr.TabIndex = 21;
            // 
            // numericUpDown_pR
            // 
            this.numericUpDown_pR.DecimalPlaces = 2;
            this.numericUpDown_pR.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.numericUpDown_pR.Increment = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.numericUpDown_pR.Location = new System.Drawing.Point(43, 27);
            this.numericUpDown_pR.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_pR.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_pR.Name = "numericUpDown_pR";
            this.numericUpDown_pR.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_pR.TabIndex = 6;
            this.numericUpDown_pR.ValueChanged += new System.EventHandler(this.numericUpDown_pR_ValueChanged);
            // 
            // textBox_iTr
            // 
            this.textBox_iTr.Location = new System.Drawing.Point(347, 56);
            this.textBox_iTr.Name = "textBox_iTr";
            this.textBox_iTr.Size = new System.Drawing.Size(67, 25);
            this.textBox_iTr.TabIndex = 20;
            // 
            // numericUpDown_iR
            // 
            this.numericUpDown_iR.DecimalPlaces = 2;
            this.numericUpDown_iR.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
            this.numericUpDown_iR.Increment = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.numericUpDown_iR.Location = new System.Drawing.Point(43, 55);
            this.numericUpDown_iR.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_iR.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_iR.Name = "numericUpDown_iR";
            this.numericUpDown_iR.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_iR.TabIndex = 5;
            this.numericUpDown_iR.ValueChanged += new System.EventHandler(this.numericUpDown_iR_ValueChanged);
            // 
            // numericUpDown_dR
            // 
            this.numericUpDown_dR.DecimalPlaces = 2;
            this.numericUpDown_dR.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
            this.numericUpDown_dR.Increment = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.numericUpDown_dR.Location = new System.Drawing.Point(43, 84);
            this.numericUpDown_dR.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_dR.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_dR.Name = "numericUpDown_dR";
            this.numericUpDown_dR.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_dR.TabIndex = 4;
            this.numericUpDown_dR.ValueChanged += new System.EventHandler(this.numericUpDown_dR_ValueChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label11.Location = new System.Drawing.Point(279, 30);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(62, 17);
            this.label11.TabIndex = 18;
            this.label11.Text = "pTerm:";
            // 
            // textBox_iR
            // 
            this.textBox_iR.Location = new System.Drawing.Point(151, 56);
            this.textBox_iR.Name = "textBox_iR";
            this.textBox_iR.Size = new System.Drawing.Size(112, 25);
            this.textBox_iR.TabIndex = 15;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label10.Location = new System.Drawing.Point(279, 58);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(62, 17);
            this.label10.TabIndex = 17;
            this.label10.Text = "iTerm:";
            // 
            // textBox_dR
            // 
            this.textBox_dR.Location = new System.Drawing.Point(151, 85);
            this.textBox_dR.Name = "textBox_dR";
            this.textBox_dR.Size = new System.Drawing.Size(112, 25);
            this.textBox_dR.TabIndex = 14;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label9.Location = new System.Drawing.Point(279, 87);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(62, 17);
            this.label9.TabIndex = 16;
            this.label9.Text = "dTerm:";
            // 
            // Pitch
            // 
            this.Pitch.BackColor = System.Drawing.Color.DimGray;
            this.Pitch.Controls.Add(this.groupBox5);
            this.Pitch.Location = new System.Drawing.Point(4, 26);
            this.Pitch.Name = "Pitch";
            this.Pitch.Padding = new System.Windows.Forms.Padding(3);
            this.Pitch.Size = new System.Drawing.Size(445, 134);
            this.Pitch.TabIndex = 1;
            this.Pitch.Text = "Pitch";
            // 
            // groupBox5
            // 
            this.groupBox5.BackColor = System.Drawing.Color.DimGray;
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.label4);
            this.groupBox5.Controls.Add(this.label16);
            this.groupBox5.Controls.Add(this.textBox_pP);
            this.groupBox5.Controls.Add(this.textBox3);
            this.groupBox5.Controls.Add(this.textBox10);
            this.groupBox5.Controls.Add(this.numericUpDown_pPitch);
            this.groupBox5.Controls.Add(this.textBox11);
            this.groupBox5.Controls.Add(this.numericUpDown_iPitch);
            this.groupBox5.Controls.Add(this.numericUpDown_dPitch);
            this.groupBox5.Controls.Add(this.label17);
            this.groupBox5.Controls.Add(this.textBox_iP);
            this.groupBox5.Controls.Add(this.label18);
            this.groupBox5.Controls.Add(this.textBox_dP);
            this.groupBox5.Controls.Add(this.label19);
            this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox5.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox5.Location = new System.Drawing.Point(3, 3);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(439, 128);
            this.groupBox5.TabIndex = 43;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "PID PITCH:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Location = new System.Drawing.Point(11, 88);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(26, 17);
            this.label3.TabIndex = 12;
            this.label3.Text = "D:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Location = new System.Drawing.Point(11, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(26, 17);
            this.label4.TabIndex = 11;
            this.label4.Text = "I:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label16.Location = new System.Drawing.Point(11, 30);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(26, 17);
            this.label16.TabIndex = 10;
            this.label16.Text = "P:";
            // 
            // textBox_pP
            // 
            this.textBox_pP.Location = new System.Drawing.Point(151, 27);
            this.textBox_pP.Name = "textBox_pP";
            this.textBox_pP.Size = new System.Drawing.Size(112, 25);
            this.textBox_pP.TabIndex = 13;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(347, 83);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(67, 25);
            this.textBox3.TabIndex = 19;
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(347, 26);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(67, 25);
            this.textBox10.TabIndex = 21;
            // 
            // numericUpDown_pPitch
            // 
            this.numericUpDown_pPitch.DecimalPlaces = 2;
            this.numericUpDown_pPitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.numericUpDown_pPitch.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDown_pPitch.Location = new System.Drawing.Point(43, 27);
            this.numericUpDown_pPitch.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_pPitch.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_pPitch.Name = "numericUpDown_pPitch";
            this.numericUpDown_pPitch.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_pPitch.TabIndex = 6;
            this.numericUpDown_pPitch.ValueChanged += new System.EventHandler(this.numericUpDown_pPitch_ValueChanged);
            // 
            // textBox11
            // 
            this.textBox11.Location = new System.Drawing.Point(347, 56);
            this.textBox11.Name = "textBox11";
            this.textBox11.Size = new System.Drawing.Size(67, 25);
            this.textBox11.TabIndex = 20;
            // 
            // numericUpDown_iPitch
            // 
            this.numericUpDown_iPitch.DecimalPlaces = 2;
            this.numericUpDown_iPitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
            this.numericUpDown_iPitch.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDown_iPitch.Location = new System.Drawing.Point(43, 55);
            this.numericUpDown_iPitch.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_iPitch.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_iPitch.Name = "numericUpDown_iPitch";
            this.numericUpDown_iPitch.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_iPitch.TabIndex = 5;
            this.numericUpDown_iPitch.ValueChanged += new System.EventHandler(this.numericUpDown_iPitch_ValueChanged);
            // 
            // numericUpDown_dPitch
            // 
            this.numericUpDown_dPitch.DecimalPlaces = 2;
            this.numericUpDown_dPitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F);
            this.numericUpDown_dPitch.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDown_dPitch.Location = new System.Drawing.Point(43, 84);
            this.numericUpDown_dPitch.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.numericUpDown_dPitch.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_dPitch.Name = "numericUpDown_dPitch";
            this.numericUpDown_dPitch.Size = new System.Drawing.Size(102, 24);
            this.numericUpDown_dPitch.TabIndex = 4;
            this.numericUpDown_dPitch.ValueChanged += new System.EventHandler(this.numericUpDown_dPitch_ValueChanged);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label17.Location = new System.Drawing.Point(279, 30);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(62, 17);
            this.label17.TabIndex = 18;
            this.label17.Text = "pTerm:";
            // 
            // textBox_iP
            // 
            this.textBox_iP.Location = new System.Drawing.Point(151, 56);
            this.textBox_iP.Name = "textBox_iP";
            this.textBox_iP.Size = new System.Drawing.Size(112, 25);
            this.textBox_iP.TabIndex = 15;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label18.Location = new System.Drawing.Point(279, 58);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(62, 17);
            this.label18.TabIndex = 17;
            this.label18.Text = "iTerm:";
            // 
            // textBox_dP
            // 
            this.textBox_dP.Location = new System.Drawing.Point(151, 85);
            this.textBox_dP.Name = "textBox_dP";
            this.textBox_dP.Size = new System.Drawing.Size(112, 25);
            this.textBox_dP.TabIndex = 14;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label19.Location = new System.Drawing.Point(279, 87);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(62, 17);
            this.label19.TabIndex = 16;
            this.label19.Text = "dTerm:";
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.DimGray;
            this.tabPage1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPage1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage1.Controls.Add(this.gMap);
            this.tabPage1.Controls.Add(this.headingIndicatorInstrumentControl1);
            this.tabPage1.Controls.Add(this.attitudeIndicatorInstrumentControl1);
            this.tabPage1.ImageIndex = 0;
            this.tabPage1.Location = new System.Drawing.Point(4, 57);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(1213, 740);
            this.tabPage1.TabIndex = 2;
            // 
            // gMap
            // 
            this.gMap.Bearing = 0F;
            this.gMap.CanDragMap = true;
            this.gMap.Dock = System.Windows.Forms.DockStyle.Right;
            this.gMap.GrayScaleMode = false;
            this.gMap.LevelsKeepInMemmory = 5;
            this.gMap.Location = new System.Drawing.Point(350, 3);
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
            this.gMap.Size = new System.Drawing.Size(856, 730);
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
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.DimGray;
            this.tabPage2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.tabPage2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage2.Controls.Add(this.button_clearSerial);
            this.tabPage2.Controls.Add(this.SocketRead);
            this.tabPage2.Controls.Add(this.groupBox2);
            this.tabPage2.ForeColor = System.Drawing.SystemColors.HighlightText;
            this.tabPage2.ImageIndex = 1;
            this.tabPage2.Location = new System.Drawing.Point(4, 57);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(1213, 740);
            this.tabPage2.TabIndex = 1;
            // 
            // button_clearSerial
            // 
            this.button_clearSerial.ForeColor = System.Drawing.SystemColors.Desktop;
            this.button_clearSerial.Location = new System.Drawing.Point(6, 707);
            this.button_clearSerial.Name = "button_clearSerial";
            this.button_clearSerial.Size = new System.Drawing.Size(134, 23);
            this.button_clearSerial.TabIndex = 29;
            this.button_clearSerial.Text = "Clear serial";
            this.button_clearSerial.UseVisualStyleBackColor = true;
            this.button_clearSerial.Click += new System.EventHandler(this.button_clearSerial_Click);
            // 
            // SocketRead
            // 
            this.SocketRead.Controls.Add(this.textBox_socketRead);
            this.SocketRead.ForeColor = System.Drawing.SystemColors.Control;
            this.SocketRead.Location = new System.Drawing.Point(634, 6);
            this.SocketRead.Name = "SocketRead";
            this.SocketRead.Size = new System.Drawing.Size(569, 411);
            this.SocketRead.TabIndex = 27;
            this.SocketRead.TabStop = false;
            this.SocketRead.Text = "SocketRead:";
            // 
            // textBox_socketRead
            // 
            this.textBox_socketRead.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_socketRead.Location = new System.Drawing.Point(3, 21);
            this.textBox_socketRead.Multiline = true;
            this.textBox_socketRead.Name = "textBox_socketRead";
            this.textBox_socketRead.Size = new System.Drawing.Size(563, 387);
            this.textBox_socketRead.TabIndex = 26;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_SerialPrint);
            this.groupBox2.ForeColor = System.Drawing.SystemColors.Control;
            this.groupBox2.Location = new System.Drawing.Point(6, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(622, 695);
            this.groupBox2.TabIndex = 25;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "SerialPrint:";
            // 
            // textBox_SerialPrint
            // 
            this.textBox_SerialPrint.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_SerialPrint.Location = new System.Drawing.Point(3, 21);
            this.textBox_SerialPrint.Multiline = true;
            this.textBox_SerialPrint.Name = "textBox_SerialPrint";
            this.textBox_SerialPrint.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_SerialPrint.Size = new System.Drawing.Size(616, 671);
            this.textBox_SerialPrint.TabIndex = 23;
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
            this.groupBox3.Controls.Add(this.tabControl3);
            this.groupBox3.ForeColor = System.Drawing.SystemColors.Control;
            this.groupBox3.Location = new System.Drawing.Point(928, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(275, 727);
            this.groupBox3.TabIndex = 21;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Graph settings:";
            // 
            // tabControl3
            // 
            this.tabControl3.Controls.Add(this.tabPage4);
            this.tabControl3.Controls.Add(this.tabPage5);
            this.tabControl3.Location = new System.Drawing.Point(3, 21);
            this.tabControl3.Name = "tabControl3";
            this.tabControl3.SelectedIndex = 0;
            this.tabControl3.Size = new System.Drawing.Size(269, 703);
            this.tabControl3.TabIndex = 29;
            this.tabControl3.TabStop = false;
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
            "output",
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
            "output",
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
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.IMU);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Font = new System.Drawing.Font("Lucida Sans Typewriter", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl1.ImageList = this.tabControlImageList;
            this.tabControl1.ImeMode = System.Windows.Forms.ImeMode.AlphaFull;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1221, 801);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage6
            // 
            this.tabPage6.BackColor = System.Drawing.Color.DimGray;
            this.tabPage6.Location = new System.Drawing.Point(4, 57);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(1213, 740);
            this.tabPage6.TabIndex = 4;
            this.tabPage6.Text = "Values";
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
            // GUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DarkGray;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ClientSize = new System.Drawing.Size(1221, 801);
            this.Controls.Add(this.comboBox_Comports);
            this.Controls.Add(this.btn_serialDisconnect);
            this.Controls.Add(this.btn_ConnectSerial);
            this.Controls.Add(this.lb_connectionStatus);
            this.Controls.Add(this.status);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "GUI";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ArduinoDebug";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_stearingRatio)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_throttle)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.tabControl2.ResumeLayout(false);
            this.Roll.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_iR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_dR)).EndInit();
            this.Pitch.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_pPitch)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_iPitch)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_dPitch)).EndInit();
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.SocketRead.ResumeLayout(false);
            this.SocketRead.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.IMU.ResumeLayout(false);
            this.IMU.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.tabControl3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.tabPage5.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lb_connectionStatus;
        private System.Windows.Forms.ComboBox comboBox_Comports;
        private System.Windows.Forms.ImageList tabControlImageList;
        private System.Windows.Forms.Button btn_ConnectSerial;
        private System.Windows.Forms.Button btn_serialDisconnect;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.CheckBox checkBox_sendSocket;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage Roll;
        private System.Windows.Forms.TabPage Pitch;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox textBox_pP;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.NumericUpDown numericUpDown_pPitch;
        private System.Windows.Forms.TextBox textBox11;
        private System.Windows.Forms.NumericUpDown numericUpDown_iPitch;
        private System.Windows.Forms.NumericUpDown numericUpDown_dPitch;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBox_iP;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox textBox_dP;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.CheckBox checkBox_sendDataToArduino;
        private System.Windows.Forms.TabPage tabPage1;
        private GMap.NET.WindowsForms.GMapControl gMap;
        private AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl headingIndicatorInstrumentControl1;
        private AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl attitudeIndicatorInstrumentControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox SocketRead;
        private System.Windows.Forms.TextBox textBox_socketRead;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox_SerialPrint;
        private System.Windows.Forms.TabPage IMU;
        private ZedGraph.ZedGraphControl zedGraphControl2;
        private System.Windows.Forms.Label label8;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.TabControl tabControl3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.CheckedListBox checkedListBox_graph1;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.Label status;
        public System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lb_d;
        private System.Windows.Forms.Label lb_i;
        private System.Windows.Forms.Label lb_p;
        private System.Windows.Forms.TextBox textBox_pR;
        private System.Windows.Forms.TextBox textBox_dTr;
        private System.Windows.Forms.TextBox textBox_pTr;
        private System.Windows.Forms.NumericUpDown numericUpDown_pR;
        private System.Windows.Forms.TextBox textBox_iTr;
        private System.Windows.Forms.NumericUpDown numericUpDown_iR;
        private System.Windows.Forms.NumericUpDown numericUpDown_dR;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBox_iR;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBox_dR;
        private System.Windows.Forms.Label label9;
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
        private System.Windows.Forms.TrackBar trackBar_throttle;
        private System.Windows.Forms.TextBox textBox_e;
        private System.Windows.Forms.TextBox textBox_bl;
        private System.Windows.Forms.TextBox textBox_br;
        private System.Windows.Forms.TextBox textBox_fl;
        private System.Windows.Forms.TextBox textBox_fr;
        private System.Windows.Forms.Button button_clearSerial;
        private System.Windows.Forms.Label label7;
        private AvionicsInstrumentControlDemo.AttitudeIndicatorInstrumentControl attitudeIndicatorInstrumentControl2;
        private AvionicsInstrumentControlDemo.HeadingIndicatorInstrumentControl headingIndicatorInstrumentControl2;
        private System.Windows.Forms.NumericUpDown numericUpDown_stearingRatio;
        private System.Windows.Forms.Button btn_right;
        private System.Windows.Forms.Button brn_down;
        private System.Windows.Forms.Button btn_left;
        private System.Windows.Forms.Button btn_up;
    }
}

