package inpresbus.data;

import java.io.Serializable;
import java.util.Date;

public class Horaire
        implements Serializable, Comparable {
    private Bus _bus;
    private Conducteur _conducteur;
    private Ligne _ligne;
    private Date _heureDepart;
    
    public static final LazyDir<Horaire> dir = new LazyDir<Horaire>("horaires");
    
    public Horaire(Bus bus, Conducteur conducteur,
            Ligne ligne, Date heureDepart)
    {
        this._bus = bus;
        this._conducteur = conducteur;
        this._ligne = ligne;
        this._heureDepart = heureDepart;
    }

    public Bus getBus()
    {
        return _bus;
    }

    public void setBus(Bus bus)
    {
        this._bus = bus;
    }

    public Conducteur getConducteur()
    {
        return _conducteur;
    }

    public void setConducteur(Conducteur conducteur)
    {
        this._conducteur = conducteur;
    }

    public Ligne getLigne()
    {
        return _ligne;
    }

    public void setLigne(Ligne ligne)
    {
        this._ligne = ligne;
    }

    public Date getHeureDepart()
    {
        return _heureDepart;
    }

    public void setHeureDepart(Date heureDepart)
    {
        this._heureDepart = heureDepart;
    }

    public int compareTo(Object t)
    {
        Horaire other = (Horaire) t;
        
        return this.getHeureDepart().compareTo(other.getHeureDepart());
    }
}