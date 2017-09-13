/*2017-04-20
    狩野 達哉
        Chap-2*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HelloCSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //フォームが読み込まれたとき
        private void Form1_Load(object sender, EventArgs e)
        {
            //タイトル・ラベル・ボタンのテキストを変更
            this.Text = "こんにちはC#";
            labelName.Text = "名前";
            labelMessage.Text = "";
            buttonOK.Text = "OK";
        }

        //OKボタンが押されたとき
        private void buttonOK_Click(object sender, EventArgs e)
        {
            //入力された名前で表示する
            labelMessage.Text = textBoxName.Text + "さん、こんにちは。";
        }
    }
}
