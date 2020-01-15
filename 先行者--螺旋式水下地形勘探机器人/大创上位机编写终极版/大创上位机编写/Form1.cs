using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace 大创上位机编写
{
    /****************************************************************
     等比例缩小2.5
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
        private List<int> DataL2;
        private List<int> DataL3;
        //存放在画布上的数据节点的数组
        private Point[] pArrData;
        private Point[] pArrData2;
        private Point[] pArrData3;

        private int distanceValue1;
        private int distanceValue2;
        private int distanceValue3;
        private string goForward;
        private string goBack;
        private string goLeft;
        private string goRight;
        private string goUp;
        private string goDown;
        private string machineStop;
        private int mapFlag=0;
        private Int16 dutyCycleg = 700;
        private Int16 dutyCyclej = 700;
        private Int16 dutyCyclev = 700;
        private Int16 dutyCyclen = 500;
        private string directionState;
        private int leng=0;
        private int handleFlag=0;
        int[] handle = new int[14];

        public Form1()//初始化
        {
            InitializeComponent();


            panel3.Parent = pictureBox5;
            panel3.BackColor = Color.Transparent;
            label4.Parent = panel3;
            label4.BackColor = Color.Transparent;

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
                    comboBox1.Text = flag;
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

            //等势图
            sizeMax = pictureBox5.Width / 20;
            //数据数组
            DataL = new List<int>();
            DataL2 = new List<int>();
            DataL3 = new List<int>();
            pArrData = new Point[sizeMax + 1];
            pArrData2 = new Point[sizeMax + 1];
            pArrData3 = new Point[sizeMax + 1];

            #region  坐标轴初始化
            //数据初始化   
            string[] yValue = new string[7] { "0","75", "150", "225", "300", "375", "450"};
            //画图初始化   
            Bitmap bMap = new Bitmap(800, 258);
            Graphics gph = Graphics.FromImage(bMap);
            //gph.Clear(Color.White);

            PointF cPt = new PointF(30, 222);//中心点   
            //画X轴   
            //gph.DrawLine(Pens.Black, cPt.X, cPt.Y, cPt.Y+1000, cPt.Y);
            //gph.FillPolygon(new SolidBrush(Color.Black), xPt);
            //画Y轴   
            gph.DrawLine(Pens.Black, cPt.X, cPt.Y, cPt.X, cPt.X);
            //gph.DrawString("单位(cm)", new Font("宋体", 9), Brushes.Black, new PointF(6, 7));
            for (int i = 0; i <= 6; i++)
            {
                //画Y轴刻度   
                    gph.DrawString(yValue[i], new Font("宋体", 11), Brushes.Black,
                     new PointF(cPt.X - 30, cPt.Y - i * 30 - 6));
                    gph.DrawLine(Pens.Black, cPt.X - 3, cPt.Y - i * 30, cPt.X, cPt.Y - i * 30);
            }
            ////显示在pictureBox2控件中
            this.pictureBox11.Image = bMap;
            this.pictureBox12.Image = bMap;
            this.pictureBox13.Image = bMap;
            #endregion
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            
            this.KeyPreview = true;
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
            radioButton1.Checked = true;
            radioButton4.Checked = true;
            comboBox2.Text = Convert.ToString(9600);
            timer1.Interval = 150;
            timer1.Start();
            timer2.Start();
            timer3.Start();
            timer4.Start();


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
                catch (Exception) {
                    //MessageBox.Show("异常");
                }      
            }
            else
            {
                int dat;
                dat = serialPort1.ReadByte();

                if (Convert.ToString(dat, 16) == "b")
                {
                    handleFlag=1;
                }
                if(handleFlag==1)
                {
                    handle[leng] = dat;               
                    leng++;
                    if (Convert.ToString(dat, 16) == "d"&&leng==14)
                    {
                        leng = 0;
                        distanceValue1 = handle[1] * 1000 + handle[2] * 100 + handle[3] * 10 + handle[4];
                        distanceValue2 = handle[5] * 1000 + handle[6] * 100 + handle[7] * 10 + handle[8];
                        distanceValue3 = handle[9] * 1000 + handle[10] * 100 + handle[11] * 10 + handle[12];
                        textBox1.AppendText("距离1："+Convert.ToString(distanceValue1)+"   ");
                        textBox1.AppendText("距离2：" + Convert.ToString(distanceValue2) + "   ");
                        textBox1.AppendText("距离3：" + Convert.ToString(distanceValue2) + "   \n");
                        distanceValue1 = 220 - distanceValue1 / 2;
                        distanceValue2 = 220 - distanceValue2 / 2;
                        distanceValue3 = 220 - distanceValue3 / 2;
                        if (mapFlag == 1)
                        {
                            DataL.Add(distanceValue1);
                            DataL2.Add(distanceValue2);
                            DataL3.Add(distanceValue2);
                        }
                    }
                 }
            }
        }
        #endregion
        #region   按键
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            Keys k = e.KeyCode;
            if (k == Keys.W)
            {
                label10.Text = "向上";
                label16.Text = "700";
                label17.Text = "700";
                try
                {
                    goForward = "w";
                    if(serialPort1.IsOpen)
                        serialPort1.WriteLine(goForward);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "w";
                pictureBox1.Image = Properties.Resources.UpGreen;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;

            }
            else if (k == Keys.S)
            {
                label10.Text = "向下";
                try
                {
                   goBack = "s";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goBack);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "s";
                //dutyCycle = 200;
                //label2.Text = Convert.ToString(dutyCycle, 10);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownGreen;
                KeyDownState = true;
            }
            else if (k == Keys.D)
            {
                label10.Text = "向右";
                label16.Text = "700";
                label17.Text = "0";
                try
                {
                    goRight = "d";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goRight);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "d";
                //dutyCycle = 200;
                //label2.Text = Convert.ToString(dutyCycle, 10);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftBlue;
                pictureBox3.Image = Properties.Resources.RightGreen;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;
            }
            else if (k == Keys.A)
            {
                label10.Text = "向左";
                label16.Text = "0";
                label17.Text = "700";
                try
                {
                    goLeft = "a";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goLeft);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "a";
                //dutyCycle = 200;
                //label2.Text = Convert.ToString(dutyCycle, 10);
                pictureBox1.Image = Properties.Resources.UpBlue;
                pictureBox2.Image = Properties.Resources.LeftGreen;
                pictureBox3.Image = Properties.Resources.RightBlue;
                pictureBox4.Image = Properties.Resources.DownBlue;
                KeyDownState = true;
            }
            else if (k == Keys.G)
            {
                //label10.Text = "上浮";
                try
                {
                    goUp = "g";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goUp);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "g";
                dutyCycleg -= 10;
                label16.Text = Convert.ToString(dutyCycleg, 10);
                button11.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }
            else if (k == Keys.H)
            {
                //label10.Text = "下沉";
                try
                {
                   goDown = "h";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "h";
                dutyCycleg += 10;
                label16.Text = Convert.ToString(dutyCycleg, 10);
                button12.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }

            else if (k == Keys.J)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "j";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "j";
                dutyCyclej -= 10;
                label17.Text = Convert.ToString(dutyCyclej, 10);
                button13.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }
            else if (k == Keys.K)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "k";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "k";
                dutyCyclej += 10;
                label17.Text = Convert.ToString(dutyCyclej, 10);
                button14.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }

            else if (k == Keys.V)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "v";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "v";
                dutyCyclev -= 10;
                label18.Text = Convert.ToString(dutyCyclev, 10);
                button15.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }
            else if (k == Keys.B)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "b";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "b";
                dutyCyclev += 10;
                label18.Text = Convert.ToString(dutyCyclev, 10);
                button16.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }

            else if (k == Keys.N)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "n";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "n";
                dutyCyclen -= 10;
                label19.Text = Convert.ToString(dutyCyclen, 10);
                button17.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }

            else if (k == Keys.M)
            {
                //label10.Text = "下沉";
                try
                {
                    goDown = "m";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(goDown);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "m";
                dutyCyclen += 10;
                label19.Text = Convert.ToString(dutyCyclen, 10);
                button18.BackColor = System.Drawing.Color.Blue;
                KeyDownState = true;
            }
            else if (k == Keys.O)
            {
                label10.Text = "停止";
                try
                {
                    machineStop = "o";
                    if (serialPort1.IsOpen)
                        serialPort1.WriteLine(machineStop);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送出错了", "提示");
                }
                directionState = "o";
                //dutyCycle = 200;
                //label2.Text = Convert.ToString(dutyCycle, 10);
                button9.BackColor = System.Drawing.Color.Blue;
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
                button11.BackColor = System.Drawing.Color.White;
                button12.BackColor = System.Drawing.Color.White;
                button13.BackColor = System.Drawing.Color.White;
                button14.BackColor = System.Drawing.Color.White;
                button15.BackColor = System.Drawing.Color.White;
                button16.BackColor = System.Drawing.Color.White;
                button17.BackColor = System.Drawing.Color.White;
                button18.BackColor = System.Drawing.Color.White;
                button9.BackColor = System.Drawing.Color.White;
                //label10.Text = "悬停";
            }
            KeyDownState = false;

                if (serialPort1.IsOpen)
                {
                    pictureBox7.Image = Properties.Resources.Ture1;
                }
                else
                {
                    pictureBox7.Image = Properties.Resources.False;
                }
        }
        #endregion
        #region   数据扫描
        private void button3_Click(object sender, EventArgs e)
        {
            string flag;
            for (int i = 0; i < 20; i++)
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
        #region  等势图绘制
        private void timer2_Tick(object sender, EventArgs e)
        {
            try
            {
                //DataL.Add(rd.Next(0, 231));
                //数据链表是否达到x轴最大容量的数组（动态曲线的来源）
                if (DataL.Count == sizeMax + 2)
                {
                    DataL.RemoveAt(0);//移除链表第一个
                }

                //判断数据链表是否为空
                if (DataL.Count != 0)
                {
                    pArrData = new Point[DataL.Count];
                }

                //生成新的节点
                for (int i = 0; i < sizeMax + 1; i++)
                {
                    if (i >= DataL.Count)
                    {
                        break;
                    }
                    pArrData[i] = new Point(i * 20, DataL[i]);
                }
                pictureBox10.Refresh();
            }
            catch (Exception)
            {
                //MessageBox.Show("错误1");
            }
            
        }


        private void timer3_Tick(object sender, EventArgs e)
        {
            //DataL2.Add(rd.Next(0, 263));
            //数据链表是否达到x轴最大容量的数组（动态曲线的来源）
            if (DataL2.Count == sizeMax + 2)
            {
                DataL2.RemoveAt(0);//移除链表第一个
            }

            //判断数据链表是否为空
            if (DataL2.Count != 0)
            {
                pArrData2 = new Point[DataL2.Count];
            }

            //生成新的节点
            for (int i = 0; i < sizeMax + 1; i++)
            {
                if (i >= DataL2.Count)
                {
                    break;
                }
                pArrData2[i] = new Point(i * 20, DataL2[i]);
            }
            pictureBox9.Refresh();
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            //DataL3.Add(rd.Next(0, 263));
            //数据链表是否达到x轴最大容量的数组（动态曲线的来源）
            if (DataL3.Count == sizeMax + 2)
            {
                DataL3.RemoveAt(0);//移除链表第一个
            }

            //判断数据链表是否为空
            if (DataL3.Count != 0)
            {
                pArrData3 = new Point[DataL3.Count];
            }

            //生成新的节点
            for (int i = 0; i < sizeMax + 1; i++)
            {
                if (i >= DataL3.Count)
                {
                    break;
                }
                pArrData3[i] = new Point(i * 20, DataL3[i]);
            }
            pictureBox5.Refresh();
        }
        public Pen greenPen = new Pen(Color.Green, 2);
        public Pen redPen = new Pen(Color.Red, 2);
        public Pen blackPen = new Pen(Color.Black, 2);
        public Pen grayPen = new Pen(Color.Gray, 1);

        private void pictureBox5_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                if (DataL.Count != 1)
                {
                    e.Graphics.DrawCurve(greenPen, pArrData);
                }
            }
            catch (Exception)
            {
                //MessageBox.Show("cuowu");
            }
            
        }
        #endregion

        private void button7_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }

        private void button9_Click(object sender, EventArgs e)
        {
            machineStop="o";
            if (serialPort1.IsOpen)
                serialPort1.WriteLine(machineStop);
        }

        private void pictureBox10_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                if (DataL2.Count != 1)
                {
                    e.Graphics.DrawCurve(redPen, pArrData2);
                }
            }
            catch (Exception)
            {
                //MessageBox.Show("cuowu2");
            }
            
        }

        private void pictureBox9_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                if (DataL3.Count != 1)
                {
                    e.Graphics.DrawCurve(blackPen, pArrData3);
                }
            }
            catch (Exception)
            {
                //MessageBox.Show("cuowu3");
            }
            
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (mapFlag == 0)
                {
                    mapFlag = 1;
                    button8.Text = "关闭绘图";
                }
                else
                {
                    mapFlag = 0;
                    button8.Text = "开启绘图";
                }
            }
            else
            {
                MessageBox.Show("串口未打开","提示");
            }
        }




    }
}
