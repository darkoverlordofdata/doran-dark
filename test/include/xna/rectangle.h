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

method Rectangle* New(Rectangle* self, int x, int y, int width, int height)
{
    extends(Object);
    self->isa = isa(Rectangle);
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