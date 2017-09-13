/*2017-04-20
    狩野 達哉
        Chap-2-Ex*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControlCheck
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
            //タイトル・チェックボックス・ラジオボタン・ラベル・ニューメリックのテキストを変更
            this.Text = "コントロールの状態";
            checkBox1.Text = "チェックボックス";
            radioButton1.Text = "ラジオボタン1";
            radioButton2.Text = "ラジオボタン2";
            label1.Text = "ニューメリックアップダウン";
            labelCheckBox.Text = "チェックボックス:" + checkBox1.Checked;
            labelRadioButton1.Text = "ラジオボタン1:" + radioButton1.Checked;
            labelRadioButton2.Text = "ラジオボタン2:" + radioButton2.Checked;
            labelNumericUpDown.Text = "数値:" + numericUpDown1.Value;

        }

        //チェックボックスが変わったとき
        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            //状態を表示
            labelCheckBox.Text = "チェックボックス:" + checkBox1.Checked;
        }

        //ラジオボタン1が変わったとき
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            //状態を表示
            labelRadioButton1.Text = "ラジオボタン1:" + radioButton1.Checked;
        }

        //ラジオボタン2が変わったとき
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            //状態を表示
            labelRadioButton2.Text = "ラジオボタン2:" + radioButton2.Checked;
        }

        //ニューメリックの数値が変わったとき
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            //数値を表示
            labelNumericUpDown.Text = "数値:" + numericUpDown1.Value;
        }
    }
}
