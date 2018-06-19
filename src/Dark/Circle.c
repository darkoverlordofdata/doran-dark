#include "Dark/Circle.h"

/* Overrides */
static TDark_Circle_Area          Virtual_Dark_Circle_Area;
static TDark_Circle_Draw          Virtual_Dark_Circle_Draw;
static TDark_Circle_ToString      Virtual_Dark_Circle_ToString;

static struct Dark_Shape_VTable const vTable = 
{ 
    .Area =     &Virtual_Dark_Circle_Area,
    .Draw =     &Virtual_Dark_Circle_Draw,
    .ToString = &Virtual_Dark_Circle_ToString,
};

/**
 * Constructor
 */
Dark_Circle* Dark_Circle_Ctor(Dark_Circle *this, int x, int y, int radius)
{
    Dark_Shape_Ctor(&this->base, x, y);
    this->base._vptr = &vTable;
    this->radius = radius;
    return this;
}

/**
 * Allocate a new Circle
 */
Dark_Circle* Dark_Circle_New(int x, int y, int radius)
{
    Dark_Circle* this;
    this = (Dark_Circle*)calloc (1, sizeof(Dark_Circle));
    return Dark_Circle_Ctor(this, x, y, radius);
}

/**
 * Area implementation
 */
static int Virtual_Dark_Circle_Area(Dark_Shape const * const this)
{
    Dark_Circle const * const base = (Dark_Circle const *)this;
    return 3 * base->radius * base->radius;
}

/**
 * Draw implementation
 */
static void Virtual_Dark_Circle_Draw(Dark_Shape const * const this)
{
    Dark_Circle const * const base = (Dark_Circle const *)this;
}

/**
 * ToString
 */
static char* Virtual_Dark_Circle_ToString(Dark_Shape const * const this)
{
    assert(this != NULL);
    return (char*)"System.Circle";
}
