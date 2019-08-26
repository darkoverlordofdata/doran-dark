#pragma once
#include <dark/Foundation.h>


type (Rectangle)
{
    Class isa;
    int x;
    int y;
    int width;
    int height;
};

delegate (Rectangle, New,          Rectangle*, (Rectangle*, int, int, int, int));
delegate (Rectangle, ToString,     char*, (const Rectangle* const));
delegate (Rectangle, Contains,     char*, (const Rectangle* const, const Rectangle* const));

/**
 * Rectangle vtable
 */
vtable (Rectangle) 
{
    const RectangleToString         ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const RectangleContains         Contains;
};

/**
 * Put it all together
 */
static inline vptr(Rectangle);
/**
 * Class Loader callback
 */
static inline Class ClassLoadRectangle(Class base) 
{
    Class cls = createClass(base, Rectangle);
    addMethod(cls, Rectangle,   ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, Rectangle,   Contains);
    return cls;
}


method Rectangle* New(Rectangle* self, int x, int y, int width, int height)
{
    extends(Object);
    set_isa(Game);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;

    return self;
}

method bool Contains(Rectangle* self, Rectangle* other) {
    return ((((self->x <= other->x) && 
        ((other->x + other->width) <= (self->x + self->width))) && 
        (self->y <= other->y)) && 
        ((other->y + other->height) <= (self->y + self->height)));

}


method char* ToString(const Rectangle* const self)
{
    return "Rectangle { }";
}