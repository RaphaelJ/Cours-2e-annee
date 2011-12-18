using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    class FormeComplexe : IDrawable
    {
        public List<Tuple<IDrawable, Point>> Formes { get; private set; }

        int minX, minY, maxX, maxY;

        public FormeComplexe(List<Tuple<IDrawable, Point>> formes)
        {
            this.Formes = formes;

            this.minX = this.Formes.Aggregate(
                int.MaxValue,
                (acc, f) => Math.Min(acc, f.Second.X)
            );
            this.minY = this.Formes.Aggregate(
                int.MaxValue,
                (acc, f) => Math.Min(acc, f.Second.Y)
            );
            this.maxX = this.Formes.Aggregate(
                int.MinValue,
                (acc, f) => Math.Max(acc, f.Second.X)
            );
            this.maxY = this.Formes.Aggregate(
                int.MinValue,
                (acc, f) => Math.Max(acc, f.Second.Y)
            );
        }

        public void Draw(Graphics g, Point center, Color color)
        {
            var width = maxX - minX;
            var height = maxY - minY;
            var topLeft = new Point(
                center.X - width / 2,
                center.Y - height / 2
            );

            foreach (var forme in this.Formes) {
                var formeCenter = new Point(
                    topLeft.X + forme.Second.X - minX,
                    topLeft.Y + forme.Second.Y - minY
                );
                forme.First.Draw(g, formeCenter, color);
            }
        }
    }
}
