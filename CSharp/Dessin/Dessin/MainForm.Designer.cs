﻿namespace Dessin
{
    partial class MainForm
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.but_effacer = new System.Windows.Forms.Button();
            this.but_formecomplexe = new System.Windows.Forms.Button();
            this.but_creercomplexe = new System.Windows.Forms.Button();
            this.but_image = new System.Windows.Forms.Button();
            this.but_rectangle = new System.Windows.Forms.Button();
            this.but_circle = new System.Windows.Forms.Button();
            this.but_square = new System.Windows.Forms.Button();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.pictureBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.but_effacer);
            this.splitContainer1.Panel2.Controls.Add(this.but_formecomplexe);
            this.splitContainer1.Panel2.Controls.Add(this.but_creercomplexe);
            this.splitContainer1.Panel2.Controls.Add(this.but_image);
            this.splitContainer1.Panel2.Controls.Add(this.but_rectangle);
            this.splitContainer1.Panel2.Controls.Add(this.but_circle);
            this.splitContainer1.Panel2.Controls.Add(this.but_square);
            this.splitContainer1.Size = new System.Drawing.Size(700, 350);
            this.splitContainer1.SplitterDistance = 580;
            this.splitContainer1.TabIndex = 0;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.BackColor = System.Drawing.Color.Gainsboro;
            this.pictureBox1.Location = new System.Drawing.Point(13, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(575, 326);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            // 
            // but_effacer
            // 
            this.but_effacer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_effacer.Location = new System.Drawing.Point(11, 262);
            this.but_effacer.Name = "but_effacer";
            this.but_effacer.Size = new System.Drawing.Size(93, 23);
            this.but_effacer.TabIndex = 6;
            this.but_effacer.Text = "Effacer";
            this.but_effacer.UseVisualStyleBackColor = true;
            this.but_effacer.Click += new System.EventHandler(this.bEffacer_click);
            // 
            // but_formecomplexe
            // 
            this.but_formecomplexe.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_formecomplexe.Enabled = false;
            this.but_formecomplexe.Location = new System.Drawing.Point(9, 132);
            this.but_formecomplexe.Name = "but_formecomplexe";
            this.but_formecomplexe.Size = new System.Drawing.Size(95, 23);
            this.but_formecomplexe.TabIndex = 5;
            this.but_formecomplexe.Text = "Forme complexe";
            this.but_formecomplexe.UseVisualStyleBackColor = true;
            // 
            // but_creercomplexe
            // 
            this.but_creercomplexe.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_creercomplexe.Location = new System.Drawing.Point(9, 291);
            this.but_creercomplexe.Name = "but_creercomplexe";
            this.but_creercomplexe.Size = new System.Drawing.Size(95, 47);
            this.but_creercomplexe.TabIndex = 4;
            this.but_creercomplexe.Text = "Créer une forme complexe";
            this.but_creercomplexe.UseVisualStyleBackColor = true;
            this.but_creercomplexe.Click += new System.EventHandler(this.bCreerFormeComplexe_click);
            // 
            // but_image
            // 
            this.but_image.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_image.Location = new System.Drawing.Point(9, 102);
            this.but_image.Name = "but_image";
            this.but_image.Size = new System.Drawing.Size(95, 23);
            this.but_image.TabIndex = 3;
            this.but_image.Text = "Image";
            this.but_image.UseVisualStyleBackColor = true;
            this.but_image.Click += new System.EventHandler(this.bImage_Click);
            // 
            // but_rectangle
            // 
            this.but_rectangle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_rectangle.Location = new System.Drawing.Point(9, 72);
            this.but_rectangle.Name = "but_rectangle";
            this.but_rectangle.Size = new System.Drawing.Size(95, 23);
            this.but_rectangle.TabIndex = 2;
            this.but_rectangle.Text = "Rectangle";
            this.but_rectangle.UseVisualStyleBackColor = true;
            this.but_rectangle.Click += new System.EventHandler(this.bRectangle_Click);
            // 
            // but_circle
            // 
            this.but_circle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_circle.Location = new System.Drawing.Point(9, 42);
            this.but_circle.Name = "but_circle";
            this.but_circle.Size = new System.Drawing.Size(95, 23);
            this.but_circle.TabIndex = 1;
            this.but_circle.Text = "Cercle";
            this.but_circle.UseVisualStyleBackColor = true;
            this.but_circle.Click += new System.EventHandler(this.bCircle_Click);
            // 
            // but_square
            // 
            this.but_square.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.but_square.Location = new System.Drawing.Point(9, 12);
            this.but_square.Name = "but_square";
            this.but_square.Size = new System.Drawing.Size(95, 23);
            this.but_square.TabIndex = 0;
            this.but_square.Text = "Carré";
            this.but_square.UseVisualStyleBackColor = true;
            this.but_square.Click += new System.EventHandler(this.bSquare_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(700, 350);
            this.Controls.Add(this.splitContainer1);
            this.Name = "MainForm";
            this.Text = "Dessin";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button but_square;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button but_circle;
        private System.Windows.Forms.Button but_rectangle;
        private System.Windows.Forms.Button but_image;
        private System.Windows.Forms.Button but_creercomplexe;
        private System.Windows.Forms.Button but_formecomplexe;
        private System.Windows.Forms.Button but_effacer;
    }
}