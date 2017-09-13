/*Form2.cs*/

/*2017-07-01
    狩野 達哉*/

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
    public partial class Form2 : Form
    {
        //メンバ変数
        //テキストボックスのテキストを格納
        internal string feeling;

        public Form2()
        {
            InitializeComponent();
        }

        //List6-7
        //buttonOKクリックイベントハンドラ
        //OKが押された時にテキストボックスのテキストを代入
        private void buttonOK_Click(object sender, EventArgs e)
        {
            feeling = textBoxFeeling.Text;
        }
    }
}
