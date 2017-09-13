/*2017-04-24
    狩野 達哉
        Chap-4*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GradeCheck
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //List4-4
        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //タイトル・ラベル・テキストボックス・ボタンのテキストを変更
            this.Text = "成績判定";
            label1.Text = "科目";
            label2.Text = "数学";
            label3.Text = "物理";
            label4.Text = "英語";
            label5.Text = "%";
            label6.Text = "%";
            label7.Text = "%";
            label8.Text = "出席率";
            label9.Text = "得点";
            label10.Text = "判定結果";
            label11.Text = "平均点と比較";
            labelResultM.Text = "";
            labelResultP.Text = "";
            labelResultE.Text = "";
            labelCompAvgM.Text = "";
            labelCompAvgP.Text = "";
            labelCompAvgE.Text = "";
            textBoxAttendanceM.Text = "0.0";
            textBoxAttendanceP.Text = "0.0";
            textBoxAttendanceE.Text = "0.0";
            textBoxScoreM.Text = "0";
            textBoxScoreP.Text = "0";
            textBoxScoreE.Text = "0";
            buttonJudge.Text = "判定";
            buttonReset.Text = "リセット";
        }

        //List4-8
        //判定が押されたとき
        private void buttonJudge_Click(object sender, EventArgs e)
        {
            //出席率を不動小数点数値に変換
            double AttendanceM, AttendanceP, AttendanceE;

            //出席率を変換するメソッドの呼び出し
            textToValue(textBoxAttendanceM.Text, out AttendanceM);
            textToValue(textBoxAttendanceP.Text, out AttendanceP);
            textToValue(textBoxAttendanceE.Text, out AttendanceE);

            //点数を整数値に変換
            int scoreM, scoreP, scoreE;

            //点数を変換するメソッドの呼び出し
            textToValue(textBoxScoreM.Text, out scoreM);
            textToValue(textBoxScoreP.Text, out scoreP);
            textToValue(textBoxScoreE.Text, out scoreE);

            //点数を判定するメソッドを呼び出して判定結果を格納
            labelResultM.Text = scoreJudge(AttendanceM, scoreM);
            labelResultP.Text = scoreJudge(AttendanceP, scoreP);
            labelResultE.Text = scoreJudge(AttendanceE, scoreE);

            //平均値と比較して以上か未満か判定して表示
            labelCompAvgM.Text = averageJudge(scoreM, 1);
            labelCompAvgP.Text = averageJudge(scoreP, 1);
            labelCompAvgE.Text = averageJudge(scoreE, 1);
        }

        //List4-5
        //テキストを不動小数点数に変換するメソッド
        private void textToValue(string text,out double val)
        {
            if (double.TryParse(text,out val)==false)
            {
                val = -1.0;
            }
        }

        //テキストを整数値に変換するメソッド
        private void textToValue(string text,out int val)
        {
            if (int.TryParse(text,out val)==false)
            {
                val = -1;
            }
        }

        //List4-6
        //点数を判定するメソッド
        private string scoreJudge(double Attendance,int score)
        {
            //判定結果を格納する変数
            string result;

            //出席率と点数が範囲外の場合エラー表示
            //出席率が80%未満で不合格となる
            if (Attendance<0.0||Attendance>100.0||score<0||score>100)
            {
                result = "エラー";
            }
            else if (Attendance>=80.0)
            {
                //点数が60未満で不合格
                if (score>=80)
                {
                    result = "A判定";
                }
                else if (score>=70)
                {
                    result = "B判定";
                }
                else if (score>=60)
                {
                    result = "C判定";
                }
                else
                {
                    result = "不合格";
                }
            }
            else
            {
                result = "不合格";
            }

            //判定結果を返す
            return result;
        }

        //List4-7
        //平均点と比較するメソッド
        private string averageJudge(int score,int subject)
        {
            //判定結果を格納する変数
            string result;

            //教科の平均点を格納する変数
            int average;

            //点数が範囲外のときエラー表示
            if (score<0||score>100)
            {
                return "エラー";
            }

            //教科を判断して平均点を格納
            if (subject==1)
            {
                average = 73;
            }
            else if (subject==2)
            {
                average = 65;
            }
            else if (subject==3)
            {
                average = 77;
            }
            else
            {
                return "エラー";
            }

            //点数と平均点を比較して以上か未満か判定
            if (score>=average)
            {
                result = "平均点以上";
            }
            else
            {
                result = "平均点未満";
            }

            //判定結果を返す
            return result;
        }

        //List4-9
        //リセットが押されたとき
        private void buttonReset_Click(object sender, EventArgs e)
        {
            //すべてのテキストボックスとラベルの内容を初期化する
            textBoxAttendanceM.Text = "0.0";
            textBoxAttendanceP.Text = "0.0";
            textBoxAttendanceE.Text = "0.0";
            textBoxScoreM.Text = "0";
            textBoxScoreP.Text = "0";
            textBoxScoreE.Text = "0";
            labelResultM.Text = "";
            labelResultP.Text = "";
            labelResultE.Text = "";
            labelCompAvgM.Text = "";
            labelCompAvgP.Text = "";
            labelCompAvgE.Text = "";
        }
    }
}
