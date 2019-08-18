NSObject looks somewhat like this:

    object->isa  => class {
        isa => metaclass {
            isa	
            superclass
            name
            itable => {
                ivar1
                ivarN
            }
            vtable => {
                method1
                methodN
            }
        }
        superclass
        name
        itable => {
            ivar1
            ivarN
        }
        vtable => {
            method1
            methodN
        }
    }
    
For simplicity, Object is flattened out:

    object->isa => class {
        isa	
        superclass
        name
        object->method1
        ...
        object->methodN
        class->method1
        ...
        class->methodN
        class->ivar1
        ...
        class->ivarN
    }
    object->ivar1
    ...
    object->ivarN

    This makes Object a fragile base class, and the developer is 
    responsible for keeping all the fields in sync between classes
    and their subclasses
    On the upside, this should have better perfomance.

