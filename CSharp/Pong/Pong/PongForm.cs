using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace Pong
{
    public partial class PongForm : Form
    {	
        public Pong Pong { get; set; }

	    public bool Pause { 
            get {
                return this._Pause;
            } set {
                if (value)
                    this.Text = "Pong (en pause. 'P' pour reprendre)";
                else
                    this.Text = "Pong";

                this._Pause = value;
            }
        }
        private bool _Pause = false;

        public PongForm()
        {
            InitializeComponent();
            this.KeyPreview = true; // Permet de capturer les événements clavier

            // Lance le jeu
            this.Pong = new Pong(this.GameLoop);
			
            // Initialise les boutons de gestion des pointes
            this.buttonAddPointLeft.Click += (sender, args) => {
                this.Pong.Scores.AddLeft();
            };
            this.buttonAddPointRight.Click += (sender, args) => {
                this.Pong.Scores.AddRight();
            };
            
            // Initialise les boutons de gestion des intelligences
            var intelligences = new Intelligences.Intelligence[] {
                Intelligences.Computer,
                Intelligences.KeyboardPlayer,
                Intelligences.MousePlayer
            };

            this.comboJ1.SelectedIndex = 0;
            this.comboJ1.SelectedIndexChanged += (sender, args) => {
                this.Pong.LeftRacquet.Intelligence
                    = intelligences[this.comboJ1.SelectedIndex];
            };
            this.comboJ2.SelectedIndex = 0;
            this.comboJ2.SelectedIndexChanged += (sender, args) => {
                this.Pong.RightRacquet.Intelligence
                    = intelligences[this.comboJ2.SelectedIndex];
            };

            // Mets le jeu en pause au départ
            this.Pause = true;
        }
		
		/// <summary>
        /// Boucle indéfiniment l'exécution de fct avec un maximum de maxFps appels
        /// par seconde.
        /// Le 1er paramètre de fct est le ratio du delta de du temps d'exécution
        /// du précédent appel. Le second est la zone de dessin. Le 3e paramètre contient
        /// les clés pressées durant la dernière itération. Le 4e paramètre contient la
        /// dernière position connue du pointeur de la souris.
        /// </summary>
        public void GameLoop(int maxFps, Action<float, Graphics, Keys, Point?> fct)
        {
			// 1000 millisec / maxFPS
			var minTimePerCall = new TimeSpan(0, 0, 0, 0, 1000 / maxFps);
					
			// Capture les événements clavier
			var keysPressed = Keys.None;
			this.KeyDown += (sender, e) => {
                if (e.KeyCode == Keys.P)
                    this.Pause = !this.Pause;
                else
				    keysPressed = e.KeyCode;
			};
			
			// Capture les évémements souris
			Point? mouseLocation = null;
			this.terrain.MouseMove += (sender, e) => {
				mouseLocation = e.Location;
			};

            var start = DateTime.Now;

            Graphics area = this.terrain.CreateGraphics();

            new Thread(() => {
                // Boucle de jeu
                try {
                    while (Thread.CurrentThread.IsAlive) {
                        var new_start = DateTime.Now;
                        var eslaped = new_start - start;
                        start = new_start;

                        if (!this.Pause) {
                            lock (this.terrain) {
                                area.Clip = new Region(new Rectangle(0, 0, this.terrain.Width, this.terrain.Height));
    
                                area.Clear(Color.Black);
    
                                fct(
                                    (float)eslaped.Ticks / minTimePerCall.Ticks,
                                    area, keysPressed, mouseLocation
                                );
                            }
                        }

                        keysPressed = Keys.None;
                        eslaped = DateTime.Now - start;

                        if (minTimePerCall > eslaped)
                            Thread.Sleep(minTimePerCall - eslaped);   
                    }
                } catch (Exception e) {
                    Thread.CurrentThread.Abort();
                }
            }).Start();
        }

        private void buttonRaz_Click(object sender, EventArgs e)
        {
            lock (this.terrain) {
                var aiLeft = this.Pong.LeftRacquet.Intelligence;
                var aiRight = this.Pong.RightRacquet.Intelligence;

                this.Pong.Init();

                this.Pong.LeftRacquet.Intelligence = aiLeft;
                this.Pong.RightRacquet.Intelligence = aiRight;
            }
        }
    }
}
