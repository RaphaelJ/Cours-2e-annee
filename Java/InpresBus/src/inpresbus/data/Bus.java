package inpresbus.data;

import inpresbus.data.exceptions.BadIdentifierException;
import java.io.Serializable;

public class Bus
        extends VehiculeTransportPassagers implements Serializable {
    private boolean _articule;
    private boolean _enService;
    private String _nomDepot;
    
    public static final LazyDir<Bus> dir = new LazyDir<Bus>("bus");
    
    public Bus(String identifiant, Dimensions3D dimensions, int nbrePassagers,
            boolean articule, boolean enService, String nomDepot)
            throws BadIdentifierException
    {
        super(identifiant, dimensions, nbrePassagers);
        
        this._articule = articule;
        this._enService = enService;
        this._nomDepot = nomDepot;
    }

    public boolean isArticule()
    {
        return _articule;
    }

    public void setArticule(boolean articule)
    {
        this._articule = articule;
    }

    public boolean isEnService()
    {
        return _enService;
    }

    public void setEnService(boolean enService)
    {
        this._enService = enService;
    }

    public String getNomDepot()
    {
        return _nomDepot;
    }

    public void setNomDepot(String nomDepot)
    {
        this._nomDepot = nomDepot;
    }
}
