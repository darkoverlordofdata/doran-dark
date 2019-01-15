#include <stdlib.h>
#include <stdio.h>

// Nothing  - None
// Just     - Some
//  Maybe   - Optiob

// // return :: Monad m => a -> m a
// typedef void * /* m a */ return_t(void * /* a */);

// // type kleisli_arrow a b = a -> m b
// typedef void * /* m b */ kleisli_arrow(void * /* a */);

// // bind :: Monad m => m a -> (a -> m b) -> m b
// typedef void * /* m b */ bind_t(void * /* m a */, kleisli_arrow * /* a -> m b */);

// return :: Monad m => a -> m a
typedef void * return_t(void * );

// type kleisli_arrow a b = a -> m b
typedef void * kleisli_arrow(void *);

// bind :: Monad m => m a -> (a -> m b) -> m b
typedef void * bind_t(void *, kleisli_arrow *);

// class Monad m
typedef struct {
    bind_t   * bind;
    return_t * return_;
} Monad;

// data Maybe a = Nothing | Just a
typedef struct {
    int is_it_there;
    void * /* a */ it;
} Maybe;
Maybe nothing = {0,0};
void * /* Maybe a */ just (void * a /* a */) {
    Maybe * result = (Maybe *)malloc(sizeof(Maybe));
    result->is_it_there=1;
    result->it=a;
    return result;
}

// instance Monad Maybe
bind_t   bindMaybe;
Monad maybeMonad = { bindMaybe, just};

void * /* Maybe b */ bindMaybe (void * ma /* Maybe a */
                               ,kleisli_arrow * a_mb /* a -> Maybe b */) {
    Maybe * maybeA = (Maybe *) ma;
    if(!maybeA->is_it_there) return &nothing;
    return a_mb(maybeA->it);
}

int weatherIsNice() {return 1;} // Imagine this is more complicated

// Maybe Int
void * getData() {
  if(weatherIsNice()) {
    int * it = (int *) malloc(sizeof(int));
    *it = 3;
    return just(it);
  } else return &nothing;
}

float data[] = {42.0f, 41.0f, 0.5f, 15.0f };

// Int -> Maybe Float
void * /* Maybe Float */ getMoreData(void * data_index_p /* Int */ ) {
    int data_index = * (int *) data_index_p;
    if(data_index>=0 && data_index < 4) {
        float * it = (float *)malloc(sizeof(float));
        *it = data[data_index];
        return just(it);
    } else return &nothing;
}

struct Unit /* () */ {} unit; // A data type that holds no information

// Float -> Maybe ()
void * print(void * f_ /* Float */) {
    float f = * (float *) f_;
    printf("%f", f); // Nobody said we're in a pure language! (Evil grin)
    return just(&unit);
}

/*
main = do
  a <- getData
  b <- getMoreData a
  print b
*/
int main() {
    maybeMonad.bind(maybeMonad.bind(getData(), getMoreData), print);
}