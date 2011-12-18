using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;

namespace Pong
{
    public class Ball : GameObject
    {
        /// <summary>
        /// Structure contenant le déplacement de la balle par seconde
        /// </summary>
        public class Movement
        {
            public float X;
            public float Y;

            public Movement(float x, float y)
            {
                this.X = x;
                this.Y = y;
            }
        }

        public const int Size = 18;

        public float CenterX { get; protected set; }
        public float CenterY { get; protected set; }

        public Movement CurrentMove { get; protected set; }

        public Ball()
        {
            this.Init();
        }

        public void Init()
        {
            this.CenterX = 430;
            this.CenterY = 232;

            // Lance la balle dans une direction aléatoire
            // entre -10 et 10
            var rand = new Random();
            this.CurrentMove = new Movement(
                (int)(rand.NextDouble() * 20 - 10),
                (int)(rand.NextDouble() * 20 - 10)
            );

            if (this.CurrentMove.X == 0) {
                // Evite de lancer la balle verticalement
                this.CurrentMove.X = 1; 
            }
        }

        public void Update(float timeRatio, Pong pong, RectangleF area)
        {
            // Retourne une valeur infinie si le nombre est négatif
            // ou nul
            Func<float, float> PositiveOrInf = (value) => {
                if (value <= 0)
                    return float.PositiveInfinity;
                else
                    return value;
            };

            // Déplace la balle sans faire de vérifications
            Action<float> MoveStupid = (moveTime) => {
                this.CenterX = this.CenterX + this.CurrentMove.X * moveTime;
                this.CenterY = this.CenterY + this.CurrentMove.Y * moveTime;
            };

            // Rectangle de la balle
            var rayon = Size / 2;
            var top = this.CenterY - rayon;
            var left = this.CenterX - rayon;
            var bottom = this.CenterY + rayon;
            var right = this.CenterX + rayon;

            // Bordures du jeu
            var minX = Racquet.GoalDist;
            var maxX = area.Width - Racquet.GoalDist;
            var minY = PlayGround.Margin;
            var maxY = area.Height - PlayGround.Margin;

            // Temps nécéssaire pour toucher les bords
            // Rmks: x / 0 avec un float donne +inf
            var timeMinX = PositiveOrInf((minX - left) / this.CurrentMove.X);
            var timeMaxX = PositiveOrInf((maxX - right) / this.CurrentMove.X);
            var timeMinY = PositiveOrInf((minY - top) / this.CurrentMove.Y);
            var timeMaxY = PositiveOrInf((maxY - bottom) / this.CurrentMove.Y);

            // Sélectionne le bord touché en premier
            if (timeMinX < timeRatio && timeMinX < timeMinY && timeMinX < timeMaxY) {
                // Bord gauche
                MoveStupid(timeMinX);

                if (pong.LeftRacquet.OnTheRacquet((int) this.CenterY)) {
                    // Sur la raquette
                    this.CurrentMove = pong.LeftRacquet.NewMove(
                        this.CurrentMove, (int) this.CenterY
                    );

                    this.Update(timeRatio - timeMinX, pong, area);
                } else {
                    // Perd le point
                    pong.Scores.AddRight();
                    this.Init();
                }
            } else if (timeMaxX < timeRatio && timeMaxX < timeMinY && timeMaxX < timeMaxY) {
                // Bord droit
                MoveStupid(timeMaxX);

                if (pong.RightRacquet.OnTheRacquet((int)this.CenterY)) {
                    // Sur la raquette
                    this.CurrentMove = pong.RightRacquet.NewMove(
                        this.CurrentMove, (int) this.CenterY
                    );

                    this.Update(timeRatio - timeMaxX, pong, area);
                } else {
                    // Perd le point
                    pong.Scores.AddLeft();
                    this.Init();
                }
            } else if (timeMinY < timeRatio && timeMinY < timeMinX && timeMinY < timeMaxX) {
                // Bord supérieur
                MoveStupid(timeMinY);
                this.CurrentMove.Y *= -1;
                this.Update(timeRatio - timeMinY, pong, area);
            } else if (timeMaxY < timeRatio && timeMaxY < timeMinX && timeMaxY < timeMaxX) {
                // Bord inférieur
                MoveStupid(timeMaxY);
                this.CurrentMove.Y *= -1;
                this.Update(timeRatio - timeMaxY, pong, area);
            } else {
                // Ne touche rien
                MoveStupid(timeRatio);
            }
        }

        public override void Draw(Graphics area)
        {
            var left = this.CenterX - Size / 2;
            var top = this.CenterY - Size / 2;

            area.FillEllipse(Brushes.White, left, top, Size, Size);
        }
    }
}