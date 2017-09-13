namespace AlarmTimer
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
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
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
            this.labelDate = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.buttonReset = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.buttonSet = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelTime
            // 
            this.labelTime.Location = new System.Drawing.Point(12, 30);
            this.labelTime.Name = "labelTime";
            this.labelTime.Size = new System.Drawing.Size(35, 12);
            this.labelTime.TabIndex = 0;
            this.labelTime.Text = "label1";
            // 
            // labelDate
            // 
            this.labelDate.Location = new System.Drawing.Point(12, 84);
            this.labelDate.Name = "labelDate";
            this.labelDate.Size = new System.Drawing.Size(35, 12);
            this.labelDate.TabIndex = 1;
            this.labelDate.Text = "label2";
            // 
            // labelStatus
            // 
            this.labelStatus.Location = new System.Drawing.Point(12, 136);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(35, 12);
            this.labelStatus.TabIndex = 2;
            this.labelStatus.Text = "label3";
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(159, 165);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(75, 23);
            this.buttonReset.TabIndex = 1;
            this.buttonReset.Text = "button2";
            this.buttonReset.UseVisualStyleBackColor = true;
            // 
            // buttonSet
            // 
            this.buttonSet.Location = new System.Drawing.Point(54, 165);
            this.buttonSet.Name = "buttonSet";
            this.buttonSet.Size = new System.Drawing.Size(75, 23);
            this.buttonSet.TabIndex = 0;
            this.buttonSet.Text = "button1";
            this.buttonSet.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 210);
            this.Controls.Add(this.buttonReset);
            this.Controls.Add(this.buttonSet);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.labelDate);
            this.Controls.Add(this.labelTime);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label labelTime;
        private System.Windows.Forms.Label labelDate;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button buttonSet;
    }
}

