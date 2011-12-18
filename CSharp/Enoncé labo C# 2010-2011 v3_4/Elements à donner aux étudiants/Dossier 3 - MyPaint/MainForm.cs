using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WFAPrepaEnonce3DossierCSharp
{
    public partial class MainForm : Form
    {
        IDrawable current = null;      

        List<IDrawable> _list = new List<IDrawable>();

        public MainForm()
        {
            InitializeComponent();
        }

        private void bSquare_Click(object sender, EventArgs e)
        {
            current = new Square(50,new Point(25,25));
            current.Color = Color.Red;
        }

        private void bCircle_Click(object sender, EventArgs e)
        {
            current = new Circle(50, new Point(25, 25));
            current.Color = Color.Red;
        
        }

        private void bRectangle_Click(object sender, EventArgs e)
        {
            // Add code to create a new rectangle to draw here
        }

        private void bImage_Click(object sender, EventArgs e)
        {

            // Add code to create a new image to draw here
        }

       
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            foreach (IDrawable item in _list)
            {
                item.Color = Color.Blue;
                item.Draw(e.Graphics);
            }

            if (current != null)
            {
                current.Color = Color.Red;
                current.Draw(e.Graphics);
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (current != null)
            {
                _list.Add(current);
                current = null;
                pictureBox1.Invalidate();

            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (current != null)
            {

                current.Center = e.Location;
                pictureBox1.Invalidate();
            }
        }
    }
}
