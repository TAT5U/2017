/*2017-04-20
    狩野 達哉
        Chap-3*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AddTax
{
    public partial class Form1 : Form
    {
        //入力された金額・税込みの金額・消費税率の変数を宣言
        int money = 0;

        public Form1()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //タイトル・ラベル・テキストボックスのテキストを変更
            this.Text = "消費税追加";
            label1.Text = "金額";
            label2.Text = "税込み金額";
            textBoxMoney.Text = "0";
            label3.Text = "円";
            labelAddTax.Text = "0円";
            buttonAddTax.Text = "消費税追加";
        }

        //消費税追加が押されたとき
        private void buttonAddTax_Click(object sender, EventArgs e)
        {
            //List4-2
            //例外処理
            //金額が不正なときはメッセージを表示させる
            //try
            //{
            //    //入力された金額をint型に変換して格納
            //    money = int.Parse(textBoxMoney.Text);

            //    //消費税込みの金額の計算メソッドの呼び出し
            //    money = addTax(money);

            //    //消費税込みの金額を表示
            //    labelAddTax.Text = money + "円";
            //}
            //catch (FormatException ex)
            //{
            //    //エラーの時にメッセージを表示する
            //    labelAddTax.Text = ex.Message;
            //}

            //List4-3
            //TryParseを使った処理
            //簡単な例外の処理で使用
            //変換時にfalseがでたらエラーとみなす
            if (int.TryParse(textBoxMoney.Text, out money) == true)
            {
                //消費税込みの金額の計算メソッドの呼び出し
                money = addTax(money);

                //消費税込みの金額を表示
                labelAddTax.Text = money + "円";
            }
            else
            {
                //エラーの時にメッセージを表示する
                labelAddTax.Text = "入力文字列の形式が正しくありません。";
            }

        }

        //List4-1
        //消費税込み金額の計算
        private int addTax(int m)
        {
            //消費税率
            const double tax = 0.08;

            //戻り値で消費税込み金額を返す
            return (int)(m * (1 + tax));
        }
    }
}
