//http://blog.sigfpe.com/2007/02/monads-in-c-pt-ii.html
#include <stdio.h>

typedef struct {
   int something;
   int just;
} MaybeInt;

MaybeInt returnMaybe(int i)
{
   MaybeInt r;
   r.something = 1;
   r.just = i;
   return r;
}

MaybeInt nothing()
{
   MaybeInt r;
   r.something = 0;
   return r;
}

MaybeInt bind(MaybeInt (*f)(int),MaybeInt x)
{
   if (x.something)
   {
       return f(x.just);
   } else
   {
       return nothing();
   }
}

MaybeInt print(int i)
{
   int written = printf("%d\n",i);
   if (written>=0)
   {
       return returnMaybe(written);
   } else
   {
       return nothing();
   }
}

MaybeInt printplus_bad(int i)
{
   MaybeInt x = print(i);
   return print(x.just); /* cheating! */
}

MaybeInt printplus(int i)
{
   MaybeInt x = print(i);
   return bind(print,x);
}
int main() {


   //  MaybeInt x = print(10);
    MaybeInt x = printplus(10);
    
}