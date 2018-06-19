#ifndef _VALA_SHAPE_H_
#define _VALA_SHAPE_H_

#include <Dark/Object.h>
/**
 * Shape Instance Data
 */
typedef struct 
{
    Dark_Object base;
    struct Dark_Shape_VTable const *_vptr;
    int x; 
    int y; 
    
} Dark_Shape;

/**
 * Define Shape Interface
 */
typedef Dark_Shape*     (TDark_Shape_Ctor)      (Dark_Shape*, int, int);
typedef void            (TDark_Shape_MoveBy)    (Dark_Shape*, int, int);
typedef char*           (TDark_Shape_ToString)  (Dark_Shape const * const this);
typedef int             (TDark_Shape_Area)      (Dark_Shape const * const this);
typedef void            (TDark_Shape_Draw)      (Dark_Shape const * const this);

/**
 * Declare Shape Interface
 */
TDark_Shape_Ctor                Dark_Shape_Ctor;
TDark_Shape_MoveBy              Dark_Shape_MoveBy;
static TDark_Shape_ToString     Dark_Shape_ToString;
static TDark_Shape_Area         Dark_Shape_Area;
static TDark_Shape_Draw         Dark_Shape_Draw;

/**
 * Shape VTable
 */
typedef struct Dark_Shape_VTable 
{
    TDark_Shape_ToString* ToString;
    TDark_Shape_Area* Area;
    TDark_Shape_Draw* Draw;
};

/**
 * Dispatch
 */
static inline char* Dark_Shape_ToString(Dark_Shape const * const this)
{
    return (*this->_vptr->ToString)(this);
}


static inline int Dark_Shape_Area(Dark_Shape const * const this)
{
    return (*this->_vptr->Area)(this);
}

static inline void Dark_Shape_Draw(Dark_Shape const * const this)
{
    (*this->_vptr->Draw)(this);
}

#endif /* _VALA_SHAPE_H_ */
