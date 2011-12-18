package inpresbus.data;

public class Lazy<T> {    
    private T _value;
    private boolean _computed = false;
    private LazyAction<T> _action;
    
    public Lazy(LazyAction<T> action)
    {
        this._action = action;
    }
    
    public final T get() throws Exception
    {
        if (!this._computed)
            this._value = this._action.compute();
        
        return this._value;
    }
}