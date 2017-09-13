/*2017-04-20
    狩野 達哉
        Chap-3-Ex*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SplitCost
{
    public partial class Form1 : Form
    {
        //金額を格納する変数・消費税率
        int money = 0, per = 0,remain = 0;
        double splitCost = 0.0;
        const double tax = 0.08;

        public Form1()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //タイトル・ラベル・テキストボックス・ボタンのテキストを変更
            this.Text = "割り勘";
            label1.Text = "税抜き金額";
            label2.Text = "人数";
            label3.Text = "円";
            label4.Text = "人";
            textBoxMoney.Text = "0";
            textBoxPer.Text = "0";
            labelPerTax.Text = "一人あたり";
            labelRemain.Text = "余り";
            buttonSplitCost.Text = "計算する";
        }

        //計算するボタンが押されたとき
        private void buttonSplitCost_Click(object sender, EventArgs e)
        {
            //例外処理
            //金額が不正なときはエラーのメッセージボックスを表示させる
            try
            {
                //入力された金額をint型に変換して格納
                money = int.Parse(textBoxMoney.Text);

                //例外処理
                //人数が不正なときはエラーのメッセージボックスを表示させる
                try
                {
                    //入力された人数をint型に変換して格納
                    per = int.Parse(textBoxPer.Text);

                    //入力された金額/人数の値を格納
                    splitCost = money / per;

                    //割り勘したときの余りを格納
                    remain = money % per;

                    //消費税をプラスして格納
                    splitCost *= (1 + tax);

                    //整数型で小数点以下をなくす
                    money = (int)splitCost;

                    //1人あたりの金額と余りの金額を表示
                    labelPerTax.Text = "一人あたり\n\n" + money + "円";
                    labelRemain.Text = "余り\n\n" + remain + "円";
                }
                catch (Exception)
                {
                    //人数が不正なときにエラー文を表示してテキストボックスの中身を消す
                    MessageBox.Show("人数が不正です", "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    textBoxPer.Text = "0";
                }

            }
            catch (Exception)
            {
                //金額が不正なときにエラー文を表示してテキストボックスの中身を消す
                MessageBox.Show("金額が不正です", "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxMoney.Text = "0";
            }

        }
    }
}
