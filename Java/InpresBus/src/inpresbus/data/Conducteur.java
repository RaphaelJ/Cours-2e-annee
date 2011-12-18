package inpresbus.data;

import inpresbus.data.*;
import inpresbus.data.exceptions.*;
import java.io.Serializable;

public class Conducteur
        extends Personne implements Serializable {
    private String _matricule;
    private Bus _busHabituel;
    
    public static final LazyDir<Conducteur> dir = new LazyDir<Conducteur>("conducteurs");
    
    public Conducteur(String nom, String prenom, String matricule, Bus busHabituel)
            throws BadIdentifierException
    {
        super(nom, prenom);
        
        this.setMatricule(matricule);
        this._busHabituel = busHabituel;
    }

    @Override
    public String getIdentifiant()
    {
//        if (this.getMatricule() == null && this.getBusHabituel() != null)
//            return this.getBusHabituel().getIdentifiant();
//        else
            return this.getMatricule();
    }

    public String getMatricule()
    {
        return _matricule;
    }

    public final void setMatricule(String matricule)
            throws BadIdentifierException
    {
        if (Utils.verifierIdentifiant(matricule)) {
            throw new BadIdentifierException(
                    "Le matricule ne peut contenir que " +
                    "des caractères alphanumériques"
            );
        } else
            this._matricule = matricule;
    }

    public Bus getBusHabituel()
    {
        return _busHabituel;
    }

    public void setBusHabituel(Bus busHabituel)
    {
        this._busHabituel = busHabituel;
    }
}