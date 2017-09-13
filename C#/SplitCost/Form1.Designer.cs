namespace SplitCost
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonSplitCost = new System.Windows.Forms.Button();
            this.textBoxMoney = new System.Windows.Forms.TextBox();
            this.textBoxPer = new System.Windows.Forms.TextBox();
            this.labelPerTax = new System.Windows.Forms.Label();
            this.labelRemain = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(172, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "label2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(141, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "label3";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(299, 62);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "label4";
            // 
            // buttonSplitCost
            // 
            this.buttonSplitCost.Location = new System.Drawing.Point(102, 197);
            this.buttonSplitCost.Name = "buttonSplitCost";
            this.buttonSplitCost.Size = new System.Drawing.Size(75, 23);
            this.buttonSplitCost.TabIndex = 2;
            this.buttonSplitCost.Text = "button1";
            this.buttonSplitCost.UseVisualStyleBackColor = true;
            this.buttonSplitCost.Click += new System.EventHandler(this.buttonSplitCost_Click);
            // 
            // textBoxMoney
            // 
            this.textBoxMoney.Location = new System.Drawing.Point(35, 48);
            this.textBoxMoney.Name = "textBoxMoney";
            this.textBoxMoney.Size = new System.Drawing.Size(100, 19);
            this.textBoxMoney.TabIndex = 0;
            this.textBoxMoney.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxPer
            // 
            this.textBoxPer.Location = new System.Drawing.Point(193, 55);
            this.textBoxPer.Name = "textBoxPer";
            this.textBoxPer.Size = new System.Drawing.Size(100, 19);
            this.textBoxPer.TabIndex = 1;
            this.textBoxPer.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPerTax
            // 
            this.labelPerTax.AutoSize = true;
            this.labelPerTax.Location = new System.Drawing.Point(54, 120);
            this.labelPerTax.Name = "labelPerTax";
            this.labelPerTax.Size = new System.Drawing.Size(35, 12);
            this.labelPerTax.TabIndex = 6;
            this.labelPerTax.Text = "label5";
            // 
            // labelRemain
            // 
            this.labelRemain.AutoSize = true;
            this.labelRemain.Location = new System.Drawing.Point(218, 131);
            this.labelRemain.Name = "labelRemain";
            this.labelRemain.Size = new System.Drawing.Size(35, 12);
            this.labelRemain.TabIndex = 7;
            this.labelRemain.Text = "label6";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(582, 262);
            this.Controls.Add(this.labelRemain);
            this.Controls.Add(this.labelPerTax);
            this.Controls.Add(this.textBoxPer);
            this.Controls.Add(this.textBoxMoney);
            this.Controls.Add(this.buttonSplitCost);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonSplitCost;
        private System.Windows.Forms.TextBox textBoxMoney;
        private System.Windows.Forms.TextBox textBoxPer;
        private System.Windows.Forms.Label labelPerTax;
        private System.Windows.Forms.Label labelRemain;
    }
}

