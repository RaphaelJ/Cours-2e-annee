
package inpresbus.beans;

import java.beans.*;
import java.io.Serializable;

/**
 *
 * @author rapha
 */
public class BusAlertAnalyzeBean
        extends javax.swing.JDialog implements Serializable, BusAlertListener
{
    private String _evenement;
    
    public static final String PROP_MESSAGE_HORAIRE_A_TRANSMETTRE
            = "messageHoraireATransmettre";
    private String _messageHoraireATransmettre;
    private PropertyChangeSupport propertySupport
            = new PropertyChangeSupport(this);
    
    private javax.swing.JButton butValider;
    private javax.swing.JComboBox comboRetard;
    private javax.swing.JLabel labelTitre;
    private javax.swing.JLabel labelErreur;
    private javax.swing.JLabel labelRetard;
    private javax.swing.JLabel labelType;
    private javax.swing.JTextField textRetard;
    
    public BusAlertAnalyzeBean(java.awt.Frame parent, boolean modal) {
        super(parent, modal);
    }
    
    private void initComponents() {

        labelTitre = new javax.swing.JLabel();
        labelType = new javax.swing.JLabel();
        butValider = new javax.swing.JButton();
        comboRetard = new javax.swing.JComboBox();
        labelRetard = new javax.swing.JLabel();
        textRetard = new javax.swing.JTextField();
        labelErreur = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Un événement s'est produit!");

        labelTitre.setFont(new java.awt.Font("Sans Serif", 0, 18)); // NOI18N
        labelTitre.setText("Un événement s'est produit !");

        labelType.setText("Type d'événement: "+this._evenement);

        butValider.setText("Valider");
        butValider.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                butValiderActionPerformed(evt);
            }
        });

        comboRetard.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "minutes", "heures", "jours" }));

        labelRetard.setText("Retard:");

        labelErreur.setFont(new java.awt.Font("Sans Serif", 1, 13)); // NOI18N
        labelErreur.setForeground(new java.awt.Color(255, 0, 25));

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelType)
                    .addComponent(labelTitre)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(labelRetard)
                        .addGap(18, 18, 18)
                        .addComponent(textRetard, javax.swing.GroupLayout.DEFAULT_SIZE, 104, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(comboRetard, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(labelErreur, javax.swing.GroupLayout.DEFAULT_SIZE, 189, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(butValider)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(labelTitre)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(labelType)
                .addGap(8, 8, 8)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(comboRetard, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelRetard)
                    .addComponent(textRetard, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 12, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(butValider)
                    .addComponent(labelErreur, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        pack();
    }
    public String getMessageHoraireATransmettre() {
        return this._messageHoraireATransmettre;
    }
    
    public void setMessageHoraireATransmettre(String value) {
        String oldValue = this._messageHoraireATransmettre;
        this._messageHoraireATransmettre = value;
        
        propertySupport.firePropertyChange(
                PROP_MESSAGE_HORAIRE_A_TRANSMETTRE,
                oldValue, this._messageHoraireATransmettre
        );
    }
    
    public void addPropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.addPropertyChangeListener(listener);
    }
    
    public void removePropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.removePropertyChangeListener(listener);
    }

    public void NewBusAlertReceived(BusAlertEvent e) {
        this._evenement = e.getEvenement();
        
        initComponents();
        
        this.setVisible(true);
    }

    private void butValiderActionPerformed(java.awt.event.ActionEvent evt) {
        int nombre = Integer.parseInt(this.textRetard.getText());
        String unite = (String) this.comboRetard.getSelectedItem();
        
        this.setMessageHoraireATransmettre(
            "Suite à un incident ("+ this._evenement +"), " +
            "un retard de "+nombre+" "+unite+" sera occasioné.\n"
        );
        
        this.dispose();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                BusAlertAnalyzeBean dialog = new BusAlertAnalyzeBean(
                        new javax.swing.JFrame(), true
                );
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {

                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }
}