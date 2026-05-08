using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace bitirme
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            foreach (string s in SerialPort.GetPortNames())
            {
                comboBox2.Items.Add(s);
            }
        }
        bool dragging;
        Point offset;
        string gelenveri;
        string[] gelenveriparca;
        SerialPort port1 = new SerialPort();
        private void label1_Click(object sender, EventArgs e)
        {
            port1.Close();
            this.Close();
        }

        private void baslik_MouseUp(object sender, MouseEventArgs e)
        {
            dragging = false;
        }

        private void baslik_MouseMove(object sender, MouseEventArgs e)
        {
            if (dragging)
            {
                Point currentScreenPos = PointToScreen(e.Location);
                Location = new
                Point(currentScreenPos.X - offset.X,
                currentScreenPos.Y - offset.Y);
            }
        }

        private void baslik_MouseDown(object sender, MouseEventArgs e)
        {
            dragging = true;
            offset = e.Location;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void pictureBox2_MouseUp(object sender, MouseEventArgs e)
        {
            pictureBox2.ImageLocation = "D://proje//Cancel_64px.png";
        }

        private void pictureBox2_MouseLeave(object sender, EventArgs e)
        {
            pictureBox2.ImageLocation = "D://proje//Cancel_48px.png";
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            pictureBox2.ImageLocation = "D://proje//Cancel_64px.png";
        }

        private void pictureBox2_MouseHover(object sender, EventArgs e)
        {
            pictureBox2.ImageLocation = "D://proje//Cancel_64px.png";
        }

        private void label1_MouseMove(object sender, MouseEventArgs e)
        {
            if (dragging)
            {
                Point currentScreenPos = PointToScreen(e.Location);
                Location = new
                Point(currentScreenPos.X - offset.X,
                currentScreenPos.Y - offset.Y);
            }
        }

        private void label1_MouseDown(object sender, MouseEventArgs e)
        {
            dragging = true;
            offset = e.Location;
        }

        private void label1_MouseUp(object sender, MouseEventArgs e)
        {
            dragging = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            comboBox2.Items.Clear();
            foreach (string s in SerialPort.GetPortNames())
            {
                comboBox2.Items.Add(s);
            }
        }



        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                port1.PortName = comboBox2.SelectedItem.ToString();
                port1.BaudRate = 115200;
                port1.Parity = Parity.None;
                port1.DataBits = 8;
                port1.StopBits = StopBits.One;
                port1.Open();
                System.Threading.Thread.Sleep(1000);
                port1.WriteLine("komut1");
                System.Threading.Thread.Sleep(1000);
                port1.DataReceived += SerialPortDataReceived;
                timer1.Enabled = true;
            }
            catch(Exception hata)
            {
                MessageBox.Show(hata.ToString(), "Hata Mesajı");
            }


        }
        string indata;
        private void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            indata += sp.ReadExisting();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gelenveri = indata;
            String pattern = @"\[([^\[\]]+)\]";
            int ctr = 0;
            foreach (Match m in Regex.Matches(gelenveri, pattern))
            {
                comboBox1.Items.Add(m.Groups[1].Value);
            }
            timer1.Enabled = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            port1.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string sifre = Microsoft.VisualBasic.Interaction.InputBox(comboBox1.SelectedItem.ToString(), "Şifre Girişi", "", 50, 50);
            if (port1.IsOpen)
            {
                port1.WriteLine("ssidsend");
                port1.WriteLine(comboBox1.SelectedItem.ToString()+";");
                port1.WriteLine("passsend");
                port1.WriteLine(sifre + ";");
            }
        }
    }
}
