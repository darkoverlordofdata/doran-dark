#pragma once
#include <dark/Foundation.h>


type (Point)
{
    Class isa;
    int x;
    int y;
};

delegate (Point, New,          Point*, (Point*, int, int));
delegate (Point, ToString,     char*, (const Point* const));

/**
 * Point vtable
 */
vtable (Point) 
{
    const PointToString             ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
};

/**
 * Put it all together
 */
static inline vptr(Point);
/**
 * Class Loader callback
 */
static inline Class objc_loadPoint(Class super) 
{
    Class cls = createClass(super, Point);
    addMethod(cls, Point,       ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    return cls;
}


method Point* New(Point* self, int x, int y)
{
	extends(Object);
    self->isa = objc_getClass("Point");
    self->x = x;
    self->y = y;
    return self;
}

method char* ToString(const Point* const self)
{
    return "Point { }";
}