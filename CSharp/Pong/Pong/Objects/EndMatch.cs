using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Pong
{
    public class EndMatch : GameObject
    {
        public const int FontSize = 30;

        public Scores.Competitors Winner { get; set; }

        public EndMatch(Scores.Competitors winner)
        {
            this.Winner = winner;
        }

        public override void Draw(Graphics area)
        {
            var xMiddle = area.ClipBounds.Width / 2;
            var yMiddle = area.ClipBounds.Height / 2;

            string str;
            if (this.Winner == Scores.Competitors.Left)
                str = "Le joueur de gauche remporte le match";
            else
                str = "Le joueur de droite remporte le match";

            var font = new Font(
                new FontFamily("Calibri"), FontSize,
                FontStyle.Bold
            );

            area.DrawString(str, font, Brushes.White,
                xMiddle - (str.Length * FontSize) / 3.5f,
                yMiddle - FontSize / 2
            );
        }
    }
}
