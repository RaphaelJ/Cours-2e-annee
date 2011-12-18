using System;
using System.Collections.Generic;

namespace LaboCSharp
{
	public class Piece
		: IEquatable<Piece>, IComparable<Piece>
	{
		private static int compteurPiece = 0;
		
		public static readonly Comparison<Piece> ComparisonTriCroissant
			= (p1, p2) => p1.CompareTo(p2);
		
		public static readonly Comparison<Piece> ComparisonTriDecroissant
			= (p1, p2) => - p1.CompareTo(p2);
			
		public string Nom { get; protected set; }
		public int IdPiece { get; protected set; }
		
		public double Longueur { get; set; }
		public double Largeur { get; set; }
		public double Hauteur { get; set; }
		
		public double Surface {
			get {
				return this.Longueur * this.Largeur * this.Hauteur;
			}
		}
		
		public Piece()
			: this("Inconnu", 0, 0, 0)
		{
		}
		public Piece(string Nom, double Longueur, double Largeur)
			: this(Nom, Longueur, Largeur, 0)
		{
		}
		public Piece(string Nom, double Longueur, double Largeur, double Hauteur)
		{
			this.Nom = Nom;
			this.IdPiece = compteurPiece++;
			this.SetDimensions(Longueur, Largeur, Hauteur);
		}
		
		public double this[string index]
		{
			get {
				if (index == "Longueur")
					return this.Longueur;
				else if (index == "Largeur")
					return this.Largeur;
				else if (index == "Hauteur")
					return this.Hauteur;
				else if (index == "Surface")
					return this.Surface;
				else
					throw new Exception("Invalid Index");
			}
		}
		
		public void SetDimensions(double Longueur, double Largeur, double Hauteur)
		{
			this.Longueur = Longueur;
			this.Largeur = Largeur;
			this.Hauteur = Hauteur;
		}
		
		public bool TesterEgalitéClés(Piece p2)
		{
			return this.Nom == p2.Nom;
		}
		
		public static bool operator==(Piece p1, Piece p2)
		{
			return p1.TesterEgalitéClés(p2);
		}
		
		public static bool operator!=(Piece p1, Piece p2)
		{
			return !(p1 == p2);
		}
		
		public bool Equals(Piece other)
		{
			return this == other;
		}
		
		public override bool Equals(object obj)
		{
			if (obj is Piece)
				return this.Equals((Piece) obj);
			else
				return false;
		}
		
		public override int GetHashCode()
		{
			return this.Nom.GetHashCode();
		}
		
		public int CompareTo(Piece other)
		{
			return this.Nom.CompareTo(other.Nom);
		}
		
		public override string ToString()
		{
			return string.Format("[Piece: Nom={0}, IdPiece={1}, " +
			                     "Longueur={2}, Largeur={3}, Hauteur={4}]",
			                     Nom, IdPiece, Longueur, Largeur, Hauteur);
		}
	}
}