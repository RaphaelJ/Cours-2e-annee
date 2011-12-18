using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Dessin
{
    public partial class DialogFormeComplexe : Form
    {
        Tuple<IDrawable, Point> current = null;

        public List<Tuple<IDrawable, Point>> List { get; set; }

        public DialogFormeComplexe()
        {
            InitializeComponent();
            this.List = new List<Tuple<IDrawable, Point>>();
        }

        private void bSquare_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable) new Square(50), new Point(50, 50));
        }

        private void bCircle_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable)new Circle(50), new Point(50, 50));
        }

        private void bRectangle_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable)new Rectangle(50, 80), new Point(25, 40));
        }

        private void bImage_Click(object sender, EventArgs e)
        {
            var dial = new OpenFileDialog();
            dial.Filter = "Images|*.jpg;*.jpeg;*.png;*.gif";
            if (dial.ShowDialog() == DialogResult.OK)
            {
                current = current = Tuple.Create(
                    (IDrawable) new Image(new System.Drawing.Bitmap(dial.OpenFile())),
                    new Point(50, 50)
                );
            }

        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            foreach (var item in List)
            {
                item.First.Draw(
                    e.Graphics, item.Second, Color.Blue
                );
            }

            if (current != null)
            {
                current.First.Draw(
                    e.Graphics, current.Second,
                    Color.Red
                );
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (current != null)
            {
                List.Add(current);
                current = null;
                pictureBox1.Invalidate();
            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (current != null)
            {
                current.Second = e.Location;
                pictureBox1.Invalidate();
            }
        }

        private void bEffacer_click(object sender, EventArgs e)
        {
            this.List.Clear();
            this.pictureBox1.Invalidate();
        }

        private void bValider_click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void bAnnuler_click(object sender, EventArgs e)
        {
            this.Dispose();
            this.List.Clear();
        }
    }
}
