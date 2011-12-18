/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * NouveauConducteur.java
 *
 * Created on 6 juin 2011, 17:52:29
 */
package inpresbus.ui;

import inpresbus.data.Bus;
import inpresbus.data.Conducteur;
import inpresbus.data.exceptions.BadIdentifierException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultComboBoxModel;

/**
 *
 * @author rapha
 */
public class NouveauConducteur extends javax.swing.JDialog {

    /** Creates new form NouveauConducteur */
    public NouveauConducteur(java.awt.Frame parent, boolean modal)
            throws Exception
    {
        super(parent, modal);
        initComponents();
        
        this._chargerListeBus();
    }
    
    private void _chargerListeBus()
            throws Exception
    {
        DefaultComboBoxModel model = (DefaultComboBoxModel) this.comboBus.getModel();
        
        for (String bus : Bus.dir.listerObjets()) {
            model.addElement(bus);
        }
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        labelNom = new javax.swing.JLabel();
        textNom = new javax.swing.JTextField();
        labelPrenom = new javax.swing.JLabel();
        textPrenom = new javax.swing.JTextField();
        butEnregistrer = new javax.swing.JButton();
        textMatricule = new javax.swing.JTextField();
        labelMatricule = new javax.swing.JLabel();
        labelBus = new javax.swing.JLabel();
        comboBus = new javax.swing.JComboBox();
        labelErreur = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Nouveau conducteur");

        labelNom.setText("Nom:");

        labelPrenom.setText("Prénom:");

        butEnregistrer.setText("Enregistrer");
        butEnregistrer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                butEnregistrerActionPerformed(evt);
            }
        });

        labelMatricule.setText("Matricule:");

        labelBus.setText("Bus habituel:");

        comboBus.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Aucun" }));

        labelErreur.setFont(new java.awt.Font("Sans Serif", 1, 13)); // NOI18N
        labelErreur.setForeground(java.awt.Color.red);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(labelErreur, javax.swing.GroupLayout.DEFAULT_SIZE, 277, Short.MAX_VALUE)
                        .addGap(18, 18, 18)
                        .addComponent(butEnregistrer))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(labelPrenom)
                            .addComponent(labelNom)
                            .addComponent(labelMatricule)
                            .addComponent(labelBus))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(comboBus, 0, 284, Short.MAX_VALUE)
                            .addComponent(textMatricule, javax.swing.GroupLayout.DEFAULT_SIZE, 284, Short.MAX_VALUE)
                            .addComponent(textPrenom, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 284, Short.MAX_VALUE)
                            .addComponent(textNom, javax.swing.GroupLayout.DEFAULT_SIZE, 284, Short.MAX_VALUE))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(textPrenom, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelPrenom))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(textNom, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelNom))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelMatricule)
                    .addComponent(textMatricule, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelBus)
                    .addComponent(comboBus, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 23, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(butEnregistrer)
                    .addComponent(labelErreur, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void butEnregistrerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_butEnregistrerActionPerformed
        try {
            Bus bus;
            if (this.comboBus.getSelectedIndex() == 0) // Aucun
                bus = null; 
            else {
                bus = (Bus) Bus.dir.chargerObjet(
                    (String) this.comboBus.getSelectedItem()
                );
            }
            
            Conducteur conducteur = new Conducteur(
                this.textNom.getText(), this.textPrenom.getText(),
                this.textMatricule.getText(), bus
            );
            
            Conducteur.dir.enregistrerObjet(
                    conducteur, conducteur.getIdentifiant()
            );
            
            this.dispose();
        } catch (BadIdentifierException ex) {
            this.labelErreur.setText("Saisissez un identifiant valide");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }//GEN-LAST:event_butEnregistrerActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                try {
                    NouveauConducteur dialog = new NouveauConducteur(new javax.swing.JFrame(), true);
                    dialog.addWindowListener(new java.awt.event.WindowAdapter() {

                        public void windowClosing(java.awt.event.WindowEvent e) {
                            System.exit(0);
                        }
                    });
                    dialog.setVisible(true);
                } catch (Exception ex) {
                    Logger.getLogger(NouveauConducteur.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton butEnregistrer;
    private javax.swing.JComboBox comboBus;
    private javax.swing.JLabel labelBus;
    private javax.swing.JLabel labelErreur;
    private javax.swing.JLabel labelMatricule;
    private javax.swing.JLabel labelNom;
    private javax.swing.JLabel labelPrenom;
    private javax.swing.JTextField textMatricule;
    private javax.swing.JTextField textNom;
    private javax.swing.JTextField textPrenom;
    // End of variables declaration//GEN-END:variables
}