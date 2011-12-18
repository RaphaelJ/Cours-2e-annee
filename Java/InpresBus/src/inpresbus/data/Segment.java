package inpresbus.data;

import java.io.Serializable;

public class Segment
        implements Serializable {
    private String _depart;
    private String _arrivee;
    private float _duree;
    
    public Segment(String depart, String arrivee, float duree)
    {
        this._depart = depart;
        this._arrivee = arrivee;
        this._duree = duree;    
    }

    public String getDepart()
    {
        return _depart;
    }

    public void setDepart(String depart)
    {
        this._depart = depart;
    }

    public String getArrivee()
    {
        return _arrivee;
    }

    public void setArrivee(String arrivee)
    {
        this._arrivee = arrivee;
    }

    public float getDuree()
    {
        return _duree;
    }

    public void setDuree(float duree)
    {
        this._duree = duree;
    }    
}