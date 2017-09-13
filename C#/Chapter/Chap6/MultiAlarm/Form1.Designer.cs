namespace MultiAlarm
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.labelTime = new System.Windows.Forms.Label();
            this.checkBoxSetTime1 = new System.Windows.Forms.CheckBox();
            this.checkBoxSetTime2 = new System.Windows.Forms.CheckBox();
            this.checkBoxSetTime3 = new System.Windows.Forms.CheckBox();
            this.buttonSet1 = new System.Windows.Forms.Button();
            this.buttonSet2 = new System.Windows.Forms.Button();
            this.buttonSet3 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // labelTime
            // 
            this.labelTime.AutoSize = true;
            this.labelTime.Location = new System.Drawing.Point(45, 23);
            this.labelTime.Name = "labelTime";
            this.labelTime.Size = new System.Drawing.Size(35, 12);
            this.labelTime.TabIndex = 0;
            this.labelTime.Text = "label1";
            // 
            // checkBoxSetTime1
            // 
            this.checkBoxSetTime1.AutoSize = true;
            this.checkBoxSetTime1.Location = new System.Drawing.Point(12, 83);
            this.checkBoxSetTime1.Name = "checkBoxSetTime1";
            this.checkBoxSetTime1.Size = new System.Drawing.Size(80, 16);
            this.checkBoxSetTime1.TabIndex = 0;
            this.checkBoxSetTime1.Text = "checkBox1";
            this.checkBoxSetTime1.UseVisualStyleBackColor = true;
            // 
            // checkBoxSetTime2
            // 
            this.checkBoxSetTime2.AutoSize = true;
            this.checkBoxSetTime2.Location = new System.Drawing.Point(12, 133);
            this.checkBoxSetTime2.Name = "checkBoxSetTime2";
            this.checkBoxSetTime2.Size = new System.Drawing.Size(80, 16);
            this.checkBoxSetTime2.TabIndex = 0;
            this.checkBoxSetTime2.Text = "checkBox2";
            this.checkBoxSetTime2.UseVisualStyleBackColor = true;
            // 
            // checkBoxSetTime3
            // 
            this.checkBoxSetTime3.AutoSize = true;
            this.checkBoxSetTime3.Location = new System.Drawing.Point(12, 181);
            this.checkBoxSetTime3.Name = "checkBoxSetTime3";
            this.checkBoxSetTime3.Size = new System.Drawing.Size(80, 16);
            this.checkBoxSetTime3.TabIndex = 0;
            this.checkBoxSetTime3.Text = "checkBox3";
            this.checkBoxSetTime3.UseVisualStyleBackColor = true;
            // 
            // buttonSet1
            // 
            this.buttonSet1.Location = new System.Drawing.Point(118, 83);
            this.buttonSet1.Name = "buttonSet1";
            this.buttonSet1.Size = new System.Drawing.Size(75, 23);
            this.buttonSet1.TabIndex = 0;
            this.buttonSet1.Text = "button1";
            this.buttonSet1.UseVisualStyleBackColor = true;
            // 
            // buttonSet2
            // 
            this.buttonSet2.Location = new System.Drawing.Point(118, 133);
            this.buttonSet2.Name = "buttonSet2";
            this.buttonSet2.Size = new System.Drawing.Size(75, 23);
            this.buttonSet2.TabIndex = 1;
            this.buttonSet2.Text = "button2";
            this.buttonSet2.UseVisualStyleBackColor = true;
            // 
            // buttonSet3
            // 
            this.buttonSet3.Location = new System.Drawing.Point(118, 181);
            this.buttonSet3.Name = "buttonSet3";
            this.buttonSet3.Size = new System.Drawing.Size(75, 23);
            this.buttonSet3.TabIndex = 2;
            this.buttonSet3.Text = "button3";
            this.buttonSet3.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(217, 235);
            this.Controls.Add(this.buttonSet3);
            this.Controls.Add(this.buttonSet2);
            this.Controls.Add(this.buttonSet1);
            this.Controls.Add(this.checkBoxSetTime3);
            this.Controls.Add(this.checkBoxSetTime2);
            this.Controls.Add(this.checkBoxSetTime1);
            this.Controls.Add(this.labelTime);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelTime;
        private System.Windows.Forms.CheckBox checkBoxSetTime1;
        private System.Windows.Forms.CheckBox checkBoxSetTime2;
        private System.Windows.Forms.CheckBox checkBoxSetTime3;
        private System.Windows.Forms.Button buttonSet1;
        private System.Windows.Forms.Button buttonSet2;
        private System.Windows.Forms.Button buttonSet3;
        private System.Windows.Forms.Timer timer1;
    }
}

