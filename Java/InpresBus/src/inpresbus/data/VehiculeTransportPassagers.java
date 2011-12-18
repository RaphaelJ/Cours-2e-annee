package inpresbus.data;

import inpresbus.data.exceptions.BadIdentifierException;
import java.io.Serializable;

public class VehiculeTransportPassagers
        extends VehiculeTransport implements Serializable {
    private int _nbrePassagers;
    
    public VehiculeTransportPassagers(String identifiant,
            Dimensions3D dimensions, int nbrePassagers)
            throws BadIdentifierException
    {
        super(identifiant, dimensions);
        
        this._nbrePassagers = nbrePassagers;
    }

    public int getNbrePassagers()
    {
        return _nbrePassagers;
    }

    public void setNbrePassagers(int nbrePassagers)
    {
        this._nbrePassagers = nbrePassagers;
    }
}