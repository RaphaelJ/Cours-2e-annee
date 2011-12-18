using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Pong
{
    public abstract class GameObject
    {
        /// <summary>
        /// Dessine l'objet sur la zone de jeu
        /// </summary>
        public abstract void Draw(Graphics area);
    }
}
