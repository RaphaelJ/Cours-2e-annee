using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace Pong
{
    public static class Intelligences
    {
        public delegate void Intelligence(RectangleF area, float timeRatio,
            Ball ball, Racquet racquet, Keys keysEvent, Point? mouseLocation);

        public static void MousePlayer(RectangleF area, float timeRatio,
            Ball ball, Racquet racquet, Keys keysEvent, Point? mouseLocation)
        {
            if (mouseLocation.HasValue)
                racquet.SetY(mouseLocation.Value.Y, area);
        }

        public static void KeyboardPlayer(RectangleF area, float timeRatio,
            Ball ball, Racquet racquet, Keys keysEvent, Point? mouseLocation)
        {
            const int moveSpeed = 50;

            if (keysEvent == Keys.Z)
                racquet.SetY(racquet.Y - (int) (moveSpeed * timeRatio), area);
            else if (keysEvent == Keys.S)
                racquet.SetY(racquet.Y + (int)(moveSpeed * timeRatio), area);
        }

        public static void Computer(RectangleF area, float timeRatio,
            Ball ball, Racquet racquet, Keys keysEvent, Point? mouseLocation)
        {
            const int moveSpeed = 10;

            if (ball.CenterY < racquet.Y) {
                racquet.SetY(
                    racquet.Y - (int) Math.Min(
                        racquet.Y - ball.CenterY,
                        moveSpeed * timeRatio
                    ), area
                );
            } else if (ball.CenterY > racquet.Y) {
                racquet.SetY(
                    racquet.Y + (int)Math.Min(
                        ball.CenterY - racquet.Y,
                        moveSpeed * timeRatio
                    ), area
                );
            }
        }
    }
}
