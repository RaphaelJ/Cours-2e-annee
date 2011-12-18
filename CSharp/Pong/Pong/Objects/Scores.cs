using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Windows.Forms;

namespace Pong
{
    public class Scores : GameObject
    {
        public const int WinSets = 2;

        public enum Competitors {
            Unknown,
            Left,
            Right
        };

        public enum Points {
            Zero = 0,
            Fifteen = 15,
            Thirty = 30,
            Forty = 40,
            AD = -1
        };

        public static string PointsToString(Points points)
        {
            switch (points) {
            case Points.Zero:
                return " 0";
            case Points.Fifteen:
                return "15";
            case Points.Thirty:
                return "30";
            case Points.Forty:
                return "40";
            case Points.AD:
                return "AD";
            default:
                return "?";
            }
        }

        public class WinEventArgs : EventArgs {
            public Competitors Winner;

            public WinEventArgs(Competitors winner)
            {
                this.Winner = winner;
            }
        }

        public event EventHandler<WinEventArgs> PointEnded;
        public event EventHandler<WinEventArgs> GameEnded;
        public event EventHandler<WinEventArgs> SetEnded;
        public event EventHandler<WinEventArgs> MatchEnded;

        public class Set {
            public int GamesLeft = 0;
            public int GamesRight = 0;

            public void AddLeft()
            {
                this.GamesLeft += 1;
            }

            public void AddRight()
            {
                this.GamesRight += 1;
            }

            /// <summary>
            /// Donne le gagnant du jeu. Unknown si le set n'est
            /// pas terminé.
            /// </summary>
            public Competitors Winner
            {
                get {
                    if (Math.Max(this.GamesLeft, this.GamesRight) < 6
                        || Math.Abs(this.GamesLeft - this.GamesRight) < 2)
                        return Competitors.Unknown;
                    else if (this.GamesLeft > this.GamesRight)
                        return Competitors.Left;
                    else
                        return Competitors.Right;
                }
            }
        }

        public const int SetsSize = 18;
        public const int GamesSize = 32;
        public const int Margin = 15;

        public LinkedList<Set> Sets = new LinkedList<Set>();
        public Points PointsLeft = Points.Zero;
        public Points PointsRight = Points.Zero;

        public Scores()
        {
            this.Sets.AddFirst(new Set());
        }

        /// <summary>
        /// Ajoutre un point au joueur gauche
        /// </summary>
        public void AddLeft()
        {
            if (this.PointEnded != null)
                this.PointEnded(this, new WinEventArgs(Competitors.Left));

            switch (this.PointsLeft) {
            case Points.Zero:
                    this.PointsLeft = Points.Fifteen;
                break;
            case Points.Fifteen:
                this.PointsLeft = Points.Thirty;
                break;
            case Points.Thirty:
                this.PointsLeft = Points.Forty;
                break;
            case Points.Forty:
                if (this.PointsRight == Points.AD) {
                    this.PointsLeft = Points.Forty;
                    this.PointsRight = Points.Forty;
                } else if (this.PointsRight == Points.Forty) {
                    this.PointsLeft = Points.AD;
                    this.PointsRight = Points.Forty;
                } else
                    this.AddGameLeft();
                break;
            case Points.AD:
                this.AddGameLeft();
                break;
            };
        }

        /// <summary>
        /// Ajoute un point au joueur de droite
        /// </summary>
        public void AddRight()
        {
            if (this.PointEnded != null)
                this.PointEnded(this, new WinEventArgs(Competitors.Right));

            switch (this.PointsRight) {
            case Points.Zero:
                this.PointsRight = Points.Fifteen;
                break;
            case Points.Fifteen:
                this.PointsRight = Points.Thirty;
                break;
            case Points.Thirty:
                this.PointsRight = Points.Forty;
                break;
            case Points.Forty:
                if (this.PointsLeft == Points.AD) {
                    this.PointsRight = Points.Forty;
                    this.PointsLeft = Points.Forty;
                } else if (this.PointsLeft == Points.Forty) {
                    this.PointsRight = Points.AD;
                    this.PointsLeft = Points.Forty;
                } else
                    this.AddGameRight();
                break;
            case Points.AD:
                this.AddGameRight();
                break;
            };
        }

        public void AddGameLeft()
        {
            if (this.GameEnded != null)
                this.GameEnded(this, new WinEventArgs(Competitors.Left));

            var set = this.Sets.First.Value;

            set.AddLeft();
            if (set.Winner != Competitors.Unknown)
                this.AddSet(Competitors.Left);

            this.PointsLeft = Points.Zero;
            this.PointsRight = Points.Zero;
        }

        public void AddGameRight()
        {
            if (this.GameEnded != null)
                this.GameEnded(this, new WinEventArgs(Competitors.Right));

            var set = this.Sets.First.Value;

            set.AddRight();
            if (set.Winner != Competitors.Unknown)
                this.AddSet(Competitors.Right);

            this.PointsLeft = Points.Zero;
            this.PointsRight = Points.Zero;
        }

        public void AddSet(Competitors winner)
        {
            if (this.SetEnded!= null)
                this.SetEnded(this, new WinEventArgs(winner));

            if (this.Winner != Competitors.Unknown) {
                // Fin du match
                if (this.MatchEnded != null)
                    this.MatchEnded(this, new WinEventArgs(winner));
            } else {
                // Nouveau set
                this.Sets.AddFirst(new Set());
            }
        }


        /// <summary>
        /// Donne le gagnant de la partie. Unknown si la partie
        /// n'est pas terminée.
        /// </summary>
        public Competitors Winner {
            get {
                int setsLeft = 0;
                int setsRight = 0;

                foreach (var set in this.Sets) {
                    if (set.Winner == Competitors.Left)
                        setsLeft += 1;
                    else if (set.Winner == Competitors.Right)
                        setsRight += 1;
                }

                if (setsLeft >= WinSets)
                    return Competitors.Left;
                else if (setsRight >= WinSets)
                    return Competitors.Right;
                else
                    return Competitors.Unknown;
            }
        }

        public override void Draw(Graphics area)
        {
            var fontSets = new Font(
                new FontFamily("Calibri"), SetsSize,
                FontStyle.Bold
            );
            var fontGames = new Font(
                new FontFamily("Calibri"), GamesSize,
                FontStyle.Bold
            );

            var y = PlayGround.Margin + Margin;
            var middle = area.ClipBounds.Width / 2;
            var xLeft = middle - (Margin + GamesSize * 2);
            var xRight = middle + Margin;

            // Affiche les jeux
            area.DrawString(PointsToString(this.PointsLeft), fontGames, Brushes.White, xLeft, y);
            area.DrawString(PointsToString(this.PointsRight), fontGames, Brushes.White, xRight, y);
            xLeft -= SetsSize;
            xRight += 2 * GamesSize;

            // Affiche les sets
            foreach (var set in this.Sets) {
                area.DrawString(set.GamesLeft.ToString(), fontSets, Brushes.White, xLeft, y);
                area.DrawString(set.GamesRight.ToString(), fontSets, Brushes.White, xRight, y);

                xLeft -= SetsSize;
                xRight += SetsSize;
            }
        }
    }
}
