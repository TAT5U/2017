using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GradeCheck2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            labelIdentityName.Text = "氏名";
            labelSubject.Text = "科目";
            labelM.Text = "数学";
            labelP.Text = "物理";
            labelE.Text = "英語";
            labelScore.Text = "得点";
            labelAttendance.Text = "出席時数";
            labelPassScore.Text = "合格点";
            labelAverage.Text = "平均点";
            labelResult.Text = "合否判定";
            labelCompAvg.Text = "平均点と比較";

            Text = "成績判定";
            textBoxScoreM.Text = "0";
            textBoxScoreM.TextAlign = HorizontalAlignment.Right;

            textBoxScoreP.Text = "0";
            textBoxScoreP.TextAlign = HorizontalAlignment.Right;

            textBoxScoreE.Text = "0";
            textBoxScoreE.TextAlign = HorizontalAlignment.Right;

            textBoxAttendanceM.Text = "0";
            textBoxAttendanceM.TextAlign = HorizontalAlignment.Right;

            textBoxAttendanceP.Text = "0";
            textBoxAttendanceP.TextAlign = HorizontalAlignment.Right;

            textBoxAttendanceE.Text = "0";
            textBoxAttendanceE.TextAlign = HorizontalAlignment.Right;


            labelTotalM.Text = "/100";

            labelTotalP.Text = "/100";

            labelTotalE.Text = "/100";

            labelPassScoreM.Text = "100";

            labelPassScoreP.Text = "100";

            labelPassScoreE.Text = "100";

            labelAverageM.Text = "100";

            labelAverageP.Text = "100";

            labelAverageE.Text = "100";

            labelName.Text = "○○さんの成績";
            labelName.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelResultM.Text = "合格";
            labelResultM.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelResultP.Text = "合格";
            labelResultP.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelResultE.Text = "合格";
            labelResultE.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelCompAvgM.Text = "平均点以上";
            labelCompAvgM.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelCompAvgP.Text = "平均点以上";
            labelCompAvgP.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            labelCompAvgE.Text = "平均点以上";
            labelCompAvgE.Font = new Font("MS UI Gothic", 12, FontStyle.Bold);

            buttonJudge.Text = "判定";
            buttonReset.Text = "リセット";
            
        }
    }
}
