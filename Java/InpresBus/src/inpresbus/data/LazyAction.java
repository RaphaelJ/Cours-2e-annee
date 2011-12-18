package inpresbus.data;

// JAVA FAIL : pas de méthodes anonymes
// La justification stupide : http://java.sun.com/docs/white/delegates.html
// - Bound method references add complexity to the type system
//      Les fonctions anonymes sont juste un sucre syntaxique pour 
//      des classes comme celles-ci ...
// - They result in loss of object orientation
//      Ou pas. De un, ils peuvent être simulés avec des classes
//      via un simple sucre syntaxique. De deux, les fonctions anonymes
//      en LISP étaient appellées « fonctions objet ». Ce de là qu'
//      Alan Kay a resorti le terme « Orienté objets » ...
// - They are limited in expressiveness
//     Ca, c'est ne pas savoir de quoi on parle ;
// - They are no more convenient than adapter objects
//     Depuis quand c'est plus « convenient » de créer 2 classes que
//     d'écrire « () => » ?

public abstract class LazyAction<T> {
    public T compute() throws Exception
    {
        return null;
    }
}