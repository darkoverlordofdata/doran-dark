#ifndef _VALA_RECT_H_
#define _VALA_RECT_H_

#include <Dark/Shape.h>
/**
 * Rect Instance Data
 */
typedef struct 
{
    Dark_Shape base;
    int width;
    int height;
    
} Dark_Rect;

/**
 * Define Rect Interface
 */
typedef Dark_Rect*      (TDark_Rect_New)       (int, int, int, int);
typedef Dark_Rect*      (TDark_Rect_Ctor)      (Dark_Rect*, int, int, int, int);
typedef int             (TDark_Rect_Area)      (Dark_Shape const * const this);
typedef void            (TDark_Rect_Draw)      (Dark_Shape const * const this);
typedef char*           (TDark_Rect_ToString)  (Dark_Shape const * const this);

/**
 * Declare Rect Interface
 */
TDark_Rect_New                  Dark_Rect_New;
TDark_Rect_Ctor                 Dark_Rect_Ctor;
static TDark_Rect_Area          Dark_Rect_Area;
static TDark_Rect_Draw          Dark_Rect_Draw;
static TDark_Rect_ToString      Dark_Rect_ToString;



#endif /* _VALA_RECT_H_ */
