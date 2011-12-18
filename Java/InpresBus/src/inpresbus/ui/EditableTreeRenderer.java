package inpresbus.ui;

import java.awt.Component;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeCellRenderer;

public class EditableTreeRenderer implements TreeCellRenderer
{   
    public Component getTreeCellRendererComponent(
                JTree tree, Object obj, boolean selected, boolean expanded,
                boolean leaf, int row, boolean hasFocus)
    {
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) obj;
        if (node.getUserObject() instanceof JComponent)
            return (Component) node.getUserObject();
        else
            return new JLabel((String) node.getUserObject());
    }
}