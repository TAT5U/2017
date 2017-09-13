using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;

namespace GradeCheck2
{
    // List7-12
    // Subject class
    class Subject
    {
        //
        private double average = 0.0f;
        private int totalHours = 0;
        private int passScore = 0;


        //
        public Subject(string name, double average, int totalHours, int passScore)
        {
            
        }

        //
        public string Name
        {
            get;
            set;
        }
        public double Average
        {
            get
            {
                return average;
            }
            set
            {
                if ((value >= 0.0f)&&(value <= 100.0f))
                {
                    average = value;
                }
                else
                {
                    MessageBox.Show("平均点の入力が正しくありません。", "確認");
                    average = 0.0f;
                }
            }
        }
        public int TotalHours
        {
            get
            {
                return totalHours;
            }
            set
            {
                if (value >= 0)
                {
                    totalHours = value;
                }
                else
                {
                    MessageBox.Show("総合時数の入力が正しくありません。", "確認");
                    totalHours = 0;
                }
            }
        }
        public int PassScore
        {
            get
            {
                return passScore;
            }
            set
            {
                if ((value >= 0.0f)&&(value <= 100.0f))
                {
                    passScore = value;
                }
                else
                {
                    MessageBox.Show("合格点の入力が正しくありません。", "確認");
                    passScore = 0;
                }
            }
        }



    }
}
