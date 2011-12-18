package inpresbus.tests;

import java.lang.*;

import inpresbus.data.*;
import inpresbus.data.exceptions.*;

public class MainClass {
    public static void main(String[] args)
    {
        System.out.println("Debut des tests");
        try {
            new Dimensions3D(5, 10, 10);
        } catch (BadDimensionsException e) {
             System.out.println("Exception Dimension OK");
        }
        
        try {
            new Bus("???", new Dimensions3D(10, 10, 10), 75,
                false, true, "Robermont");
        } catch (BadIdentifierException e) {
             System.out.println("Exception Bus OK");
        } catch (BadDimensionsException e) {
        }
        
        try {
            new Conducteur("Javaux", "Raphael", "...", null);
        } catch (BadIdentifierException e) {
            System.out.println("Exception conducteur OK");
        }
    }
}
