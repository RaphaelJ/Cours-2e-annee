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
    public partial class MainForm : Form
    {
        Tuple<IDrawable, Point> current;

        List<Tuple<IDrawable, Point>> _list = new List<Tuple<IDrawable, Point>>();

        public MainForm()
        {
            InitializeComponent();
        }

        private void bSquare_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable)new Square(50), new Point(50, 50));
        }

        private void bCircle_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable) new Circle(50), new Point(50, 50));
        }

        private void bRectangle_Click(object sender, EventArgs e)
        {
            current = Tuple.Create((IDrawable) new Rectangle(50, 80), new Point(25, 40));
        }

        private void bImage_Click(object sender, EventArgs e)
        {
            var dial = new OpenFileDialog();
            dial.Filter = "Images|*.jpg;*.jpeg;*.png;*.gif";
            if (dial.ShowDialog() == DialogResult.OK) {
                current = Tuple.Create(
                    (IDrawable) new Image(new System.Drawing.Bitmap(dial.OpenFile())),
                    new Point(50, 50)
                );
            }

        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            foreach (var item in _list)
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
                _list.Add(current);
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
            this._list.Clear();
            this.pictureBox1.Invalidate();
        }

        private void bCreerFormeComplexe_click(object sender, EventArgs e)
        {
            var complexe = new DialogFormeComplexe();
            complexe.ShowDialog(this);

            var list_complexes = complexe.List;

            if (list_complexes.Count > 0) {
                this.but_formecomplexe.Enabled = true;
                this.but_formecomplexe.Click += (obj, args) => {
                    current = Tuple.Create(
                        (IDrawable) new FormeComplexe(list_complexes),
                        new Point(50, 50)
                    );
                };
            } else {
                this.but_formecomplexe.Enabled = false;
            }
        }
    }
}
