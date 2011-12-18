using System;
using System.Collections.Generic;

namespace LaboCSharp
{
	class MyPieceComparer
		: IComparer<Piece>
	{
		public int Compare(Piece p1, Piece p2)
		{
			return Piece.ComparisonTriDecroissant(p1, p2);
		}
	}
}

