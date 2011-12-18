package inpresbus.data;

import java.io.Serializable;

public class Ligne implements Serializable {
    private int _numero;
    private String _nom;
    private Segment[] _segments;
    
    public static final LazyDir<Ligne> dir = new LazyDir<Ligne>("lignes");
    
    public Ligne(int numero, String nom, Segment[] segments)
    {
        this._numero = numero;
        this._nom = nom;
        this._segments = segments;
    }

    public int getNumero()
    {
        return _numero;
    }

    public void setNumero(int numero)
    {
        this._numero = numero;
    }

    public String getNom()
    {
        return _nom;
    }

    public void setNom(String nom)
    {
        this._nom = nom;
    }

    public Segment[] getSegments()
    {
        return _segments;
    }

    public void setSegments(Segment[] segments)
    {
        this._segments = segments;
    }
}