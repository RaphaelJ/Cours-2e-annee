package inpresbus.beans;

import java.util.EventListener;

public interface BusAlertListener extends EventListener {
    public void NewBusAlertReceived(BusAlertEvent e);
}
