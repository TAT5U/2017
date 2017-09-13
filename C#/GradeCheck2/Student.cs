using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;

namespace GradeCheck2
{
    // List7-11
    // Student class
    class Student
    {
        //
        private int scoreM = 0;
        private int scoreP = 0;
        private int scoreE = 0;
        private int attendanceM = 0;
        private int attendanceP = 0;
        private int attendanceE = 0;

        //
        public Student(string name, int scoreM, int scoreP, int scoreE, int attendanceM, int attendanceP, int attendanceE)
        {
            Name = name;
            ScoreM = scoreM;
            ScoreP = scoreP;
            ScoreE = scoreE;
            AttendanceM = attendanceM;
            AttendanceP = attendanceP;
            AttendanceE = attendanceE;
            
        }

        //
        public string Name
        {
            get;
            set;
        }
        public int ScoreM
        {
            get
            {
                return scoreM;
            }
            set
            {
                scoreM = scoreCheck(value);
            }
        }
        public int ScoreP
        {
            get
            {
                return scoreP;
            }
            set
            {
                scoreP = scoreCheck(value);
            }
        }
        public int ScoreE
        {
            get
            {
                return scoreE;
            }
            set
            {
                scoreE = scoreCheck(value);
            }
        }
        public int AttendanceM
        {
            get
            {
                return attendanceM;
            }
            set
            {
                attendanceM = attendanceCheck(value);
            }
        }
        public int AttendanceP
        {
            get
            {
                return attendanceP;
            }
            set
            {
                attendanceP = attendanceCheck(value);
            }
        }
        public int AttendanceE
        {
            get
            {
                return attendanceE;
            }
            set
            {
                attendanceE = attendanceCheck(value);
            }
        }

        //
        private int scoreCheck(int val)
        {
            MessageBox.Show("得点が正しくありません。", "確認");
            return 0;
        }
        private int attendanceCheck(int val)
        {
            if (val >= 0)
            {
                return val;
            }
            else
            {
                MessageBox.Show("出席時数の入力が正しくありません。", "確認");
                return 0;
            }
        }
    }
}
