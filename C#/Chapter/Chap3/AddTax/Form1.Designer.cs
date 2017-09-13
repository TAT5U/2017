namespace AddTax
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
            this.textBoxMoney = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.labelAddTax = new System.Windows.Forms.Label();
            this.buttonAddTax = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(211, 19);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "label2";
            // 
            // textBoxMoney
            // 
            this.textBoxMoney.Location = new System.Drawing.Point(12, 34);
            this.textBoxMoney.Name = "textBoxMoney";
            this.textBoxMoney.Size = new System.Drawing.Size(100, 19);
            this.textBoxMoney.TabIndex = 0;
            this.textBoxMoney.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(118, 37);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "label3";
            // 
            // labelAddTax
            // 
            this.labelAddTax.AutoSize = true;
            this.labelAddTax.Location = new System.Drawing.Point(211, 37);
            this.labelAddTax.Name = "labelAddTax";
            this.labelAddTax.Size = new System.Drawing.Size(35, 12);
            this.labelAddTax.TabIndex = 4;
            this.labelAddTax.Text = "label4";
            // 
            // buttonAddTax
            // 
            this.buttonAddTax.Location = new System.Drawing.Point(154, 82);
            this.buttonAddTax.Name = "buttonAddTax";
            this.buttonAddTax.Size = new System.Drawing.Size(75, 23);
            this.buttonAddTax.TabIndex = 1;
            this.buttonAddTax.Text = "button1";
            this.buttonAddTax.UseVisualStyleBackColor = true;
            this.buttonAddTax.Click += new System.EventHandler(this.buttonAddTax_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(423, 127);
            this.Controls.Add(this.buttonAddTax);
            this.Controls.Add(this.labelAddTax);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxMoney);
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
        private System.Windows.Forms.TextBox textBoxMoney;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label labelAddTax;
        private System.Windows.Forms.Button buttonAddTax;
    }
}

