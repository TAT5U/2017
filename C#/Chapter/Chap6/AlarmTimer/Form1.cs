/*Form1.cs*/

/*2017-08-06
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
    //List6-14
    //メンバ変数の設定
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
        
        //List6-15
        //フォーム1起動時のイベントハンドラ
        private void Form1_Load(object sender, EventArgs e)
        {
            //フォームの設定
            Text = "アラーム&タイマー";
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            BackColor = Color.MediumBlue;

            //時刻を表示するラベルの設定
            labelTime.AutoSize = true;
            labelTime.Text = "12:59:59";
            labelTime.Font = new Font("MS UI Gothic", 28, FontStyle.Bold);
            labelTime.ForeColor = Color.Yellow;

            //日付を表示するラベルの設定
            labelDate.AutoSize = true;
            labelDate.Text = "YYYY年MM月DD日(曜)";
            labelDate.ForeColor = Color.White;

            //アラーム時刻を表示するラベルの設定
            labelStatus.AutoSize = true;
            labelStatus.Text = "♪ hh:mm:ss";
            labelStatus.ForeColor = Color.Aqua;

            //設定ボタンの設定
            buttonSet.Text = "設定";
            buttonSet.BackColor = Color.MediumBlue;
            buttonSet.ForeColor = Color.White;
            buttonSet.Click += new EventHandler(buttonSet_Click);

            //リセットボタンの設定
            buttonReset.Text = "リセット";
            buttonReset.BackColor = Color.MediumBlue;
            buttonReset.ForeColor = Color.White;
            buttonReset.Click += new EventHandler(buttonReset_Click);

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

        //List6-16
        //timer1イベントハンドラ
        //private void timer1_Tick(object sender, EventArgs e)
        //{
        //    //時刻と日付が毎秒毎日更新される
        //    DateTime now = DateTime.Now;
        //    labelTime.Text = now.ToLongTimeString();
        //    labelDate.Text = DateTime.Today.ToString("yyyy年MM月dd日(ddd)");
        //}

        //List6-24
        //timer1イベントハンドラ
        //設定時刻になった時の処理
        private void timer1_Tick(object sender, EventArgs e)
        {
            //時刻と日付が毎秒毎日更新される
            DateTime now = DateTime.Now;
            labelTime.Text = now.ToLongTimeString();
            labelDate.Text = DateTime.Today.ToString("yyyy年MM月dd日(ddd)");

            //設定したアラームの時間が来たとき
            if (alarmSetFlag == true)
            {
                if ((alarmHour == now.Hour) && (alarmMinute == now.Minute) && (alarmSecond == now.Second))
                {
                    alarmSetFlag = false;MessageBox.Show("時間ですよ！", "アラーム", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    labelStatus.Text = "";
                }
            }
        }

        //List6-17
        //buttonSetイベントハンドラ
        //private void buttonSet_Click(object sender, EventArgs e)
        //{
        //    //Form2を生成してモーダルダイアログで表示
        //    Form2 form2 = new Form2();
        //    form2.ShowDialog();
        //    form2.Dispose();
        //}

        //List6-23
        //buttonSetイベントハンドラ
        //設定ダイアログを閉じたときの処理
        private void buttonSet_Click(object sender, EventArgs e)
        {
            //Form2を生成
            Form2 form2 = new Form2();

            //Form2でOKが押されたらアラームの設定を行う
            if (form2.ShowDialog() == DialogResult.OK)
            {
                alarmSetFlag = true;
                alarmHour = form2.alarmHour;
                alarmMinute = form2.alarmMinute;
                alarmSecond = form2.alarmSecond;
                labelStatus.Text = "♪" + alarmHour.ToString("00") + ":" + alarmMinute.ToString("00") + ":" + alarmSecond.ToString("00");
            }

            //Form2を解放
            form2.Dispose();
        }

        //List6-25
        //buttonResetイベントハンドラ
        private void buttonReset_Click(object sender, EventArgs e)
        {
            //キャンセルが押されたらアラームのフラグをfalseにする
            //アラーム時間を表示するラベルのテキストを初期化
            alarmSetFlag = false;
            labelStatus.Text = "";
        }
    }
}
