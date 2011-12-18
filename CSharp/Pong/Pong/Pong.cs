using System;
using System.Drawing;
using System.Windows.Forms;

namespace Pong
{
	/// <summary>
	/// Classe contenant l'etat du jeu et les différentes
	/// méthode de mises à jours des objets de jeu.
	/// </summary>
	public class Pong
	{
        public Ball Ball { get; set; }
        public PlayGround Ground { get; set; }
        public Racquet LeftRacquet { get; set; }
        public Racquet RightRacquet { get; set; }
        public Scores Scores { get; set; }
        public EndMatch Winner { get; set; }

		/// <summary>
		/// Initialise et lance le jeu dans le contexte de rendu donné
		/// en argument.
		/// Le contexte de rendu est la boucle qui gère l'affichage sur
		/// le client graphique.
		/// </summary>
		public Pong(Action<int, Action<float, Graphics, Keys, Point?>> context)
		{
			this.Init();
			context(30, this.Update);
		}
		
		/// <summary>
		/// Initialise l'état des différents objets du jeu.
		/// </summary>
		public void Init()
		{
            this.Ball = new Ball();
            this.Ground = new PlayGround();

            this.Winner = null;

            this.Scores = new Scores();
            this.Scores.MatchEnded += (sender, args) => {
                this.Winner = new EndMatch(args.Winner);
            };

            this.LeftRacquet = new Racquet(Racquet.RacquetSides.Left);
            this.RightRacquet = new Racquet(Racquet.RacquetSides.Right);
		}
		
		/// <summary>
		/// Met à jour l'état du jeu et dessine les différents objets.
		/// </summary>
		public void Update(float timeRatio, Graphics area, Keys keysEvent,
		                   Point? mouseLocation)
        {
            if (this.Winner == null) {
                // Mets à jour les positions
                this.LeftRacquet.Update(timeRatio, this, area.ClipBounds,
                    keysEvent, mouseLocation);
                this.RightRacquet.Update(timeRatio, this, area.ClipBounds,
                    keysEvent, mouseLocation);
                this.Ball.Update(timeRatio, this, area.ClipBounds);
            } else {
                // Affiche le gagnant
                this.Winner.Draw(area);
            }

            // Affiche
            this.Ground.Draw(area);
            this.Scores.Draw(area);

            this.LeftRacquet.Draw(area);
            this.RightRacquet.Draw(area);

            this.Ball.Draw(area);
		}
	}
}