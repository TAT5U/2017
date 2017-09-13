/*Form2.cs*/

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
    //List6-21
    //メンバ変数の設定
    public partial class Form2 : Form
    {
        //設定したアラームの時・分・秒
        internal int alarmHour = 0, alarmMinute = 0, alarmSecond = 0;

        public Form2()
        {
            InitializeComponent();
        }

        //List6-18
        //フォーム1起動時のイベントハンドラ
        private void Form2_Load(object sender, EventArgs e)
        {
            //フォームの設定
            Text = "設定";
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            BackColor = Color.MediumBlue;

            //アラームのラジオボタンの設定
            radioButtonAlarm.Text = "アラーム";
            radioButtonAlarm.ForeColor = Color.White;

            //タイマーのラジオボタンの設定
            radioButtonTimer.Text = "タイマー";
            radioButtonTimer.ForeColor = Color.White;

            //アラームの時ラベルの設定
            labelAlmHour.AutoSize = true;
            labelAlmHour.Text = "時";
            labelAlmHour.ForeColor = Color.White;

            //アラームの分ラベルの設定
            labelAlmMnt.AutoSize = true;
            labelAlmMnt.Text = "分";
            labelAlmMnt.ForeColor = Color.White;

            //タイマーの分ラベルの設定
            labelTimMnt.AutoSize = true;
            labelTimMnt.Text = "分";
            labelTimMnt.ForeColor = Color.White;

            //タイマーの秒ラベルの設定
            labelTimSec.AutoSize = true;
            labelTimSec.Text = "秒後";
            labelTimSec.ForeColor = Color.White;

            //アラームの時のニューメリックの設定
            numericUpDownAlmHour.Maximum = 23;
            numericUpDownAlmHour.TextAlign = HorizontalAlignment.Right;
            numericUpDownAlmHour.ValueChanged += new EventHandler(numericUpDownAlm_ValueChanged);

            //アラームの分のニューメリックの設定
            numericUpDownAlmMnt.Maximum = 59;
            numericUpDownAlmMnt.TextAlign = HorizontalAlignment.Right;
            numericUpDownAlmMnt.ValueChanged += new EventHandler(numericUpDownAlm_ValueChanged);

            //タイマーの分のニューメリックの設定
            numericUpDownTimMnt.Maximum = 59;
            numericUpDownTimMnt.TextAlign = HorizontalAlignment.Right;
            numericUpDownTimMnt.ValueChanged += new EventHandler(numericUpDownTim_ValueChanged);

            //タイマーの秒のニューメリックの設定
            numericUpDownTimSec.Maximum = 59;
            numericUpDownTimSec.TextAlign = HorizontalAlignment.Right;
            numericUpDownTimSec.ValueChanged += new EventHandler(numericUpDownTim_ValueChanged);

            //OKボタンの設定
            buttonOK.Text = "OK";
            buttonOK.DialogResult = DialogResult.OK;
            buttonOK.BackColor = Color.MediumBlue;
            buttonOK.ForeColor = Color.White;
            buttonOK.Click += new EventHandler(buttonOK_Click);

            //キャンセルボタンの設定
            buttonCancel.Text = "キャンセル";
            buttonCancel.DialogResult = DialogResult.Cancel;
            buttonCancel.BackColor = Color.MediumBlue;
            buttonCancel.ForeColor = Color.White;

            //現在時刻を表示
            numericUpDownAlmHour.Value = DateTime.Now.Hour;
            numericUpDownAlmMnt.Value = DateTime.Now.Minute;
        }

        //List6-19
        //AlmのValueChangedイベントハンドラ
        private void numericUpDownAlm_ValueChanged(object sender, EventArgs e)
        {
            //アラームのほうのニューメリックの値が変更されたら
            //自動的にラジオボタンのチェックも変える
            radioButtonAlarm.Checked = true;
        }

        //List6-20
        //TimのValueChangedイベントハンドラ
        private void numericUpDownTim_ValueChanged(object sender, EventArgs e)
        {
            //タイマーのほうのニューメリックの値が変更されたら
            //自動的にラジオボタンのチェックも変える
            radioButtonTimer.Checked = true;
        }

        //List6-22
        ////buttonOKイベントハンドラ
        private void buttonOK_Click(object sender, EventArgs e)
        {
            //ラジオボタンのチェックによって処理を変更する
            //タイマーのほうは「秒後」なのでTimeSpanとAddを使って時間を設定する
            if (radioButtonAlarm.Checked == true)
            {
                alarmHour = (int)numericUpDownAlmHour.Value;
                alarmMinute = (int)numericUpDownAlmMnt.Value;
                alarmSecond = 0;
            }
            else
            {
                DateTime dtNow = DateTime.Now;
                TimeSpan addSpan = new TimeSpan(0, (int)numericUpDownTimMnt.Value, (int)numericUpDownTimSec.Value);

                DateTime setTime = dtNow.Add(addSpan);
                alarmHour = setTime.Hour;
                alarmMinute = setTime.Minute;
                alarmSecond = setTime.Second;
            }
        }
    }
}
