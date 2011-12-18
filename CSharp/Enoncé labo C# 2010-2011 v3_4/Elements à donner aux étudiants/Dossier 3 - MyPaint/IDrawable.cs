using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace WFAPrepaEnonce3DossierCSharp
{
    public interface IDrawable
    {
        void Draw(Graphics g);
        Point Center { get; set; }
        Color Color { get; set; }
    }
}
