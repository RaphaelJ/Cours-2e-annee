
package inpresbus.beans;

import java.util.EventObject;

/**
 *
 * @author rapha
 */
public class BusAlertEvent extends EventObject {
    protected String _evenement;
    
    public BusAlertEvent(Object source, String evenement) {
        super(source);
        
        this._evenement = evenement;
    }
    
    public String getEvenement()
    {
        return this._evenement;
    }
}
