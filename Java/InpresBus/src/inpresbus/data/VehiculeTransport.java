package inpresbus.data;

import inpresbus.data.exceptions.*;
import java.io.Serializable;

public abstract class VehiculeTransport
       implements ObjetMateriel, EstIdentifiable, Serializable {
    private String _identifiant;
    private Dimensions3D _dimensions;
    
    public VehiculeTransport(String identifiant, Dimensions3D dimensions) throws BadIdentifierException
    {
        this.setIdentifiant(identifiant);
        this._dimensions = dimensions;
    }

    public Dimensions3D getDimensions()
    {
        return _dimensions;
    }

    public String getIdentifiant()
    {
        return _identifiant;
    }

    public final void setIdentifiant(String identifiant)
            throws BadIdentifierException
    {
        if (Utils.verifierIdentifiant(identifiant)) {
            throw new BadIdentifierException(
                    "L'identifiant ne peut contenir que " +
                    "des caractères alphanumériques"
            );
        } else
            this._identifiant = identifiant;
    }
}