package inpresbus.data;

import inpresbus.data.exceptions.*;
import java.io.Serializable;

public class Dimensions3D
        implements Dimensions, Serializable {
    private float _longueur;
    private float _largeur;
    private float _hauteur;
    
    public Dimensions3D(float longueur, float largeur, float hauteur)
            throws BadDimensionsException
    {
        checkDimensions(longueur, largeur);
        
        this._longueur = longueur;
        this._largeur = largeur;
        this._hauteur = hauteur;
    }

    public String getUnite()
    {
        return "mètre";
    }

    public float getLongueur()
    {
        return _longueur;
    }

    public void setLongueur(float longueur)
    {
        this._longueur = longueur;
    }

    public float getLargeur()
    {
        return _largeur;
    }

    public void setLargeur(float largeur)
    {
        this._largeur = largeur;
    }

    public float getHauteur()
    {
        return _hauteur;
    }

    public void setHauteur(float hauteur)
    {
        this._hauteur = hauteur;
    }
    
    public static void checkDimensions(float longueur, float largeur)
            throws BadDimensionsException
    {
        if (largeur > longueur)
            throw new BadDimensionsException("La largeur ne peut dépasser la longueur");
    }
}