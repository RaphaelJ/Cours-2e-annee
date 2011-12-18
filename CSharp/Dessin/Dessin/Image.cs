using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    class Image : IDrawable
    {
        public System.Drawing.Image Bitmap { get; set; }

        public Image(System.Drawing.Image bitmap)
        {
            this.Bitmap = bitmap;
        }

        public void Draw(Graphics g, Point center, Color color)
        {
            g.DrawImageUnscaled(
                this.Bitmap,
                center.X - this.Bitmap.Width / 2,
                center.Y - this.Bitmap.Height / 2
            );
        }
    }
}
