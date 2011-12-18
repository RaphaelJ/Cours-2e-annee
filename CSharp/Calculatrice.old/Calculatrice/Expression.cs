using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Calculatrice
{
    // addition := multiplication | addition + multiplication | addition - multiplication
    // multiplication := valeur | multiplication * valeur | multiplication / valeur
    // atome := constante | ( addition )

    interface IOperation
    {
        double Valeur { get; }
        void Analyser(string expression);
    }

    class Atome : IOperation
    {
        private double? Constante = null;
        private Addition Addition = null;

        public double Valeur {
            get {
                if (this.Constante.HasValue)
                    return this.Constante.Value;
                else if (this.Addition != null)
                    return this.Addition.Valeur;
                else
                    throw new Exception("Valeur non définie");
            }
        }

        public void Analyser(string expression)
        {
            if (expression.StartsWith("(")) {
                if (expression.EndsWith(")")) {
                    this.Addition = new Addition();
                    this.Addition.Analyser(expression.Substring(1, expression.Length - 2));
                    this.Constante = null;
                } else
                    throw new Exception("Pas de parenthèse de fin");
            } else {
                this.Constante = double.Parse(expression);
                this.Addition = null;
            }
        }
    }

    class Addition : IOperation
    {
        Addition Gauche = null;
        Atome Droite = null;

        public double Valeur
        {
            get
            {
                if (this.Droite == null)
                    throw new Exception("Addition non définie");
                else if (this.Gauche == null)
                    return this.Droite.Valeur;
                else
                    return this.Gauche.Valeur + this.Droite.Valeur;
            }
        }

        public void Analyser(string expression)
        {
            var pos = expression.LastIndexOf('+');
            if (pos == -1) {
                pos = expression.LastIndexOf('-');
            }

            if (pos == -1) { // Valeur
                this.Droite = new Atome();
                this.Droite.Analyser(expression);
                this.Gauche = null;
            } else { // Multiplication + Valeur
                this.Gauche = new Addition();
                this.Gauche.Analyser(expression.Substring(0, pos - 1));
                this.Droite = new Atome();
                this.Droite.Analyser(expression.Substring(pos + 1));
            }
        }
    }

    class Expression : IOperation
    {
        Addition Addition;

        public double Valeur {
            get {
                if (this.Addition != null)
                    return this.Addition.Valeur;
                else
                    throw new Exception("Expression non définie");
            }
        }

        public void Analyser(string expression)
        {
            this.Addition = new Addition();
            this.Addition.Analyser(expression.Replace(" ", ""));
        }
    }
}