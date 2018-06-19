#include "Dark/Shape.h"

/* Abstract Methods */
static TDark_Shape_Area     Abstract_Dark_Shape_Area;
static TDark_Shape_Draw     Abstract_Dark_Shape_Draw;
static TDark_Shape_ToString Abstract_Dark_Shape_ToString;

static struct Dark_Shape_VTable const vTable = 
{ 
    .ToString = &Abstract_Dark_Shape_ToString,
    .Area =     &Abstract_Dark_Shape_Area,
    .Draw =     &Abstract_Dark_Shape_Draw
};

/**
 * Constructor
 */
Dark_Shape* Dark_Shape_Ctor(Dark_Shape *this, int x, int y)
{
    Dark_Object_Ctor(&this->base);
    this->_vptr = &vTable;
    this->x = x;
    this->y = y;
    return this;
}

/**
 * MoveBy
 */
void Dark_Shape_MoveBy(Dark_Shape * const this, int dx, int dy) {
    assert(this != NULL);
    this->x += dx;
    this->y += dy;
}

/**
 * Abstract ToString
 */
static char* Abstract_Dark_Shape_ToString(Dark_Shape const * const this)
{
    assert(0);
    return "";
}

/**
 * Abstract Area
 */
static int Abstract_Dark_Shape_Area(Dark_Shape const * const this)
{
    assert(0); // abstract method
    return 0;
}


/**
 * Abstract Draw
 */
static void Abstract_Dark_Shape_Draw(Dark_Shape const * const this)
{
    assert(0); // abstract method
}


