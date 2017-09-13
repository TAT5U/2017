/*Form1.cs*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    //List6-6
    //ボタンの追加
    public partial class Form1 : Form
    {
        //button1の宣言
        private Button button1;

        public Form1()
        {
            InitializeComponent();
        }

        //List6-8
        //Form1からForm2を開く処理
        private void Form1_Load(object sender, EventArgs e)
        {
            //button1の生成
            button1 = new Button();

            //button1の設定
            button1.Name = "button1";
            button1.Text = "開く";
            button1.Location = new Point(100, 100);
            button1.Size = new Size(80, 20);

            //イベントハンドラ登録
            button1.Click += new EventHandler(button1_Click);

            //フォームに追加
            Controls.Add(button1);
        }

        //イベントハンドラ定義
        private void button1_Click(object sender, EventArgs e)
        {
            //Form2生成
            Form2 form2 = new Form2();

            //モーダルダイアログで表示し、Form2でOKが押されたらテキストに代入
            if (form2.ShowDialog() == DialogResult.OK)
            {
                label1.Text = form2.feeling;
            }

            //Form2を解放
            form2.Dispose();
        }

        //List6-9
        //timer1イベントハンドラ
        private void timer1_Tick(object sender, EventArgs e)
        {
            //現在の日時を表示
            label2.Text = DateTime.Now.ToString();
        }
    }
}
