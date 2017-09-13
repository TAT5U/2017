/*Form1.cs*/

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
    public partial class Form1 : Form
    {
        //アラームセット中のフラグ
        private bool[] alarmSetFlag = new bool[3] { false, false, false };

        //設定したアラームの時・分
        private int[] alarmHour = new int[3] { 0, 0, 0 }, alarmMinute = new int[3] { 0, 0, 0 };

        public Form1()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //フォームの設定
            Text = "アラーム";
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            BackColor = Color.MediumBlue;

            //時刻を表示するラベルの設定
            labelTime.AutoSize = true;
            labelTime.Font = new Font("MS UI Gothic", 28, FontStyle.Bold);
            labelTime.ForeColor = Color.Yellow;

            //アラーム時刻1を表示するチェックボックスの設定
            checkBoxSetTime1.AutoSize = true;
            checkBoxSetTime1.Text = "00:00";
            checkBoxSetTime1.Font = new Font("MS UI Gothic", 20, FontStyle.Regular);
            checkBoxSetTime1.ForeColor = Color.Aqua;
            checkBoxSetTime1.AutoCheck = false;
            checkBoxSetTime1.TabStop = false;

            //アラーム時刻2を表示するチェックボックスの設定
            checkBoxSetTime2.AutoSize = true;
            checkBoxSetTime2.Text = "00:00";
            checkBoxSetTime2.Font = new Font("MS UI Gothic", 20, FontStyle.Regular);
            checkBoxSetTime2.ForeColor = Color.Aqua;
            checkBoxSetTime2.AutoCheck = false;
            checkBoxSetTime2.TabStop = false;

            //アラーム時刻3を表示するチェックボックスの設定
            checkBoxSetTime3.AutoSize = true;
            checkBoxSetTime3.Text = "00:00";
            checkBoxSetTime3.Font = new Font("MS UI Gothic", 20, FontStyle.Regular);
            checkBoxSetTime3.ForeColor = Color.Aqua;
            checkBoxSetTime3.AutoCheck = false;
            checkBoxSetTime3.TabStop = false;

            //設定ボタン1の設定
            buttonSet1.Text = "設定";
            buttonSet1.BackColor = Color.MediumBlue;
            buttonSet1.ForeColor = Color.White;
            buttonSet1.Click += new EventHandler(buttonSet1_Click);

            //設定ボタン2の設定
            buttonSet2.Text = "設定";
            buttonSet2.BackColor = Color.MediumBlue;
            buttonSet2.ForeColor = Color.White;
            buttonSet2.Click += new EventHandler(buttonSet2_Click);

            //設定ボタン3の設定
            buttonSet3.Text = "設定";
            buttonSet3.BackColor = Color.MediumBlue;
            buttonSet3.ForeColor = Color.White;
            buttonSet3.Click += new EventHandler(buttonSet3_Click);

            //タイマーの設定
            timer1.Interval = 1000;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            //時刻を表示
            labelTime.Text = DateTime.Now.ToLongTimeString();
        }

        //timer1イベントハンドラ
        private void timer1_Tick(object sender, EventArgs e)
        {
            //カウント変数
            int i = 0;

            //時刻と日付が毎秒毎日更新される
            DateTime now = DateTime.Now;
            labelTime.Text = now.ToLongTimeString();

            while (i < 3)
            {
                //設定したアラームの時間が来たとき
                if (alarmSetFlag[i] == true)
                {
                    if ((alarmHour[i] == now.Hour) && (alarmMinute[i] == now.Minute))
                    {
                        alarmSetFlag[i] = false;
                        MessageBox.Show("時間ですよ！", "アラーム" + (i + 1).ToString(), MessageBoxButtons.OK, MessageBoxIcon.Information);

                        //チェックボックスの名前をカウント変数で判断してテキストを初期化
                        Control ckBoxName = Controls["checkBoxSetTime" + (i + 1).ToString()];
                        ((CheckBox)ckBoxName).Text = "00:00";

                        //チェックは外す
                        ((CheckBox)ckBoxName).Checked = false;
                    }
                }
                i++;
            }
            i = 0;
        }

        //buttonSet1イベントハンドラ
        private void buttonSet1_Click(object sender, EventArgs e)
        {
            //Form2を生成
            Form2 form2 = new Form2();

            //Form2でOKが押されたらアラームの設定を行う
            if (form2.ShowDialog() == DialogResult.OK)
            {
                //ボタンのNameの最後尾の数字で判断
                alarmSetFlag[int.Parse(buttonSet1.Name.Substring(int.Parse(buttonSet1.Name.Length.ToString()) - 1)) - 1] = true;
                alarmHour[int.Parse(buttonSet1.Name.Substring(int.Parse(buttonSet1.Name.Length.ToString()) - 1)) - 1] = form2.alarmHour;
                alarmMinute[int.Parse(buttonSet1.Name.Substring(int.Parse(buttonSet1.Name.Length.ToString()) - 1)) - 1] = form2.alarmMinute;
                checkBoxSetTime1.Text = alarmHour[int.Parse(buttonSet1.Name.Substring(int.Parse(buttonSet1.Name.Length.ToString()) - 1)) - 1].ToString("00") + ":" + alarmMinute[int.Parse(buttonSet1.Name.Substring(int.Parse(buttonSet1.Name.Length.ToString()) - 1)) - 1].ToString("00");
                checkBoxSetTime1.Checked = true;
            }

            //Form2を解放
            form2.Dispose();
        }

        //buttonSet2イベントハンドラ
        private void buttonSet2_Click(object sender, EventArgs e)
        {
            //Form2を生成
            Form2 form2 = new Form2();

            //Form2でOKが押されたらアラームの設定を行う
            if (form2.ShowDialog() == DialogResult.OK)
            {
                //ボタンのNameの最後尾の数字で判断
                alarmSetFlag[int.Parse(buttonSet2.Name.Substring(int.Parse(buttonSet2.Name.Length.ToString()) - 1)) - 1] = true;
                alarmHour[int.Parse(buttonSet2.Name.Substring(int.Parse(buttonSet2.Name.Length.ToString()) - 1)) - 1] = form2.alarmHour;
                alarmMinute[int.Parse(buttonSet2.Name.Substring(int.Parse(buttonSet2.Name.Length.ToString()) - 1)) - 1] = form2.alarmMinute;
                checkBoxSetTime2.Text = alarmHour[int.Parse(buttonSet2.Name.Substring(int.Parse(buttonSet2.Name.Length.ToString()) - 1)) - 1].ToString("00") + ":" + alarmMinute[int.Parse(buttonSet2.Name.Substring(int.Parse(buttonSet2.Name.Length.ToString()) - 1)) - 1].ToString("00");
                checkBoxSetTime2.Checked = true;
            }

            //Form2を解放
            form2.Dispose();
        }

        //buttonSet3イベントハンドラ
        private void buttonSet3_Click(object sender, EventArgs e)
        {
            //Form2を生成
            Form2 form2 = new Form2();

            //Form2でOKが押されたらアラームの設定を行う
            if (form2.ShowDialog() == DialogResult.OK)
            {
                //ボタンのNameの最後尾の数字で判断
                alarmSetFlag[int.Parse(buttonSet3.Name.Substring(int.Parse(buttonSet3.Name.Length.ToString()) - 1)) - 1] = true;
                alarmHour[int.Parse(buttonSet3.Name.Substring(int.Parse(buttonSet3.Name.Length.ToString()) - 1)) - 1] = form2.alarmHour;
                alarmMinute[int.Parse(buttonSet3.Name.Substring(int.Parse(buttonSet3.Name.Length.ToString()) - 1)) - 1] = form2.alarmMinute;
                checkBoxSetTime3.Text = alarmHour[int.Parse(buttonSet3.Name.Substring(int.Parse(buttonSet3.Name.Length.ToString()) - 1)) - 1].ToString("00") + ":" + alarmMinute[int.Parse(buttonSet3.Name.Substring(int.Parse(buttonSet3.Name.Length.ToString()) - 1)) - 1].ToString("00");
                checkBoxSetTime3.Checked = true;
            }

            //Form2を解放
            form2.Dispose();
        }
    }
}
