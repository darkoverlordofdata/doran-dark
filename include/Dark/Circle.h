#ifndef _VALA_CIRCLE_H_
#define _VALA_CIRCLE_H_

#include <Dark/Shape.h>
/**
 * Shape Instance Data
 */
typedef struct 
{
    Dark_Shape base;
    int radius; 
    
} Dark_Circle;

/**
 * Define Circle Interface
 */
typedef Dark_Circle*    (TDark_Circle_New)       (int, int, int);
typedef Dark_Circle*    (TDark_Circle_Ctor)      (Dark_Circle*, int, int, int);
typedef int             (TDark_Circle_Area)      (Dark_Shape const * const this);
typedef void            (TDark_Circle_Draw)      (Dark_Shape const * const this);
typedef char*           (TDark_Circle_ToString)  (Dark_Shape const * const this);

/**
 * Declare Circle Interface
 */
TDark_Circle_New                Dark_Circle_New;
TDark_Circle_Ctor               Dark_Circle_Ctor;
static TDark_Circle_Area        Dark_Circle_Area;
static TDark_Circle_Draw        Dark_Circle_Draw;
static TDark_Circle_ToString    Dark_Circle_ToString;

#endif /* _VALA_CIRCLE_H_ */
