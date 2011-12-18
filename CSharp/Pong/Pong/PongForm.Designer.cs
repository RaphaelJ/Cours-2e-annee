namespace Pong
{
    partial class PongForm
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
            this.terrain = new System.Windows.Forms.PictureBox();
            this.comboJ1 = new System.Windows.Forms.ComboBox();
            this.comboJ2 = new System.Windows.Forms.ComboBox();
            this.buttonRaz = new System.Windows.Forms.Button();
            this.buttonAddPointRight = new System.Windows.Forms.Button();
            this.buttonAddPointLeft = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.terrain)).BeginInit();
            this.SuspendLayout();
            // 
            // terrain
            // 
            this.terrain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.terrain.BackColor = System.Drawing.SystemColors.ControlText;
            this.terrain.Location = new System.Drawing.Point(12, 12);
            this.terrain.Name = "terrain";
            this.terrain.Size = new System.Drawing.Size(860, 464);
            this.terrain.TabIndex = 0;
            this.terrain.TabStop = false;
            // 
            // comboJ1
            // 
            this.comboJ1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.comboJ1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboJ1.FormattingEnabled = true;
            this.comboJ1.Items.AddRange(new object[] {
            "Ordinateur",
            "Joueur clavier",
            "Joueur souris"});
            this.comboJ1.Location = new System.Drawing.Point(12, 482);
            this.comboJ1.Name = "comboJ1";
            this.comboJ1.Size = new System.Drawing.Size(200, 21);
            this.comboJ1.TabIndex = 1;
            // 
            // comboJ2
            // 
            this.comboJ2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.comboJ2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboJ2.FormattingEnabled = true;
            this.comboJ2.Items.AddRange(new object[] {
            "Ordinateur",
            "Joueur clavier",
            "Joueur souris"});
            this.comboJ2.Location = new System.Drawing.Point(672, 482);
            this.comboJ2.Name = "comboJ2";
            this.comboJ2.Size = new System.Drawing.Size(200, 21);
            this.comboJ2.TabIndex = 2;
            // 
            // buttonRaz
            // 
            this.buttonRaz.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonRaz.Location = new System.Drawing.Point(323, 480);
            this.buttonRaz.Name = "buttonRaz";
            this.buttonRaz.Size = new System.Drawing.Size(238, 23);
            this.buttonRaz.TabIndex = 3;
            this.buttonRaz.Text = "Remise à zéro";
            this.buttonRaz.UseVisualStyleBackColor = true;
            this.buttonRaz.Click += new System.EventHandler(this.buttonRaz_Click);
            // 
            // buttonAddPointRight
            // 
            this.buttonAddPointRight.Location = new System.Drawing.Point(567, 480);
            this.buttonAddPointRight.Name = "buttonAddPointRight";
            this.buttonAddPointRight.Size = new System.Drawing.Size(99, 23);
            this.buttonAddPointRight.TabIndex = 4;
            this.buttonAddPointRight.Text = "Ajouter un point";
            this.buttonAddPointRight.UseVisualStyleBackColor = true;
            // 
            // buttonAddPointLeft
            // 
            this.buttonAddPointLeft.Location = new System.Drawing.Point(218, 480);
            this.buttonAddPointLeft.Name = "buttonAddPointLeft";
            this.buttonAddPointLeft.Size = new System.Drawing.Size(99, 23);
            this.buttonAddPointLeft.TabIndex = 5;
            this.buttonAddPointLeft.Text = "Ajouter un point";
            this.buttonAddPointLeft.UseVisualStyleBackColor = true;
            // 
            // PongForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(884, 509);
            this.Controls.Add(this.buttonAddPointLeft);
            this.Controls.Add(this.buttonAddPointRight);
            this.Controls.Add(this.buttonRaz);
            this.Controls.Add(this.comboJ2);
            this.Controls.Add(this.comboJ1);
            this.Controls.Add(this.terrain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "PongForm";
            this.Text = "Pong";
            ((System.ComponentModel.ISupportInitialize)(this.terrain)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox terrain;
        private System.Windows.Forms.ComboBox comboJ1;
        private System.Windows.Forms.ComboBox comboJ2;
        private System.Windows.Forms.Button buttonRaz;
        private System.Windows.Forms.Button buttonAddPointRight;
        private System.Windows.Forms.Button buttonAddPointLeft;
    }
}

