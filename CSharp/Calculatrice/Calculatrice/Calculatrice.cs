using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Calculatrice
{
    class Calculatrice
    {
        public delegate double OperArithmetique(double a, double b);

        public static readonly OperArithmetique Addition =
            (a, b) => a + b;
        public static readonly OperArithmetique Soustraction =
            (a, b) => a - b;
        public static readonly OperArithmetique Multiplication =
            (a, b) => a * b;
        public static readonly OperArithmetique Division =
            (a, b) =>
            {
                if (b != 0)
                    return a / b;
                else
                    throw new DivideByZeroException();
            };

        public readonly Dictionary<char, OperArithmetique> Operations
            = new Dictionary<char, OperArithmetique>
		{
			{ '+', Addition },
			{ '-', Soustraction },
			{ '*', Multiplication },
			{ '/', Division }
		};

        public OperArithmetique this[char index]
        {
            get {
                if (this.Operations.ContainsKey(index))
                    return this.Operations[index];
                else {
                    throw new KeyNotFoundException(
                        string.Format("L'opération '{0}' n'est pas reconnue", index)
                    );
                }
            }
        }

        public OperArithmetique this[string index]
        {
            get {
                return this[index[0]];
            }
        }
    }
}
