﻿namespace Calculatrice
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.tbOperande1 = new System.Windows.Forms.TextBox();
            this.tbOperArithm = new System.Windows.Forms.TextBox();
            this.tbOperande2 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.tbResultat = new System.Windows.Forms.TextBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.lError = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tbOperande1
            // 
            this.tbOperande1.Location = new System.Drawing.Point(12, 45);
            this.tbOperande1.Name = "tbOperande1";
            this.tbOperande1.Size = new System.Drawing.Size(100, 20);
            this.tbOperande1.TabIndex = 0;
            // 
            // tbOperArithm
            // 
            this.tbOperArithm.Location = new System.Drawing.Point(190, 45);
            this.tbOperArithm.Name = "tbOperArithm";
            this.tbOperArithm.Size = new System.Drawing.Size(31, 20);
            this.tbOperArithm.TabIndex = 1;
            // 
            // tbOperande2
            // 
            this.tbOperande2.Location = new System.Drawing.Point(308, 45);
            this.tbOperande2.Name = "tbOperande2";
            this.tbOperande2.Size = new System.Drawing.Size(100, 20);
            this.tbOperande2.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(190, 8);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(31, 27);
            this.button1.TabIndex = 3;
            this.button1.Tag = "+";
            this.button1.Text = "+";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.bOperArithm_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(227, 45);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(36, 19);
            this.button2.TabIndex = 4;
            this.button2.Tag = "-";
            this.button2.Text = "-";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.bOperArithm_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(190, 71);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(31, 27);
            this.button3.TabIndex = 5;
            this.button3.Tag = "*";
            this.button3.Text = "*";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.bOperArithm_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(147, 45);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(37, 20);
            this.button4.TabIndex = 6;
            this.button4.Tag = "/";
            this.button4.Text = "/";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.bOperArithm_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(168, 104);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 23);
            this.button5.TabIndex = 7;
            this.button5.Tag = "=";
            this.button5.Text = "=";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.bEgale_Click);
            // 
            // tbResultat
            // 
            this.tbResultat.Location = new System.Drawing.Point(147, 140);
            this.tbResultat.Name = "tbResultat";
            this.tbResultat.Size = new System.Drawing.Size(116, 20);
            this.tbResultat.TabIndex = 8;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(12, 142);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(122, 17);
            this.checkBox1.TabIndex = 9;
            this.checkBox1.Text = "Calculer directement";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // lError
            // 
            this.lError.AutoSize = true;
            this.lError.Location = new System.Drawing.Point(224, 71);
            this.lError.Name = "lError";
            this.lError.Size = new System.Drawing.Size(63, 13);
            this.lError.TabIndex = 10;
            this.lError.Text = "Pas d\'erreur";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(420, 184);
            this.Controls.Add(this.lError);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.tbResultat);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tbOperande2);
            this.Controls.Add(this.tbOperArithm);
            this.Controls.Add(this.tbOperande1);
            this.Name = "Form1";
            this.Text = "Kalkulatrisse";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbOperande1;
        private System.Windows.Forms.TextBox tbOperArithm;
        private System.Windows.Forms.TextBox tbOperande2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.TextBox tbResultat;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Label lError;

    }
}

