
//$ method (\w*[*]?) (\w*)\((\w*)(.*)\;


//$ delegate ($3, $2, $1, ($3$4);


/**
 * Ecs${Name} Vtable
 */
vtable (Ecs${Name}) 
{
    const ObjectToString        ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    //$     const $3$2       $2;
};

static inline vptr(Ecs${Name});
/**
 * Create the class loader
 */
static inline Class ClassLoadEcs${Name}(Class base) 
{
    Class cls = createClass(base, Ecs${Name});
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    //$     addMethod(cls, $3, $2);
    return cls; 
}

