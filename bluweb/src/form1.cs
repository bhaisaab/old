using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        #region OpenFile
        public void openfile()
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "HTML Files(.htm)|*.htm";
            string path = open.FileName;

            if (open.ShowDialog() == DialogResult.OK)
            {
                webBrowser1.Url = new System.Uri(open.FileName, System.UriKind.Absolute);
                if (webBrowser1.Visible == false)
                    webBrowser1.Visible = true;
           
            }
        }
        #endregion

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }

        private void webBrowser1_DocumentCompleted_1(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.webBrowser1.Url = new System.Uri("C:\\Lectures\\ProgrammingC-YK_Videos\\1.Basics\\Lec01-CIntro\\Lecture01_Intro.htm", System.UriKind.Absolute);
            this.webBrowser1.Visible= true;
        }

        private void toolStripLabel5_Click(object sender, EventArgs e)
        {
            Application.Exit();  
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            button1.Visible = true;
            button2.Visible = true;
            richTextBox1.Visible = true;
        }

        private void toolStripLabel3_Click(object sender, EventArgs e)
        {
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            openfile();
        }

        private void toolStripLabel6_Click(object sender, EventArgs e)
        {
            openfile();
        }


        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            webBrowser1.GoBack();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            webBrowser1.GoForward();
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            webBrowser1.GoHome();
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            webBrowser1.Stop();
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            webBrowser1.Refresh();
        }

        

        private void webBrowser1_DocumentCompleted_2(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            richTextBox1.Visible = false;
        }

        private void toolStripLabel4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            button1.Visible = false;
            button2.Visible = false;
            richTextBox1.Visible = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("This program was made for personal use ONLY.\nThe collection of videos and stuff were extracted because of time consuming activation of Quest courseware.\nSo, I made a backup-ready to use PACKAGE by hacking into registry and cracking encrpted files!\nTHIS PROGRAM AND COURSEWARE ARE RESTRICTED TO MY PERSONAL USE ONLY!\n\nB!ueZone a.k.a. C!der");
    
        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }

        
    }
}
