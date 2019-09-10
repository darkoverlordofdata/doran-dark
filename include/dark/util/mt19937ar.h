/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#pragma once
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* Period parameters */  
#define MT19937_N 624
#define MT19937_M 397
#define MT19937_MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define MT19937_UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define MT19937_LOWER_MASK 0x7fffffffUL /* least significant r bits */

// static unsigned long mt[MT19937_N]; /* the array for the state vector  */
// static int mti=MT19937_N+1; /* mti==MT19937_N+1 means mt[MT19937_N] is not initialized */

type (Random)
{
    Class isa;
    Object* base;
    int mti;
    unsigned long mt[];
};


static Random* RandomInstance = nullptr;

static inline void init_genrand(Random* self, unsigned long s);
static inline void init_by_array(Random* self, unsigned long init_key[], int key_length);
static inline unsigned long genrand_int32(Random* self);
static inline double genrand_real1(Random* self);
method Random* New(Random* self, unsigned long seed);


method unsigned long NextLong(void)
{
    if (RandomInstance == nullptr) {
        unsigned long seed = time(nullptr);
        RandomInstance = new(Random, seed);
    }

    return genrand_int32(RandomInstance);
}

method double NextDouble(void)
{
    if (RandomInstance == nullptr) {
        unsigned long seed = time(nullptr);
        RandomInstance = new(Random, time(nullptr));
    }
    return genrand_real1(RandomInstance);
}


method Random* New(Random* self, unsigned long seed)
{
    self = DSrealloc(self, sizeof(Random)+(MT19937_N*sizeof(unsigned long)));
    self->base = extends(Object);
    self->isa = isa(Random);
    memset(self->mt, 0, (MT19937_N*sizeof(unsigned long)));
    self->mti = MT19937_N + 1;
    init_genrand(self, seed);
    return self;
}

method Random* New(Random* self, unsigned long seed[], int length)
{
    self = DSrealloc(self, sizeof(Random)+(MT19937_N*sizeof(unsigned long)));
    self->base = extends(Object);
    self->isa = isa(Random);
    memset(self->mt, 0, (MT19937_N*sizeof(unsigned long)));
    self->mti = MT19937_N + 1;
    init_by_array(self, seed, length);
    return self;

}


/* initializes mt[MT19937_N] with a seed */
static inline void init_genrand(Random* self, unsigned long s)
{
    self->mt[0]= s & 0xffffffffUL;
    for (self->mti=1; self->mti<MT19937_N; self->mti++) {
        self->mt[self->mti] = 
	    (1812433253UL * (self->mt[self->mti-1] ^ (self->mt[self->mti-1] >> 30)) + self->mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array self->mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        self->mt[self->mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
static inline void init_by_array(Random* self, unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(self, 19650218UL);
    i=1; j=0;
    k = (MT19937_N>key_length ? MT19937_N : key_length);
    for (; k; k--) {
        self->mt[i] = (self->mt[i] ^ ((self->mt[i-1] ^ (self->mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        self->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=MT19937_N) { self->mt[0] = self->mt[MT19937_N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=MT19937_N-1; k; k--) {
        self->mt[i] = (self->mt[i] ^ ((self->mt[i-1] ^ (self->mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        self->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=MT19937_N) { self->mt[0] = self->mt[MT19937_N-1]; i=1; }
    }

    self->mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
static inline unsigned long genrand_int32(Random* self)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MT19937_MATRIX_A};
    /* mag01[x] = x * MT19937_MATRIX_A  for x=0,1 */

    if (self->mti >= MT19937_N) { /* generate MT19937_N words at one time */
        int kk;

        if (self->mti == MT19937_N+1)   /* if init_genrand() has not been called, */
            init_genrand(self, 5489UL); /* a default initial seed is used */

        for (kk=0;kk<MT19937_N-MT19937_M;kk++) {
            y = (self->mt[kk]&MT19937_UPPER_MASK)|(self->mt[kk+1]&MT19937_LOWER_MASK);
            self->mt[kk] = self->mt[kk+MT19937_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<MT19937_N-1;kk++) {
            y = (self->mt[kk]&MT19937_UPPER_MASK)|(self->mt[kk+1]&MT19937_LOWER_MASK);
            self->mt[kk] = self->mt[kk+(MT19937_M-MT19937_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (self->mt[MT19937_N-1]&MT19937_UPPER_MASK)|(self->mt[0]&MT19937_LOWER_MASK);
        self->mt[MT19937_N-1] = self->mt[MT19937_M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        self->mti = 0;
    }
  
    y = self->mt[self->mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
static inline long genrand_int31(Random* self)
{
    return (long)(genrand_int32(self)>>1);
}

/* generates a random number on [0,1]-real-interval */
static inline double genrand_real1(Random* self)
{
    return genrand_int32(self)*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
static inline double genrand_real2(Random* self)
{
    return genrand_int32(self)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
static inline double genrand_real3(Random* self)
{
    return (((double)genrand_int32(self)) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
static inline double genrand_res53(Random* self) 
{ 
    unsigned long a=genrand_int32(self)>>5, b=genrand_int32(self)>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */

// int main(void)
// {
//     int i;
//     unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
//     init_by_array(init, length);
//     printf("1000 outputs of genrand_int32()\n");
//     for (i=0; i<1000; i++) {
//       printf("%10lu ", genrand_int32());
//       if (i%5==4) printf("\n");
//     }
//     printf("\n1000 outputs of genrand_real2()\n");
//     for (i=0; i<1000; i++) {
//       printf("%10.8f ", genrand_real2());
//       if (i%5==4) printf("\n");
//     }
//     return 0;
// }
