/*2017-05-02
    狩野 達哉
        Chap-4-Ex*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WeekOfDay
{
    public partial class Form1 : Form
    {
        //西暦年・月・日・曜日を格納する変数
        int y, m, d, w;

        //閏年・1月,2月のフラグ
        bool LeapY = false, Mt = false;

        public Form1()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //タイトル・ラベル・テキストボックス・ボタンのテキストを変更
            this.Text = "曜日算出";
            label1.Text = "西暦年";
            label2.Text = "月";
            label3.Text = "日";
            labelWeek.Text = "";
            textBoxYear.Text = "";
            buttonCalcWeek.Text = "曜日算出";
        }

        //曜日算出が押されたとき
        private void buttonCalcWeek_Click(object sender, EventArgs e)
        {
            //西暦年の変換時にfalseが出たらエラーとみなす
            if (int.TryParse(textBoxYear.Text,out y)==true&&y>0)
            {
                //月の値を格納
                m = (int)numericUpDownMonth.Value;

                //日の値を格納
                d = (int)numericUpDownDay.Value;

                //閏年ならフラグをtrueにする
                if (LeapYear(y)==true)
                {
                    LeapY = true;
                }

                //月が1月,2月の時は昨年の分も合わせることで計算できるので
                //その判別のフラグをtrueにする
                if (m==1||m==2)
                {
                    Mt = true;
                }
                else
                {
                    Mt = false;
                }

                //西暦年・月に対する日が正しければ曜日を表示
                if (Month(m,d)==true)
                {
                    labelWeek.Text = CalcWeek(y, m, d);
                }
                else
                {
                    //エラーメッセージ
                    labelWeek.Text = "あり得ない日付";
                }
            }
            else
            {
                //エラーメッセージ
                labelWeek.Text = "西暦年エラー";
            }
        }
        //閏年かどうかの判定
        private bool LeapYear(int n)
        {
            if ((n%4==0)&&(n%100!=0||n%400==0))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //月に対する日が存在しているかどうかの判定
        private bool Month(int n,int m)
        {
            switch (n)
            {
                //31日の月
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (m<=31)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }

                //30日の月
                case 4:
                case 6:
                case 9:
                case 11:
                    if (m<=30)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
            }

            //2月は閏年かどうかも加味する
            if (LeapY==true)
            {
                //閏年のときは29日まで
                if (m<=29)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                //そうじゃないときは28日まで
                if (m<=28)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }


        //曜日の算出
        private string CalcWeek(int year,int month,int day)
        {
            //1月,2月のとき
            //昨年も含める
            if (Mt==true)
            {
                year = year - 1;
                month = month + 12;
            }

            //曜日計算(数値で判別)
            w = (5 * year / 4 - year / 100 + year / 400 + (26 * month + 16) / 10 + day) % 7;

            //曜日判定
            if (w==0)
            {
                return "日曜日";
            }
            else if (w==1)
            {
                return "月曜日";
            }
            else if (w==2)
            {
                return "火曜日";
            }
            else if (w==3)
            {
                return "水曜日";
            }
            else if (w==4)
            {
                return "木曜日";
            }
            else if (w==5)
            {
                return "金曜日";
            }
            else
            {
                return "土曜日";
            }
        }
    }
}
