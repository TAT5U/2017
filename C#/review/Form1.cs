/*2017-04-18
    狩野 達哉
        C#の復習用プログラム*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace review
{
    public partial class Form1 : Form
    {
        //カウントする変数
        int cnt = 0;

        //日付の変数
        DateTime dt = DateTime.Now;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //フォームのサイズを500,500に変更
            this.Width = 500;
            this.Height = 500;

            //label1の位置を変更&テキストをカウントの値に変更
            this.label1.Location= new Point(this.Width/2,this.Height/2);
            this.label1.Text = cnt.ToString();

            //label2の位置を変更&現在の時刻を表示
            this.label2.Location = new Point(this.Width / 2, this.Height / 4);
            this.label2.Text = dt.Year + "年" + dt.Month + "月" + dt.Day + "日" + dt.Hour + "時" + dt.Minute + "分" + dt.Second + "秒";

            //
            this.button1.Location = new Point(this.label1.Width, this.label1.Height);
            this.button1.Text = "カウント";

            //タイマー起動
            timer1.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //カウント
            cnt++;

            //label1のテキスト内容を変更(カウントした値に変更)
            this.label1.Text = cnt.ToString();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //日付の変数に更新
            dt = DateTime.Now;

            //現在の時刻を表示
            this.label2.Text = dt.Year + "年" + dt.Month + "月" + dt.Day + "日" + dt.Hour + "時" + dt.Minute + "分" + dt.Second + "秒";
        }
    }
}
