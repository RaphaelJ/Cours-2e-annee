package inpresbus.data.exceptions;

import java.lang.Exception;

public class BadIdentifierException extends Exception {
    String _message;
    
    public BadIdentifierException()
    {
        this._message = null;
    }
    
    public BadIdentifierException(String message)
    {
        this._message = message;
    }
}