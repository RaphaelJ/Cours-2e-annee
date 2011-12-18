package inpresbus.data;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class LazyDir<T> extends Lazy<File> {
    public LazyDir(final String directory)
    {
        super(new LazyAction<File>() {
            public File compute()
            {
                File dir = new File(directory);
                if (!dir.isDirectory())
                    dir.mkdir();
                
                return dir;
            }
        });
    }
    
    public String[] listerObjets()
            throws Exception
    {
        return this.get().list();
    }
    
    public void enregistrerObjet(T objet, String nom)
            throws Exception
    {
        File fObjet = new File(this.get(), nom);
        ObjectOutputStream out = new ObjectOutputStream(
            new FileOutputStream(fObjet)
        );
        
        try {
            out.writeObject(objet);
        } finally {
            out.close();
        }
    }
    
    public T chargerObjet(String nomObjet)
            throws Exception
    {
        ObjectInputStream in = new ObjectInputStream(
            new FileInputStream(new File(this.get(), nomObjet))
        );
        
        return (T) in.readObject();
     }
    
    public boolean objetExistant(String nomObjet)
            throws Exception
    {
        return new File(this.get(), nomObjet).exists();
    }
}
