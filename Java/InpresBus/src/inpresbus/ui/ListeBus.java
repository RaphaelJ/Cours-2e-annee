/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * ListeBus.java
 *
 * Created on 4 juin 2011, 18:53:00
 */
package inpresbus.ui;

import inpresbus.data.Bus;
import inpresbus.data.Horaire;
import inpresbus.data.Ligne;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

/**
 *
 * @author rapha
 */
public class ListeBus extends javax.swing.JDialog {
    
    class EnServiceChangeListener implements ChangeListener {
        protected Bus bus;
        protected ListeBus dialog;
        
        public EnServiceChangeListener(Bus bus, ListeBus dialog)
        {
            this.bus = bus;
            this.dialog = dialog;
        }
        
        /** Défini si le bus est utilisé dans un horaire
         * @param bus
         * @return 
         */
        private boolean _busEnService(Bus bus)
                throws Exception
        {
            for (String nomHoraire : Horaire.dir.listerObjets()) {
                Horaire horaire = Horaire.dir.chargerObjet(nomHoraire);
                
                if (horaire.getBus().getIdentifiant().equals(bus.getIdentifiant()))
                    return true;
            }
            
            return false;
        }
        
        public void stateChanged(ChangeEvent e)
        {
            JCheckBox checkbox = (JCheckBox) e.getSource();
            
            if (this.bus.isEnService() != checkbox.isSelected()) {
                try {
                    this.bus.setEnService(checkbox.isSelected());

                    if (!checkbox.isSelected() && this._busEnService(bus)) {
                        this.dialog.labelErreur.setText(
                            "Le bus est utilisé dans un horaire"
                        );
                        checkbox.setSelected(true);
                    } else {
                        Bus.dir.enregistrerObjet(this.bus, this.bus.getIdentifiant());
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        }
    }

    /** Creates new form ListeBus */
    public ListeBus(java.awt.Frame parent, boolean modal)
    {
        super(parent, modal);
        initComponents();
        
        try {
            this.afficherBus();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void afficherBus() throws Exception
    {
        DefaultTreeModel model = (DefaultTreeModel) this.treeBus.getModel();
        DefaultMutableTreeNode rootNode = (DefaultMutableTreeNode) model.getRoot();
        
        // Permet d'afficher les CheckBox
        this.treeBus.setCellRenderer(new EditableTreeRenderer());
        
        // Permet l'édition des CheckBox
        this.treeBus.setCellEditor(new EditableTreeEditor());
        
        this.treeBus.setEditable(true);
        

        for (String refBus : Bus.dir.listerObjets()) {
            Bus bus = Bus.dir.chargerObjet(refBus);
            
            DefaultMutableTreeNode busNode = new DefaultMutableTreeNode(
                    bus.getIdentifiant()
            );
            
            busNode.add(new DefaultMutableTreeNode(
                    "Longueur: "
                    + bus.getDimensions().getLongueur() + " "
                    + bus.getDimensions().getUnite()
            ));
            busNode.add(new DefaultMutableTreeNode(
                    "Largeur: "
                    + bus.getDimensions().getLargeur() + " "
                    + bus.getDimensions().getUnite()
            ));
            busNode.add(new DefaultMutableTreeNode(
                    "Hauteur: "
                    + bus.getDimensions().getHauteur() + " "
                    + bus.getDimensions().getUnite()
            ));
            
            busNode.add(new DefaultMutableTreeNode(
                    "Nombre de passagers: " + bus.getNbrePassagers()
            ));
            
            busNode.add(new DefaultMutableTreeNode(
                    "Dépot: " + bus.getNomDepot()
            ));
            
            busNode.add(new DefaultMutableTreeNode(
                    bus.isArticule() ? "Bus articulé" : "Bus simple"
            ));
            
            JCheckBox check = new JCheckBox("En service", bus.isEnService());
            check.addChangeListener(new EnServiceChangeListener(bus, this));
            busNode.add(new DefaultMutableTreeNode(
                    check
            ));
            
            rootNode.add(busNode);
        }
        
        model.reload();
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        treeBus = new javax.swing.JTree();
        labelErreur = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Liste des bus");

        javax.swing.tree.DefaultMutableTreeNode treeNode1 = new javax.swing.tree.DefaultMutableTreeNode("Bus");
        treeBus.setModel(new javax.swing.tree.DefaultTreeModel(treeNode1));
        jScrollPane1.setViewportView(treeBus);

        labelErreur.setFont(new java.awt.Font("Sans Serif", 1, 13)); // NOI18N
        labelErreur.setForeground(java.awt.Color.red);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 482, Short.MAX_VALUE)
                    .addComponent(labelErreur, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 482, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 618, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(labelErreur, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGap(33, 33, 33))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                ListeBus dialog = new ListeBus(new javax.swing.JFrame(), true);
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {

                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel labelErreur;
    private javax.swing.JTree treeBus;
    // End of variables declaration//GEN-END:variables
}