using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    class Rectangle : IDrawable
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public Rectangle(int width, int height)
        {
            this.Width = width;
            this.Height = height;
        }

        public void Draw(Graphics g, Point center, Color color)
        {
            Pen p = new Pen(color);
            g.DrawRectangle(
                 p, center.X - this.Width / 2,
                 center.Y - this.Height / 2,
                 this.Width, this.Height
            );
        }
    }
}
