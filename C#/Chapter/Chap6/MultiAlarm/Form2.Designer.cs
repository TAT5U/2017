namespace MultiAlarm
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.labelAlmHour = new System.Windows.Forms.Label();
            this.labelAlmMnt = new System.Windows.Forms.Label();
            this.numericUpDownAlmHour = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownAlmMnt = new System.Windows.Forms.NumericUpDown();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlmHour)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlmMnt)).BeginInit();
            this.SuspendLayout();
            // 
            // labelAlmHour
            // 
            this.labelAlmHour.AutoSize = true;
            this.labelAlmHour.Location = new System.Drawing.Point(12, 32);
            this.labelAlmHour.Name = "labelAlmHour";
            this.labelAlmHour.Size = new System.Drawing.Size(13, 12);
            this.labelAlmHour.TabIndex = 0;
            this.labelAlmHour.Text = "  ";
            // 
            // labelAlmMnt
            // 
            this.labelAlmMnt.AutoSize = true;
            this.labelAlmMnt.Location = new System.Drawing.Point(12, 82);
            this.labelAlmMnt.Name = "labelAlmMnt";
            this.labelAlmMnt.Size = new System.Drawing.Size(13, 12);
            this.labelAlmMnt.TabIndex = 1;
            this.labelAlmMnt.Text = "  ";
            // 
            // numericUpDownAlmHour
            // 
            this.numericUpDownAlmHour.Location = new System.Drawing.Point(31, 30);
            this.numericUpDownAlmHour.Name = "numericUpDownAlmHour";
            this.numericUpDownAlmHour.Size = new System.Drawing.Size(120, 19);
            this.numericUpDownAlmHour.TabIndex = 2;
            // 
            // numericUpDownAlmMnt
            // 
            this.numericUpDownAlmMnt.Location = new System.Drawing.Point(31, 80);
            this.numericUpDownAlmMnt.Name = "numericUpDownAlmMnt";
            this.numericUpDownAlmMnt.Size = new System.Drawing.Size(120, 19);
            this.numericUpDownAlmMnt.TabIndex = 3;
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(53, 140);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 4;
            this.buttonOK.Text = "button1";
            this.buttonOK.UseVisualStyleBackColor = true;
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(53, 210);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 5;
            this.buttonCancel.Text = "button2";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(179, 261);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.numericUpDownAlmMnt);
            this.Controls.Add(this.numericUpDownAlmHour);
            this.Controls.Add(this.labelAlmMnt);
            this.Controls.Add(this.labelAlmHour);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlmHour)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlmMnt)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelAlmHour;
        private System.Windows.Forms.Label labelAlmMnt;
        private System.Windows.Forms.NumericUpDown numericUpDownAlmHour;
        private System.Windows.Forms.NumericUpDown numericUpDownAlmMnt;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
    }
}