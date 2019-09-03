/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <limits.h>
#include <stdbool.h>

#define IsBitSet(object) _Generic((object), BitSet*: true, default: false)
#define AsBitSet(object) _Generic((object),                          \
                            BitSet*: (BitSet *)object,            \
                            default: nullptr)

/*
 * BitSets are packed into arrays of "words."  Currently a word
 * consists of 32 bits, requiring 5 address bits.
 */
const int ADDRESS_BITS_PER_WORD = 5;
const int64_t BITS_PER_WORD = 1 << ADDRESS_BITS_PER_WORD; // 32
const int64_t WORD_MASK = 0xffffffff;
/**
 * BitSet instance variables
 */
type (BitSet) 
{
    Class isa;
    int length;
    uint words[];
};

delegate (BitSet, New,          BitSet*, (BitSet*, const bool));
delegate (BitSet, ToString,     char*, (const BitSet* const));
delegate (BitSet, NextSetBit,   int, (BitSet* self, int fromIndex)); 
delegate (BitSet, Intersects,   bool, (BitSet* self, BitSet* set));
delegate (BitSet, IsEmpty,      bool, (BitSet* self));
delegate (BitSet, Set,          void, (BitSet* self, int bitIndex, bool value));
delegate (BitSet, Get,          bool, (BitSet* self, int bitIndex));
delegate (BitSet, Clear,        void, (BitSet* self, int bitIndex));

/**
 * BitSet vtable
 */
vtable (BitSet) 
{
    const BitSetToString        ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const BitSetNextSetBit      NextSetBit;
    const BitSetIntersects      Intersects;
    const BitSetIsEmpty         IsEmpty;
    const BitSetGet             Get;
    const BitSetSet             Set;
    const BitSetClear           Clear;

};


/**
 * @see http://stackoverflow.com/questions/6506356/java-implementation-of-long-numberoftrailingzeros
 */
method uint numberOfTrailingZeros(uint i) 
{
    if (i == 0) return 32;
    uint x = i;
    uint y;
    uint n = 31;
    y = x << 16; if (y != 0) { n -= 16; x = y; }
    y = x <<  8; if (y != 0) { n -=  8; x = y; }
    y = x <<  4; if (y != 0) { n -=  4; x = y; }
    y = x <<  2; if (y != 0) { n -=  2; x = y; }
    return (n - ((x << 1) >> 31));
}

/**
 * Put it all together
 */
static inline vptr(BitSet);
/**
 * Class Loader callback
 */
static inline Class ClassLoadBitSet(Class base) 
{
    Class cls = createClass(base, BitSet);
    addMethod(cls, BitSet,  ToString);
    addMethod(cls, Object,  Equals);
    addMethod(cls, BitSet,  NextSetBit);
    addMethod(cls, BitSet,  Intersects);
    addMethod(cls, BitSet,  IsEmpty);
    addMethod(cls, BitSet,  Get);
    addMethod(cls, BitSet,  Set);
    addMethod(cls, BitSet,  Clear);
    return cls;
}


/**
 * Constructor
 * create a new BitSet
 * 
 * @param value of bool
 * 
 */
method BitSet* New(BitSet* self, const int nbits) 
{
    extends(Object);
    self->isa = isa(BitSet);
    self->length = 0;
    if (nbits > 0)
    {
        auto size = (((nbits-1) >> ADDRESS_BITS_PER_WORD)+1);
        self = DSrealloc(self, sizeof(Class)+sizeof(int)+sizeof(uint)*size);
        for (auto i=0; i<size; i++)
            self->words[i]= 0;
        self->length = size;
    }
    return self;
}

method BitSet* New(BitSet* self) 
{
    return New(self, 0);
}

method int NextSetBit(BitSet* self, int fromIndex) 
{
    auto u = fromIndex >> ADDRESS_BITS_PER_WORD;
    auto wordsInUse = self->length;

    auto word = self->words[u] & (WORD_MASK << fromIndex);
    while (true) 
    {
        if (word != 0)
            return (int)((u * BITS_PER_WORD) + numberOfTrailingZeros(word));
        if (++u == wordsInUse)
            return -1;
        word = self->words[u];
    }
}


method bool Intersects(BitSet* self, BitSet* set) 
{
    auto wordsInUse = self->length;

    for (auto i = Min(wordsInUse, set->length) - 1; i >= 0; i--)
        if ((self->words[i] & set->words[i]) != 0)
            return true;
    return false;

}

method bool IsEmpty(BitSet* self) 
{
    return self->length == 0;
}

method void Set(BitSet* self, int bitIndex, bool value) 
{
    auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    auto wordsInUse = self->length;
    auto wordsRequired = wordIndex+1;

    if (wordIndex >= self->length) 
    {        
        self = DSrealloc(self, sizeof(Class)+sizeof(int)+sizeof(uint)*wordIndex+1);
    }
    if (wordsInUse < wordsRequired) 
    {
        // words.resize(int.max(2 * wordsInUse, wordsRequired));
        self = DSrealloc(self, sizeof(Class)+sizeof(int)+sizeof(uint)*Max(2 * wordsInUse, wordsRequired));
        for (auto i=wordsInUse, l=self->length; i<l; i++) 
        {
            self->words[i] = 0;
        }
    }

    if (value) 
    {
        self->words[wordIndex] |= (1 << bitIndex);
    } 
    else 
    {
        self->words[wordIndex] &= ~(1 << bitIndex);
    }
}

method bool Get(BitSet* self, int bitIndex) 
{
    auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    auto wordsInUse = self->length;

    return (wordIndex < wordsInUse) && ((self->words[wordIndex] & (1 << bitIndex)) != 0);
}

method void Clear(BitSet* self, int bitIndex)  
{
    if (bitIndex == -1) 
    {
        auto wordsInUse = self->length;
        while (wordsInUse>0) 
        {
            self->words[--wordsInUse] = 0;
        }
        return;
    }

    auto wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    if (self->length <= wordIndex)
        self = DSrealloc(self, sizeof(Class)+sizeof(int)+sizeof(uint)*wordIndex+1);
    self->words[wordIndex] &= ~(1 << bitIndex);
}


/**
 * Returns the string value of self BitSet
 */
method char* ToString(const BitSet* const self) {
    return "BitSet";
//     string[] s = new string[words.length];
//     for (var i=0; i<words.length; i++)
//     {
//         s[i] = "0x%08x".printf(words[i]);
//     }
//     return string.joinv("|", s);
// }
}

