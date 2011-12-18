package inpresbus.beans;

import ThreadUtils.ThreadRandomGenerator;
import ThreadUtils.UtilisateurNombre;
import java.beans.*;
import java.io.Serializable;
import javax.swing.event.EventListenerList;

/**
 *
 * @author rapha
 */
public class BusAlertGeneratorBean implements Serializable {
    
    private EventListenerList listeners = new EventListenerList();
    
    public BusAlertGeneratorBean()
    {
        final BusAlertGeneratorBean nestedThis = this;
        
        new ThreadRandomGenerator(
            new UtilisateurNombre() {
                public void changeNombre(int n)
                {
                    Double r = Math.random() * 5;
                    
                    switch (r.intValue()) {
                    case 0:
                        nestedThis.fireAlert(BusConstants.INCIDENT_ACCIDENT);
                        break;
                    case 1:
                        nestedThis.fireAlert(BusConstants.INCIDENT_GREVE);
                        break;
                    case 2:
                        nestedThis.fireAlert(BusConstants.INCIDENT_NEIGE);
                        break;
                    case 3:
                        nestedThis.fireAlert(BusConstants.INCIDENT_PANNE);
                        break;
                    case 4:
                        nestedThis.fireAlert(BusConstants.INCIDENT_VERGLAS);
                        break;
                    }
                }
            }, 0, 10, 10, 5
        ).start();
    }
        
    public void addAlertListener(BusAlertListener l)
    {
        listeners.add(BusAlertListener.class, l);
    }
    
    public void removeFooListener(BusAlertListener l)
    {
        listeners.remove(BusAlertListener.class, l);
    }
    
    protected void fireAlert(String evenement)
    {
         Object[] objListeners = this.listeners.getListenerList();
         BusAlertEvent event = null;

         for (int i = objListeners.length-2; i>=0; i-=2) {
             if (objListeners[i] == BusAlertListener.class) {
                 if (event == null)
                     event = new BusAlertEvent((Object) this, evenement);

                 ((BusAlertListener) objListeners[i+1]).NewBusAlertReceived(event);
             }
         }
    }
}
