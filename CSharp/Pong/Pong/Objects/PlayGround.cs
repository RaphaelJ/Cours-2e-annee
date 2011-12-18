using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace Pong
{
    public class PlayGround : GameObject
    {
        public const int LinesWeight = 3;
        public const int Margin = 15;

        public override void Draw(Graphics area)
        {
            var pen = new Pen(Color.Gray, LinesWeight);

            area.DrawRectangle(
                pen,
                new Rectangle(
                    Margin, Margin,
                    (int) area.ClipBounds.Width - 2*Margin,
                    (int) area.ClipBounds.Height - 2 * Margin
                )
            );

            area.DrawLine(
                pen,
                (int) area.ClipBounds.Width / 2, Margin*2,
                (int) area.ClipBounds.Width / 2, area.ClipBounds.Height - Margin*2
            );
        }
    }
}
