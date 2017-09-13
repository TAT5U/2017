/*Form2.cs*/

/*2017-08-08
    狩野 達哉
        Chap6-Ex*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MultiAlarm
{
    public partial class Form2 : Form
    {
        //設定したアラームの時・分
        internal int alarmHour = 0, alarmMinute = 0;

        public Form2()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form2_Load(object sender, EventArgs e)
        {
            //フォームの設定
            Text = "時刻設定";
            FormBorderStyle = FormBorderStyle.FixedToolWindow;

            //アラームの時ラベルの設定
            labelAlmHour.AutoSize = true;
            labelAlmHour.Text = "時";

            //アラームの分ラベルの設定
            labelAlmMnt.AutoSize = true;
            labelAlmMnt.Text = "分";

            //アラームの時のニューメリックの設定
            numericUpDownAlmHour.Maximum = 23;
            numericUpDownAlmHour.TextAlign = HorizontalAlignment.Right;

            //アラームの分のニューメリックの設定
            numericUpDownAlmMnt.Maximum = 59;
            numericUpDownAlmMnt.TextAlign = HorizontalAlignment.Right;

            //OKボタンの設定
            buttonOK.Text = "OK";
            buttonOK.DialogResult = DialogResult.OK;
            buttonOK.Click += new EventHandler(buttonOK_Click);

            //キャンセルボタンの設定
            buttonCancel.Text = "キャンセル";
            buttonCancel.DialogResult = DialogResult.Cancel;

            //現在時刻を表示
            numericUpDownAlmHour.Value = DateTime.Now.Hour;
            numericUpDownAlmMnt.Value = DateTime.Now.Minute;
        }

        //buttonOKイベントハンドラ
        private void buttonOK_Click(object sender, EventArgs e)
        {
            //ニューメリックの値を渡す
            alarmHour = (int)numericUpDownAlmHour.Value;
            alarmMinute = (int)numericUpDownAlmMnt.Value;
        }
    }
}
