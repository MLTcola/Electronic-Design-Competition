using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace 大创上位机编写
{
    /****************************************************************
     如果接受到0x01,则传输的数据
     ****************************************************************/
    public partial class Form1 : Form
    {
        bool KeyDownState;
        private static int iSeed = 8;
        Random rd = new Random(iSeed);
        //存放数据的数组最大值
        private int sizeMax;
        //存放y轴数据的数组链表
        private List<int> DataL;
        //存放在画布上的数据节点的数组
        private Point[] pArrData;


        //存放等势图相关传回的值
        private Int16 GraphValue;
        private string goForward;
        private string goBack;
        private string goLeft;
        private string goRight;
        private string goUp;
        private string goDown;
        private string machineStop;

        public Form1()//初始化
        {
            InitializeComponent();
            string flag;
            bool jugdeSerialPortState = false;
            for (int i = 0; i < 20; i++)
            {
                flag = "COM" + i.ToString();
                try
                {
                    serialPort1.PortName = flag;
                    serialPort1.Open();
                    comboBox1.Items.Add(flag);
                    jugdeSerialPortState = true; ;
                    serialPort1.Close();
                }
                catch (Exception)
                {
                }
             }  
            if (!jugdeSerialPortState)
                {
                    MessageBox.Show("串口未打开","提示");
                }    
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            
            this.KeyPreview = true;
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
            radioButton1.Checked = true;
            radioButton3.Checked = true;
            timer1.Interval = 150;
            timer1.Start();
            timer2.Start();

        }
        #region  数据接收
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string str;
            if (!radioButton4.Checked)//字符
            {
                try
                {
                    str = serialPort1.ReadExisting();
                    textBox1.AppendText(str);
                }
                catch (Exception){ }      
            }
            else
            {
                byte dat;
                dat = (byte)serialPort1.ReadByte();
                str = Convert.ToString(dat, 16).ToUpper();
                textBox1.AppendText((str.Length == 1) ? ("0X0" + str) : ("0X" + str));
            }
        }
        #endregion
        #region   按键
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            Keys k = e.KeyCode;
            if (k == Keys.W)
            {
                label10.Text = "模式一：只允许向前走";
                goForward = "1";
                if(serialPort1.IsOpen)
                    serialPort1.WriteLine(goForward);
                pictureBox1.Image = Properties.Resources.UpGreen;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;
            }
            else if (k == Keys.S)
            {
                label10.Text = "模式二：先向前三秒在向右三秒";
                goBack = "2";
                if (serialPort1.IsOpen)
                    serialPort1.WriteLine(goBack);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownGreen;
                KeyDownState = true;
            }
            else if (k == Keys.D)
            {
                label10.Text = "模式三：只允许向右走";
                goRight = "3";
                if (serialPort1.IsOpen)
                    serialPort1.WriteLine(goRight);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightGreen;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;
            }
            else if (k == Keys.A)
            {
                label10.Text = "模式四：只允许向右走";
                goLeft = "4";
                if (serialPort1.IsOpen)
                    serialPort1.WriteLine(goLeft);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftGreen;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;
            }
        }
     
        private void timer1_Tick(object sender, EventArgs e)
        {
            if(!KeyDownState)
            {
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownBlue;
                button9.BackColor = System.Drawing.Color.White;
            }
            KeyDownState = false;
        }
        #endregion
        #region   数据扫描
        private void button3_Click(object sender, EventArgs e)
        {
            string flag;
            for (int i = 0; i > 20; i++)
            {
                flag = "COM" + i.ToString();
                try
                {
                    serialPort1.PortName = flag;
                    serialPort1.Open();
                    comboBox1.Items.Add(flag);
                    serialPort1.Close();
                }
                catch (Exception)
                {
                    serialPort1.Close();
                }
        }

    }
        #endregion
        #region  打开/关闭串口
        private void button4_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Open();
                    pictureBox8.Image = Properties.Resources.ButtonOn;
                    button4.Text = "关闭串口";
                }
                catch (Exception)
                {
                    serialPort1.Close();
                    MessageBox.Show("串口打开错误\n请检查串口参数配置","提示");
                }
            }
            else
            {
                try
                {
                    serialPort1.Close();
                    pictureBox8.Image = Properties.Resources.ButtonOff;
                    button4.Text = "打开串口";
                }
                catch (Exception)
                {
                }
            }
        }
        #endregion
        #region  数据发送
        private void SendDataToSerialPort(SerialPort myPort, TextBox myTextBox)
        {
            string str;
            if (myPort.IsOpen)
            {
                if (myTextBox.Text != "")
                {
                    if (!radioButton2.Checked)
                    {
                        #region 写入字符
                        try
                        {
                            str = myTextBox.Text;
                            myPort.WriteLine(str);
                        }
                        catch (Exception)
                        {
                            MessageBox.Show("数据写入错误", "错误");
                        }
                        #endregion
                    }
                    else
                    {
                        #region  写入数值
                        byte[] buffer = new byte[1];
                        str = myTextBox.Text;
                        for (int i = 0; i < (str.Length - str.Length % 2) / 2; i++)
                        {
                            try
                            {
                                buffer[0] = Convert.ToByte(str.Substring(i * 2, 2));
                                myPort.Write(buffer, 0, 1);
                            }
                            catch (Exception)
                            {
                                MessageBox.Show("数据写入错误", "错误");
                            }
                        }
                        #endregion
                    }
                }
                else
                    MessageBox.Show("发送数据不能为空", "错误");
            }
            else
            {
                MessageBox.Show("串口还没有打开", "错误");
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            SendDataToSerialPort(serialPort1, textBox2);
        }
        #endregion

        private void button7_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }

        private void button9_Click(object sender, EventArgs e)
        {
            machineStop="9";
            if (serialPort1.IsOpen)
                serialPort1.WriteLine(machineStop);
        }

    }
}
