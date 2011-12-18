package inpresbus.data;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.regex.Pattern;

public class Utils {
    public static boolean verifierIdentifiant(String identifiant)
    {
        // Uniquement des lettres, des chiffres et -
        return !Pattern.compile("[a-zA-Z0-9-]{1,}")
                       .matcher(identifiant)
                       .matches();
    }
}