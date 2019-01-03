
static void _objc_exception_noop(void) { } 

const void* vtable[] = {
    (void*)_objc_exception_noop,      // in-place destructor?
}
//==========================================================



Texture2D* t = $Texture2D();
_(t, Load, "filename");


Shader* shader = _(Resources, GetShader, "sprite");
_(shader, Use);
_(shader, SetInteger, "sprite", 0);
_(shader, SetMatrix4, "projection", &projection);

id _(id self, SEL _cmd, ...) {

    va_list args;
    va_start(args, _cmd);
	id result = objc_msgSendv(self, _cmd, args);
    va_end(args);
    return id;
}

/*
*/
id overload invoke(Texture2D this, char* cmd, ...);
id overload invoke(Shader this, char* cmd, ...);

id overload invoke(Texture2D this, char* cmd, ...) {
    DSLog("Texture2D %s", cmd);
}
id overload invoke(Shader this, char* cmd, ...) {
    DSLog("Shader %s", cmd);
}

void Add(DSArray* this, Any item) {
	_(this, "Add", item);
}

