package inpresbus.data;

import java.io.Serializable;

public class Personne
        implements EstIdentifiable, Serializable {
    private String _nom;
    private String _prenom;
    
    public Personne(String nom, String prenom)
    {
        this._nom = nom;
        this._prenom = prenom;
    }

    public String getIdentifiant()
    {
        return this.getPrenom() + " " + this.getNom();
    }

    public String getNom()
    {
        return _nom;
    }

    public void setNom(String nom)
    {
        this._nom = nom;
    }

    public String getPrenom()
    {
        return _prenom;
    }

    public void setPrenom(String prenom)
    {
        this._prenom = prenom;
    }
    
    public String toString()
    {
        return this.getPrenom() + " " +
               this.getNom() + " - " +
               this.getIdentifiant();
    }
}