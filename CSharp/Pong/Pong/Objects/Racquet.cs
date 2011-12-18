using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;

namespace Pong
{
    public class Racquet : GameObject
    {
        public const int Margin = 15;
        public const int Width = 10;
        public const int Heigth = 70;

        /// <summary>
        /// Ordonnée du centre de la raquette
        /// </summary>
        public int Y { get; protected set; }

        public enum RacquetSides {
            Left, Right
        };

        public RacquetSides Side { get; protected set; }

        public Intelligences.Intelligence Intelligence { get; set; }

        // Retourne le multiplicateur de vitesse en fonction
        // de l'endroit ou la balle touche (entre -1 et 1).
        public readonly Func<float, float> SpeedMult =
            (x) => 1f / (float) Math.Sqrt(1 - x*x);

        // Retourne le nouveau Dx après que la balle aie touché
        // la raquette à l'absisse x (entre -1 et 1).
        public readonly Func<float, float> DxReflection =
            (x) => (float) Math.Sqrt(1 - x * x);

        // Retourne le nouveau Dy après que la balle aie touché
        // la raquette à l'absisse x (entre -1 et 1).
        public readonly Func<float, float> DyReflection =
            (x) => x;

        /// <summary>
        /// Distance entre le bord de l'image et le bord
        /// interieur de la raquette.
        /// </summary>
        public static readonly int GoalDist = PlayGround.Margin + Margin + Width;

        public Racquet(RacquetSides side)
        {
            this.Side = side;

            this.Y = 250;

            this.Intelligence = Intelligences.Computer;
        }

        // Retourne true si la raquette sait servir des
        // balles à cette ordonnée.
        public bool OnTheRacquet(int y)
        {
            var top = this.Y - Heigth / 2;
            var bottom = this.Y + Heigth / 2;

            return y > top && y < bottom;
        }

        public void SetY(int value, RectangleF area)
        {
            var minY = PlayGround.Margin + Heigth / 2;
            var maxY = (int) area.Height - minY;

            if (value < minY)
                this.Y = minY;
            else if (value > maxY)
                this.Y = maxY;
            else
                this.Y = value;
        }

        // Retourne le nouveau mouvement effectué par la
        // balle en fonction de l'endroit où elle touche
        // la raquette.
        public Ball.Movement NewMove(Ball.Movement oldMove, int y)
        {
            float xBar = (float) (y - this.Y) / (Heigth / 2);

            float direction;
            if (this.Side == RacquetSides.Left)
                direction = +1;
            else
                direction = -1;

            // Vitesse avant réflexion (distance de Manathan)
            var oldSpeed = Math.Sqrt(
                oldMove.X * oldMove.X
                + oldMove.Y * oldMove.Y
            );
            // Vitesse uni-dimentionnelle amortie (si dx = dy);
            var oldSpeedMult = Math.Sqrt((oldSpeed * oldSpeed) / 2);

            // Direction après réflexion
            var reflX = DxReflection(xBar);
            var reflY = DyReflection(xBar);
            // Vitesse de la réflexion 
            var reflSpeed = Math.Sqrt(
                reflX * reflX + reflY * reflY
            );
            // Vitesse uni-dimentionnelle de la réflexion
            var reflSpeedMult = Math.Sqrt((reflSpeed * reflSpeed) / 2);

            // Rapport de vitesse entre la réflexion et l'ancienne vitesse
            // auquel le multiplicateur de vitesse est appliqué
            var speedMult = oldSpeedMult / reflSpeedMult * SpeedMult(xBar);

            return new Ball.Movement(
                (float) (reflX * speedMult * direction),
                (float) (reflY * speedMult)
            );
        }

        public void Update(float timeRatio, Pong pong, RectangleF area, Keys keysEvent,
		                   Point? mouseLocation)
        {
            this.Intelligence(area, timeRatio, pong.Ball, this, keysEvent, mouseLocation);
        }

        public override void Draw(Graphics area)
        {
            int x;
            if (this.Side == RacquetSides.Left)
                x = PlayGround.Margin + Margin;
            else
                x = (int) area.ClipBounds.Width - (PlayGround.Margin + Margin + Width);

            area.FillRectangle(Brushes.White, x, this.Y - Heigth / 2, Width, Heigth);
        }
    }
}
