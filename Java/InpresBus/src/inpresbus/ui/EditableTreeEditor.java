package inpresbus.ui;

import java.awt.Component;
import java.awt.event.MouseEvent;
import java.util.EventObject;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JTree;
import javax.swing.event.CellEditorListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeCellEditor;

public class EditableTreeEditor implements TreeCellEditor
{
    public Component getTreeCellEditorComponent(JTree tree, Object obj,
            boolean isSelected, boolean expanded, boolean leaf,
            int row)
    {
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) obj;
        if (node.getUserObject() instanceof JComponent) {
            JComponent widget = (JComponent) node.getUserObject();
            widget.setEnabled(true);
            return widget;
        } else
            return new JLabel((String) node.getUserObject());
    }
    public void addCellEditorListener(CellEditorListener l)
    {
    }
    public void cancelCellEditing()
    {
    }
    public Object getCellEditorValue()
    {
        return this;
    }
    public boolean isCellEditable(EventObject evt)
    {
        if (evt instanceof MouseEvent) {
            MouseEvent mevt = (MouseEvent) evt;
            return mevt.getClickCount() == 1;
        }
        return false;
    }
    public void removeCellEditorListener(CellEditorListener l)
    {
    }
    public boolean shouldSelectCell(EventObject anEvent)
    {
        return true;
    }
    public boolean stopCellEditing()
    {
        return false;
    }
}