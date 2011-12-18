namespace Calculatrice
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
            this.Entree = new System.Windows.Forms.TextBox();
            this.BoutonAC = new System.Windows.Forms.Button();
            this.Resultat = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Entree
            // 
            this.Entree.Location = new System.Drawing.Point(12, 12);
            this.Entree.Name = "Entree";
            this.Entree.Size = new System.Drawing.Size(472, 20);
            this.Entree.TabIndex = 0;
            this.Entree.TextChanged += this.EntreeModifiee;
            // 
            // BoutonAC
            // 
            this.BoutonAC.Location = new System.Drawing.Point(13, 39);
            this.BoutonAC.Name = "BoutonAC";
            this.BoutonAC.Size = new System.Drawing.Size(75, 23);
            this.BoutonAC.TabIndex = 1;
            this.BoutonAC.Text = "AC";
            this.BoutonAC.UseVisualStyleBackColor = true;
            // 
            // Resultat
            // 
            this.Resultat.AutoSize = true;
            this.Resultat.Location = new System.Drawing.Point(94, 44);
            this.Resultat.Name = "Resultat";
            this.Resultat.Size = new System.Drawing.Size(41, 13);
            this.Resultat.TabIndex = 3;
            this.Resultat.Text = "resultat";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(496, 72);
            this.Controls.Add(this.Resultat);
            this.Controls.Add(this.BoutonAC);
            this.Controls.Add(this.Entree);
            this.Name = "Form1";
            this.Text = "Kalkulatrisse";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Entree;
        private System.Windows.Forms.Button BoutonAC;
        private System.Windows.Forms.Label Resultat;
    }
}

