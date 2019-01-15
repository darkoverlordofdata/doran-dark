#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
This is our integer linked list type (Null is an empty list)
(it is immutable, note the consts)
*/
typedef struct IntList_s const * const IntList;
static IntList const Nil = NULL; /* the empty list */

/*
This is a Cons element. (singly linked list element)
(note: also immutable)
*/
typedef struct IntList_s
{
  int32_t const value;
  IntList next;
} Cons;

/*
This is a pointer to where we are going to store the the "result" of our
 computation. We won't really know the type of it until we have our whole 
 chain of calls built up, so it's void * for now. 
 I think if I did this in C++ I could use templates to make this
 statically typed.
*/
typedef void * const CPS_Result;

/* prototypes and typedefs for the continuations */
typedef void (*MakeListCallback)(IntList list, CPS_Result result);
void make_list( uint32_t const array_size
              , int32_t const array[]
              , IntList new_list
              , MakeListCallback const callback
              , CPS_Result result);

void reverse_and_stuff(IntList list, CPS_Result result);
void stuff_list(IntList list, CPS_Result result);

typedef void (*ReversedListCallback)( IntList reversed_list
                                    , CPS_Result result);
void reverse( IntList list
            , IntList reversed_list
            , ReversedListCallback const callback
            , CPS_Result result);

typedef void(*VoidMappable)(int32_t const value);
void void_map_array( VoidMappable const f
                   , uint32_t const size
                   , int32_t const * const array);
void print_value(int32_t const value);


/*
Define an array to reverse, and an array to store the result, and 
 then do stuff
*/
int main(int argc, char * argv[])
{
  (void)argc;
  (void)argv;
  
  int32_t my_array[] = { 2, 5, 6, 1, 9, 23, 7654, 12, 0, 4};
  uint32_t const my_array_size = sizeof(my_array)/sizeof(my_array[0]);
  
  int32_t result[my_array_size];
  /* call make_list and pass reverse_and_stuff as the "continuation".
     The action to perform next. */
  make_list(my_array_size, my_array, Nil, reverse_and_stuff, result);

  /* print out our reversed array */
  void_map_array(print_value, my_array_size, result);
  printf("\n");
  return 0;
}


/* constructs a linked list from an array */
void make_list( uint32_t const array_size
              , int32_t const array[]
              , IntList new_list
              , MakeListCallback const callback
              , CPS_Result result)
{
  if (array_size > 0)
  {
    Cons cell = { .value = array[array_size - 1], .next = new_list };
    make_list(array_size - 1, array, &cell, callback, result);
  }
  else
  {
    /* call our "continuation" with our result */
    callback(new_list, result);
  }
}

/* function that reverses a list and then stores it in an array */
void reverse_and_stuff(IntList list, CPS_Result result)
{
  reverse(list, Nil, stuff_list, result);
}

/* stuffs a linked list into an array */
void stuff_list(IntList list, CPS_Result result)
{
  if (Nil != list)
  {
    int32_t * array = result;
    array[0] = list->value;
    stuff_list(list->next, array + 1);
  }
}

void reverse( IntList list
            , IntList reversed_list
            , ReversedListCallback const callback
            , CPS_Result result)
{
  if (Nil == list)
  {
    callback(reversed_list, result);
  }
  else
  {
    /* build up the reversed list */
    Cons cell = { .value = list->value, .next = reversed_list };
    reverse(list->next, &cell, callback, result);
  }
}

/*
"loops" over an array and performs action f on each element
*/
void void_map_array( VoidMappable const f
                   , uint32_t const size
                   , int32_t const * const array)
{
  if (size > 0)
  {
    f(array[0]);
    void_map_array(f, size - 1, array + 1);
  }
}


void print_value(int32_t const value)
{
  printf("%d ", value);
}