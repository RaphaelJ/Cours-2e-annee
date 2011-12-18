package inpresbus.data;

import inpresbus.data.Lazy;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;
import java.io.FileInputStream;

public class UsersManager {
    // JAVA FAIL (pas de fonctions anonymes, pas de Currying, pas de composition,
    //           de type Lazy, ni de surcharge du cast)
    // En C# :
    //private static Lazy<Properties> _properties = () => {
    //    Properties p = new Properties();
    //    p.load(new FileInputStream("users.properties"));
    //    return p;
    //}
    // En Haskell:
    // content <- readFile "user.properties"
    // let properties = map ((\(f, s) -> (f, tail s)) . break (== '=')) $ lines content
    
    private static Lazy<Properties> _properties = new Lazy<Properties>(
        new LazyAction<Properties>() {
            public Properties compute() throws IOException
            {
                Properties p = new Properties();
                FileInputStream s = new FileInputStream("users.properties");
                p.load(s);
                s.close();
                return p;
            }
        }
    );
    
    public static boolean authentificate(String user, String password)
            throws FileNotFoundException, IOException, Exception
    {
        // get() => JAVA FAIL (pas de surchage de l'opérateur =)
        return password.equals(_properties.get().getProperty(user));
    }
}
