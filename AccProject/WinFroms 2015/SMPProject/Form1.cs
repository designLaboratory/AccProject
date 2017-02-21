using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SMPProject
{
    public partial class Form1 : Form
    {
        string RawAccelXYZaxisData;   // raw data frame from UART

        int[] ConvertedAccelData = new int[3]; //array to hold separeted and converted data

        int[] RGBconvertedAccelData = new int[3]; //Data converted to RGB 

        public Form1()
        {
            InitializeComponent();  //init of win forms component
            var _portNames = SerialPort.GetPortNames();
            foreach (var item in _portNames)
            {
                choosePort_ComobBox.Items.Add(item);
            }
        }



        private void uartPort_DataReceviedHandler(object sender, SerialDataReceivedEventArgs e)   //UART data recevied event handler
        {
            SerialPort _uart = (SerialPort)sender;   //reference to the object that raised the event

            RawAccelXYZaxisData = _uart.ReadExisting();  //recevied data to string

            if (RawAccelXYZaxisData != null)
            {
                RawData_ToIntArray();  // Converting to int
                ConvertedAccelData_ToRGB(); // converting to RGB
                SetPictureBoxColor();  // setting picture box color
            }
            

            this.Invoke(new MethodInvoker(delegate  //asynchronous GUI update
            {
                axisLabel.Text = RawAccelXYZaxisData;
                XaxisLabel.Text = ConvertedAccelData[0].ToString();
                YaxisLabel.Text = ConvertedAccelData[1].ToString();
                ZaxisLabel.Text = ConvertedAccelData[2].ToString();
            }));
        }

        private void connectButton_Click(object sender, EventArgs e)   //button click event
        {
            try
            {
                //uartPort.PortName = choosePort_ComobBox.SelectedText;
                uartPort.PortName = choosePort_ComobBox.SelectedItem.ToString();
                if (choosePort_ComobBox.SelectedText != null)
                {
                    uartPort.Open();   //openning defined UART port
                    uartPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(uartPort_DataReceviedHandler); // added Data recevied event handler

                    if (uartPort.IsOpen)
                    {
                        MessageBox.Show("CONNECTED");
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void RawData_ToIntArray()  //function wihich converts raw data from UART frame to (int)array
        {
            var _splitedString = RawAccelXYZaxisData.Split(System.Environment.NewLine.ToCharArray()); //splitting raw data to char array after evry new line

            string[] _temparray = new string[3];  //creating temp string array

            if (_splitedString.Length > 3) //checking if Split function succed
            {
                foreach (var item in _splitedString)  
                {
                    if (item != string.Empty)
                    {
                        if (item.Contains('X')) //cheking if X axis
                        {
                            foreach (char var in item)
                            {
                                if (Char.IsDigit(var) || var == '-')
                                {
                                    _temparray[0] += var.ToString(); //added converted string to tem array
                                }
                            }
                        }
                        if (item.Contains('Y')) //checking if Y axis
                        {
                            foreach (char var in item)
                            {
                                if (Char.IsDigit(var) || var == '-')
                                {
                                    _temparray[1] += var.ToString(); 
                                }
                            }
                        }
                        if (item.Contains('Z')) //checking if Z axis
                        {
                            foreach (char var in item)
                            {
                                if (Char.IsDigit(var) || var == '-')
                                {
                                    _temparray[2] += var.ToString();
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < _temparray.Length; i++)
                {
                    int _tempnum = 0;

                    if (_temparray[i] != null)
                    {
                        if (int.TryParse(_temparray[i], out _tempnum)) //Try Parse to int, if succed save to converted accel data
                        {
                            ConvertedAccelData[i] = _tempnum;
                        }
                    }

                }
            }           
        }

        private void ConvertedAccelData_ToRGB()  // converting data to RGB color range
        {
            int[] _AccelDataRange = new int[2];
            _AccelDataRange[0] = -16000; //start value
            _AccelDataRange[1] = 16000; //end value

            int[] _RGBrange = new int[2];
            _RGBrange[0] = 0;
            _RGBrange[1] = 255;

            double scale = (double)(_RGBrange[1] - _RGBrange[0]) / (_AccelDataRange[1] - _AccelDataRange[0]);
            try
            {
                for (int i = 0; i < RGBconvertedAccelData.Length; i++)
                {
                    RGBconvertedAccelData[i] = (int)(_RGBrange[0] + ((ConvertedAccelData[i] - _AccelDataRange[0]) * scale));
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }  

        private void SetPictureBoxColor()  //setting ciolor of picturebox
        {
            if (!(RGBconvertedAccelData[0] < 0 || RGBconvertedAccelData[0] > 255 || RGBconvertedAccelData[1] < 0 || RGBconvertedAccelData[1] > 255 || RGBconvertedAccelData[2] < 0 || RGBconvertedAccelData[2] > 255))
            {
                try
                {
                    pictureBox1.BackColor = Color.FromArgb(RGBconvertedAccelData[0], RGBconvertedAccelData[1], RGBconvertedAccelData[2]);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            uartPort.Close();
        }
    }
}
