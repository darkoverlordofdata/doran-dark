## C Overloaded

combine clang overload attribute and polymorphic patterns into a 'generic c'.

influences: objective-c, nim. 

ObjC is the opposite of GLib - GLib attempts to be compatible with every ani-pattern in the wild. It coddles every edge case it can find. ObjC on the other hand forces you to follow a well thought out pattern. This makes it much more simple to understand than the rats nest called GLib.
Tne point is not to replicate objc, but to have objc objects available in c.

### Compatability
No effort has been made to be compatible with c++. Come on - if you are using c++ why would you use this?

### VTables
Currently, I'm loading vtables for each class at startup. Selectors are overloadable and so are resolved at compile time. The only run time part is the startup logic.

It would simplify coding to do it more like apple - lookup the selector at runtime. this means no overloading needed, no method mapping logic in startup. 

    IMP(id this, SEL cmd, ...)
    
I could use the vtable to cache the function pointers after they are found. This also would make late-binding more natural.

### Exceptions
[cexcept.h 2.0.1 (2008-Jul-19-Sat)](http://www.nicemice.net/cexcept/)
