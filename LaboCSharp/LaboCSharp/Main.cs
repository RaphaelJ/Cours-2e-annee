///////////////////////////////////////////////
// UN SEUL DEFINE NON COMMENTE A LA FOIS !!! //
///////////////////////////////////////////////

//#define TEST1
//#define TEST2
//#define TEST3
//#define TEST4
//#define TEST5
//#define TEST6
#define BONUS1

using System;
using System.Collections.Generic;
using System.Text;

namespace LaboCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            #region TEST1 : Test des constructeurs et propriétés
#if TEST1
            Piece p1 = new Piece();
            Piece p2 = new Piece("Cuisine", 6.5, 4.2);
            Piece p3 = new Piece("Salle à manger", 7.0, 5.5, 3.0);
            Piece p4 = new Piece();

            p4.SetDimensions(8.2, 5.3, 2.8);

            Console.WriteLine("p1:\t" + p1);
            Console.WriteLine("p2:\t" + p2);
            Console.WriteLine("p3:\t" + p3);
            Console.WriteLine("p4:\t" + p4);

            Console.ReadKey();
#endif
            #endregion

            #region TEST2 : Test de l'égalité de pièce à l'aide d'une méthode
#if TEST2
            Piece p1 = new Piece("PIECE_001",5.0,3.5);
            Piece p2 = new Piece("PIECE_002", 7.0, 3.8);
            Piece p3 = new Piece("PIECE_003", 4.3, 2.7);
            Piece p4 = new Piece("PIECE_001", 4.0, 5.5);

            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P2 : " + p2);

            if (p1.TesterEgalitéClés(p2))
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");            
            }
            else
            {
                Console.WriteLine("OK : " + p1.Nom + " est différent de " + p2.Nom);
            }

            Console.WriteLine();

            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P3 : " + p3);

            if (p1.TesterEgalitéClés(p3))
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");
            }
            else
            {
                Console.WriteLine("OK : " + p1.Nom + " est différent de " + p3.Nom);
            }

            Console.WriteLine();


            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P4 : " + p4);

            if (p1.TesterEgalitéClés(p4))
            {
                Console.WriteLine("Parfait : " + p1.Nom + " == " + p4.Nom);
            }
            else
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");
            }

            Console.ReadKey();
#endif
            #endregion

            #region TEST3 : Test de l'égalité de pièce à l'aide de l'opérateur ==
#if TEST3
            Piece p1 = new Piece("PIECE_001",5.0,3.5);
            Piece p2 = new Piece("PIECE_002", 7.0, 3.8);
            Piece p3 = new Piece("PIECE_003", 4.3, 2.7);
            Piece p4 = new Piece("PIECE_001", 4.0, 5.5);

            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P2 : " + p2);

            if (p1 == p2)
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");            
            }
            else
            {
                Console.WriteLine("OK : " + p1.Nom + " est différent de " + p2.Nom);
            }

            Console.WriteLine();

            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P3 : " + p3);

            if (p1 == p3)
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");
            }
            else
            {
                Console.WriteLine("OK : " + p1.Nom + " est différent de " + p3.Nom);
            }

            Console.WriteLine();


            Console.WriteLine("Test de l'égalité entre : ");
            Console.WriteLine("P1 : " + p1);
            Console.WriteLine("et");
            Console.WriteLine("P4 : " + p4);

            if (p1 == p4)
            {
                Console.WriteLine("Parfait : " + p1.Nom + " == " + p4.Nom);
            }
            else
            {
                Console.WriteLine("Oooops ! Something is wrong :( ... Try again !!!");
            }

            Console.ReadKey();
#endif
            #endregion

            #region TEST4 : Test présence d'un objet dans une liste
#if TEST4
            List<Piece> ListePieces = new List<Piece>();

            Piece p1 = new Piece("PIECE_001", 5.0, 3.5);
            Piece p2 = new Piece("PIECE_002", 7.0, 3.8);
            Piece p3 = new Piece("PIECE_003", 4.3, 2.7);
            Piece p4 = new Piece("PIECE_001", 4.0, 5.5);

            ListePieces.Add(p1);

            if (!ListePieces.Contains(p2))
            {
                ListePieces.Add(p2);
            }

            if (!ListePieces.Contains(p3))
            {
                ListePieces.Add(p3);
            }
            if (!ListePieces.Contains(p4))
            {
                ListePieces.Add(p4);
                Console.WriteLine("Ooops ! On ne devrait pas pouvoir ajouter une pièce ayant la meme clé qu'une pièce dejà présente dans la liste");
            }

            foreach (Piece p in ListePieces)
            {
                Console.WriteLine(p);
            }

            if (ListePieces.Count == 3)
            {
                Console.WriteLine("Ok la liste contient bien 3 pièces");
            }
            else
            {
                Console.WriteLine("Ooops !!! La liste devrait contenir 3 pièces");
            }
            
      
            Console.ReadKey();
#endif
            #endregion

            #region TEST5: Comparaison de pièces via le tri dans une liste
#if TEST5

            List<Piece> ListePieces = new List<Piece>();

            Piece p1 = new Piece("PIECE_001", 5.0, 3.5);
            Piece p2 = new Piece("PIECE_002", 7.0, 3.8);
            Piece p3 = new Piece("PIECE_003", 4.3, 2.7);
            Piece p4 = new Piece("PIECE_004", 4.0, 5.5);

            ListePieces.Add(p2);
            ListePieces.Add(p4);
            ListePieces.Add(p3);
            ListePieces.Add(p1);


            Console.WriteLine("Affichage de la liste non triée");

            foreach (Piece p in ListePieces)
            {
                Console.WriteLine(p);
            }


            try
            {
                Console.WriteLine("Tentative de tri");
                ListePieces.Sort();

                Console.WriteLine("Affichage de la liste triée");

                foreach (Piece p in ListePieces)
                {
                    Console.WriteLine(p);
                }
            }
            catch (Exception exc)
            {
                Console.WriteLine("Ooops ! Le tri n'a pu s'effectuer !!!", exc);
                
            }

            try
            {
                Console.WriteLine("Tentative de tri décroissant via un délégué");
                Comparison<Piece> compPieces = new Comparison<Piece>(Piece.ComparisonTriDecroissant);
                ListePieces.Sort(compPieces);

                Console.WriteLine("Affichage de la liste triée de manière decroissante");

                foreach (Piece p in ListePieces)
                {
                    Console.WriteLine(p);
                }
            }
            catch (Exception exc)
            {
                Console.WriteLine("Ooops ! Le tri n'a pu s'effectuer !!!" + exc);
            }

            // Ajouter la fonctionalité de tri de pièces par surface croissante
      
            Console.ReadKey();
#endif
            #endregion

            #region TEST6 : Test de l'indexeur
#if TEST6
            Piece p1 = new Piece("PIECE_001", 5.0, 3.5);

            try
            {

                Console.WriteLine("Longueur : " + p1["Longueur"]);
                Console.WriteLine("Largeur : " + p1["Largeur"]);
                Console.WriteLine("Hauteur : " + p1["Hauteur"]);
                Console.WriteLine("Surface : " + p1["Surface"]);
                Console.WriteLine("JavaPas : " + p1["JavaPas"]);
            }
            catch (Exception exc)
            {
                Console.WriteLine("Exception : " + exc.Message);
            }

            Console.ReadLine();

           
#endif
            #endregion

            #region BONUS : Une classe dédicacée à la comparaison
#if BONUS1
            List<Piece> ListePieces = new List<Piece>();

            Piece p1 = new Piece("PIECE_001", 5.0, 3.5);
            Piece p2 = new Piece("PIECE_002", 7.0, 3.8);
            Piece p3 = new Piece("PIECE_003", 4.3, 2.7);
            Piece p4 = new Piece("PIECE_004", 4.0, 5.5);

            ListePieces.Add(p2);
            ListePieces.Add(p4);
            ListePieces.Add(p3);
            ListePieces.Add(p1);


            Console.WriteLine("Affichage de la liste non triée");

            foreach (Piece p in ListePieces)
            {
                Console.WriteLine(p);
            }


            try
            {
                Console.WriteLine("Tentative de tri");
                ListePieces.Sort();

                Console.WriteLine("Affichage de la liste triée");

                foreach (Piece p in ListePieces)
                {
                    Console.WriteLine(p);
                }
            }
            catch (Exception exc)
            {
                Console.WriteLine("Ooops ! Le tri n'a pu s'effectuer !!!", exc);

            }

            try
            {
                Console.WriteLine("Tentative de tri décroissant via un objet comparer");
                MyPieceComparer myComparer = new MyPieceComparer();

                ListePieces.Sort(myComparer);

                Console.WriteLine("Affichage de la liste triée de manière decroissante");

                foreach (Piece p in ListePieces)
                {
                    Console.WriteLine(p);
                }
            }
            catch (Exception exc)
            {
                Console.WriteLine("Ooops ! Le tri n'a pu s'effectuer !!!", exc);
            }

            // Ajouter la fonctionalité de tri de pièces par surface croissante

            Console.ReadKey();

#endif
            #endregion

        }
    }
}