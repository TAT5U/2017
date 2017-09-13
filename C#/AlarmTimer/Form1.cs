/*Form1.cs*/

/*2017-07-06
    狩野 達哉
        Chap6*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AlarmTimer
{
    public partial class Form1 : Form
    {
        //アラームセット中のフラグ
        private bool alarmSetFlag = false;

        //設定したアラームの時・分・秒
        private int alarmHour = 0, alarmMinute = 0, alarmSecond = 0;

        public Form1()
        {
            InitializeComponent();
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            //フォームの設定
            Text = "アラーム&タイマー";
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            BackColor = Color.MediumBlue;

            //時刻を表示するラベルの設定
            labelTime.Text = "12:59:59";
            labelTime.Font = new Font("MS UI Gothic", 28, FontStyle.Bold);
            labelTime.ForeColor = Color.Yellow;

            //日付を表示するラベルの設定
            labelDate.Text = "YYYY年MM月DD日(曜)";
            labelDate.ForeColor = Color.White;

            //アラーム時刻を表示するラベルの設定
            labelStatus.Text = "♪ hh:mm:ss";
            labelStatus.ForeColor = Color.Aqua;

            //設定ボタンの設定
            buttonSet.Text = "設定";
            buttonSet.BackColor = Color.MediumBlue;
            buttonSet.ForeColor = Color.White;

            //リセットボタンの設定
            buttonReset.Text = "リセット";
            buttonReset.BackColor = Color.MediumBlue;
            buttonReset.ForeColor = Color.White;

            //タイマーの設定
            timer1.Interval = 1000;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            //アラーム時刻の表示を初期化
            labelStatus.Text = "";

            //日付を表示
            labelDate.Text = DateTime.Today.ToString("yyyy年MM月dd日(ddd)");

            //時刻を表示
            labelTime.Text = DateTime.Now.ToLongTimeString();
        }

        //timer1イベントハンドラ
        private void timer1_Tick(object sender, EventArgs e)
        {
            //時刻と日付を毎秒毎日更新される
            DateTime now = DateTime.Now;
            labelTime.Text = now.ToLongTimeString();
            labelDate.Text = DateTime.Today.ToString("yyyy年MM月dd日(ddd)");
        }
    }
}
