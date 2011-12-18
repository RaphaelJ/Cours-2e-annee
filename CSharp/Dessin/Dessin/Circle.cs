using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    class Circle : IDrawable
    {
        public int Radius { get; set; }

        public Circle(int radius)
        {
            this.Radius = radius;
        }

        public void Draw(Graphics g, Point center, Color color)
        {
            Pen p = new Pen(color);
            g.DrawEllipse(
                p, center.X - this.Radius / 2,
                center.Y - this.Radius / 2,
                this.Radius, this.Radius
            );
        }
    }
}
