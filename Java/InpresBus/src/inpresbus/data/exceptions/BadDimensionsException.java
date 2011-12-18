package inpresbus.data.exceptions;

import java.lang.Exception;

public class BadDimensionsException extends Exception {
    String _message;
    
    public BadDimensionsException()
    {
        this._message = null;
    }
    
    public BadDimensionsException(String message)
    {
        this._message = message;
    }
    
}
