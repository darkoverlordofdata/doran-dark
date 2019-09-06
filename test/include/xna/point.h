#pragma once
#include <dark/Foundation.h>


type (Point)
{
    Class isa;
    int x;
    int y;
};

method Point* New(Point* self, int x, int y)
{
	extends(Object);
    self->isa = isa(Point);
    self->x = x;
    self->y = y;
    return self;
}

method char* ToString(const Point* const self)
{
    return "Point { }";
}