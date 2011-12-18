using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    class Square : IDrawable
    {
        public int Size { get; set; }

        public Square(int size)
        {
            this.Size = size;
        }

        public void Draw(Graphics g, Point center, Color color)
        {
            Pen p = new Pen(color);
            g.DrawRectangle(
                 p, center.X - this.Size / 2,
                 center.Y - this.Size / 2,
                 this.Size, this.Size
            );
        }
    }
}
