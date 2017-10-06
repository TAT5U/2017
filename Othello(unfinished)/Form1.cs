using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace オセロ
{

    public partial class Main : Form
    {
        int cnt = 0, player1 = 0, player2 = 0, xs = 1, ys = 0;
        List<data> za = new List<data>();
        int[] inf= new int[100];

        public struct data
        {
            public int x;
            public int y;
        }
        public struct data2
        {
            public int x;
            public int y;
        }
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            String str = null;
            int st = 0,cou=0;
            PictureBox p = null;
            p = (PictureBox)sender;
            str = p.Name.Substring(10);
            st = int.Parse(str);
           // if (st<=8)
           // {
           //     cou = 8;
           // }
           // if (st<=16)
           // {
           //     cou = 16;
           // }
           // if ( st <= 24)
           // {
           //     cou = 24;
           // }
           //if ( st <= 32)
           // {
           //     cou = 32;
           // }
           // if ( st <= 40)
           // {
           //     cou = 40;
           // }
           // if (st <= 48)
           // {
           //     cou = 48;
           // }
           //  if (st <= 56)
           // {
           //     cou = 56;
           // }
           // if ( st <= 64)
           // {
           //     cou = 64;
           // }
            //List<data2> lis = new List<data2>();
            //data2 d2;
            //d2.x = p.Location.X;
            //d2.y = p.Location.Y;
            //lis.Add(d2);
            //if (za)
            //{

            //}

            if (cnt==0)
            {
                if (inf[st+1]==2|| inf[st -1] == 2 || inf[st +8] == 2 || 
                                inf[st - 8] == 2 || inf[st +9] == 2 || inf[st - 9] == 2 || inf[st +7] == 2 || inf[st - 7] == 2)
                {
                    p.BackgroundImage = Image.FromFile(@"kuro.png");
                    cnt = 1;
                    //label1.Text = str;
                    // label1.Text += (string.Format("{0}", inf[1]));
                    inf[st] = 1;
                    p.Enabled = false;
                   // for (int i = 2; (i + st)==cou ; i++)
                   // {
                        if (inf[st + 2] == 1)
                        {
                            label1.Text = str;
                            Control[] pi = Controls.Find("pictureBox" + (st + 1).ToString(), true);
                            pi[0].BackgroundImage = Image.FromFile(@"kuro.png");
                        }
                   // }

                }

            }
            else if (cnt==1)
            {
                if (inf[st + 1] == 1 || inf[st - 1] == 1 || inf[st + 8] == 1 ||
                                inf[st - 8] == 1 || inf[st + 9] == 1 || inf[st - 9] == 1 || inf[st + 7] == 1 || inf[st - 7] == 1)
                {
                    p.BackgroundImage = Image.FromFile(@"siro.png");

                    cnt = 0;
                    inf[st] = 2;
                    p.Enabled = false;
                }
            }

        }

        public Main()
        {
            InitializeComponent();
            
            for (int x = 1; x <65; x++)
            {
                Control[] pic = Controls.Find("pictureBox" + x.ToString(), true);
                pic[0].Visible = true;
                pic[0].BackColor = Color.Transparent;
                inf[xs] = 3;
                xs++;
            }


        }

       public void Form1_Load(object sender, EventArgs e)
        {

            data d;

            panel1.BackgroundImage = Image.FromFile(@"banmen.png");
            pictureBox28.Visible = true;
            pictureBox28.BackgroundImage = Image.FromFile(@"kuro.png");
            d.x = pictureBox28.Location.X;
            d.y = pictureBox28.Location.Y;
            za.Add(d);
            inf[28] = 1;
            pictureBox28.Enabled = false;
            pictureBox37.Visible = true;
            pictureBox37.BackgroundImage = Image.FromFile(@"kuro.png");
            d.x = pictureBox37.Location.X;
            d.y = pictureBox37.Location.Y;
            za.Add(d);
            inf[37] = 1;
            pictureBox37.Enabled = false;
            pictureBox29.Visible = true;
            pictureBox29.BackgroundImage = Image.FromFile(@"siro.png");
            d.x = pictureBox29.Location.X;
            d.y = pictureBox29.Location.Y;
            za.Add(d);
            inf[29] = 2;
            pictureBox29.Enabled = false;
            pictureBox36.Visible = true;
            pictureBox36.BackgroundImage = Image.FromFile(@"siro.png");
            d.x = pictureBox36.Location.X;
            d.y = pictureBox36.Location.Y;
            za.Add(d);
            inf[36] = 2;
            pictureBox36.Enabled = false;
        }
    }
}
