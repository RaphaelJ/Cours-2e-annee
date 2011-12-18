using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Calculatrice
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void EntreeModifiee(object sender, EventArgs e)
        {
            try {
                var exp = new Expression();
                exp.Analyser(this.Entree.Text);
                var val = exp.Valeur;

                this.Resultat.Text = "Résultat: " + val;
            } catch  (Exception except) {
                this.Resultat.Text = "Erreur: " + except.Message;
            }
        }
    }
}
