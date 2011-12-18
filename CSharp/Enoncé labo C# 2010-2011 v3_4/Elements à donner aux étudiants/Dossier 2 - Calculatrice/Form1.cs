using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LaboCalculatrice2emeInPrES20102011
{
    public partial class Form1 : Form
    {
        Calculatrice myCalculatrice = null;

        public Form1()
        {
            InitializeComponent();

            lError.Text = "";

            myCalculatrice = new Calculatrice();

            CalculatriceDelegatesCheckUp();
        }

        private void CalculatriceDelegatesCheckUp()
        {
            try
            {
                if (myCalculatrice["+"](3.0, 2.0) != 5.0)
                {
                    MessageBox.Show("Test error : +");
                }

                if (myCalculatrice["-"](3.0, 2.0) != 1.0)
                {
                    MessageBox.Show("Test error : -");
                }

                if (myCalculatrice["*"](3.0, 2.0) != 6.0)
                {
                    MessageBox.Show("Test error : +");
                }

                if (myCalculatrice["/"](3.0, 2.0) != 1.5)
                {
                    MessageBox.Show("Test error : +");
                }
            }
            catch (Exception exc)
            {

                MessageBox.Show(exc.Message);
            }
        }

        private void bOperArithm_Click(object sender, EventArgs e)
        {
            Button bOper = sender as Button;

            tbOperArithm.Text = bOper.Tag.ToString();

            if (checkBox1.Checked == true)
            {
                ProcessOperation();
                
            }
        }

        private void bEgale_Click(object sender, EventArgs e)
        {
            ProcessOperation();
        }

        private void ProcessOperation()
        {
            lError.Text = "";

            try
            {
                Calculatrice.OperArithmetique theDelegué = myCalculatrice[tbOperArithm.Text];

                tbResultat.Text = theDelegué(Double.Parse(tbOperande1.Text), Double.Parse(tbOperande2.Text)).ToString();
            }
            catch (Exception exc)
            {
                lError.Text = exc.Message;
            }
        }
    }
}
