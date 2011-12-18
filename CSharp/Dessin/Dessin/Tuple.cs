using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Dessin
{
    public class Tuple<T, U>
    {
        public T First { get; set; }
        public U Second { get; set; }

        public Tuple(T first, U second)
        {
            this.First = first;
            this.Second = second;
        }
    }

    public struct Tuple {
        public static Tuple<T, U> Create<T, U>(T first, U second)
        {
            return new Tuple<T, U>(first, second);
        }
    }
}
