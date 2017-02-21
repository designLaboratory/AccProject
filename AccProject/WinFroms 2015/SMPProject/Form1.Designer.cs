namespace SMPProject
{
    partial class Form1
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
            this.uartPort = new System.IO.Ports.SerialPort(this.components);
            this.axisLabel = new System.Windows.Forms.Label();
            this.YaxisLabel = new System.Windows.Forms.Label();
            this.ZaxisLabel = new System.Windows.Forms.Label();
            this.connectButton = new System.Windows.Forms.Button();
            this.XaxisLabel = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.choosePort_ComobBox = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // uartPort
            // 
            this.uartPort.BaudRate = 115200;
            this.uartPort.PortName = "COM5";
            // 
            // axisLabel
            // 
            this.axisLabel.AutoSize = true;
            this.axisLabel.Location = new System.Drawing.Point(800, 63);
            this.axisLabel.Name = "axisLabel";
            this.axisLabel.Size = new System.Drawing.Size(0, 13);
            this.axisLabel.TabIndex = 0;
            // 
            // YaxisLabel
            // 
            this.YaxisLabel.AutoSize = true;
            this.YaxisLabel.Location = new System.Drawing.Point(243, 153);
            this.YaxisLabel.Name = "YaxisLabel";
            this.YaxisLabel.Size = new System.Drawing.Size(35, 13);
            this.YaxisLabel.TabIndex = 1;
            this.YaxisLabel.Text = "label2";
            // 
            // ZaxisLabel
            // 
            this.ZaxisLabel.AutoSize = true;
            this.ZaxisLabel.Location = new System.Drawing.Point(243, 248);
            this.ZaxisLabel.Name = "ZaxisLabel";
            this.ZaxisLabel.Size = new System.Drawing.Size(35, 13);
            this.ZaxisLabel.TabIndex = 2;
            this.ZaxisLabel.Text = "label3";
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(412, 378);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 23);
            this.connectButton.TabIndex = 3;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // XaxisLabel
            // 
            this.XaxisLabel.AutoSize = true;
            this.XaxisLabel.Location = new System.Drawing.Point(246, 50);
            this.XaxisLabel.Name = "XaxisLabel";
            this.XaxisLabel.Size = new System.Drawing.Size(35, 13);
            this.XaxisLabel.TabIndex = 4;
            this.XaxisLabel.Text = "label1";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.HotTrack;
            this.pictureBox1.Location = new System.Drawing.Point(672, 50);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(520, 591);
            this.pictureBox1.TabIndex = 5;
            this.pictureBox1.TabStop = false;
            // 
            // choosePort_ComobBox
            // 
            this.choosePort_ComobBox.FormattingEnabled = true;
            this.choosePort_ComobBox.Location = new System.Drawing.Point(38, 378);
            this.choosePort_ComobBox.Name = "choosePort_ComobBox";
            this.choosePort_ComobBox.Size = new System.Drawing.Size(121, 21);
            this.choosePort_ComobBox.TabIndex = 6;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(412, 417);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1232, 726);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.choosePort_ComobBox);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.XaxisLabel);
            this.Controls.Add(this.connectButton);
            this.Controls.Add(this.ZaxisLabel);
            this.Controls.Add(this.YaxisLabel);
            this.Controls.Add(this.axisLabel);
            this.ForeColor = System.Drawing.Color.CornflowerBlue;
            this.Name = "Form1";
            this.Text = "Microproccessors technology";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.IO.Ports.SerialPort uartPort;
        private System.Windows.Forms.Label axisLabel;
        private System.Windows.Forms.Label YaxisLabel;
        private System.Windows.Forms.Label ZaxisLabel;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.Label XaxisLabel;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ComboBox choosePort_ComobBox;
        private System.Windows.Forms.Button button1;
    }
}

