#include "Dark/Rect.h"

/* Overrides */
static TDark_Rect_Area          Virtual_Dark_Rect_Area;
static TDark_Rect_Draw          Virtual_Dark_Rect_Draw;
static TDark_Rect_ToString      Virtual_Dark_Rect_ToString;

static struct Dark_Shape_VTable const vTable = 
{ 
    .Area =     &Virtual_Dark_Rect_Area,
    .Draw =     &Virtual_Dark_Rect_Draw,
    .ToString = &Virtual_Dark_Rect_ToString
};

/**
 * Constructor
 */
Dark_Rect* Dark_Rect_Ctor(Dark_Rect * this, int x, int y, int width, int height)
{
    Dark_Shape_Ctor(&this->base, x, y);
    this->base._vptr = &vTable;
    // this->base.base._vptr->ToString = _Dark_Rect_ToString;
    this->width = width;
    this->height = height;
    return this;
}

/**
 * Allocate a new Rect
 */
Dark_Rect* Dark_Rect_New(int x, int y, int width, int height)
{
    Dark_Rect* this;
    this = (Dark_Rect*)calloc (1, sizeof(Dark_Rect));
    return Dark_Rect_Ctor(this, x, y, width, height);
}

/**
 * Area implementation
 */
static int Virtual_Dark_Rect_Area(Dark_Shape const * const this)
{
    Dark_Rect const * const base = (Dark_Rect const *)this;
    return base->width * base->height;
}

/**
 * Draw implementation
 */
static void Virtual_Dark_Rect_Draw(Dark_Shape const * const this)
{
    Dark_Rect const * const base = (Dark_Rect const *)this;
}

    
/**
 * ToString
 */
static char* Virtual_Dark_Rect_ToString(Dark_Shape const * const this)
{
    assert(this != NULL);
    return (char*)"System.Rect";
}
