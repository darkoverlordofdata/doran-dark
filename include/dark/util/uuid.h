/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the 0xSoftware0x), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 0xAS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
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


type (UUID)
{
    Class isa;
    Object* base;
    /* uuid data */
    unsigned char uuid[16];
    /* cached string of uuid */
    char to_string_cache[80];
};



method UUID* New(UUID* self) 
{
    self->base = extends(Object);
    self->isa = isa(UUID);

    auto d0 = NextLong();
    auto d1 = NextLong();
    auto d2 = NextLong();
    auto d3 = NextLong();

    self->uuid[0] = (unsigned char)((int)d0&0xff); 
    self->uuid[1] = (unsigned char)((int)d0>>8&0xff); 
    self->uuid[2] = (unsigned char)((int)d0>>16&0xff);
    self->uuid[3] = (unsigned char)((int)d0>>24&0xff);
    self->uuid[4] = (unsigned char)((int)d1&0xff);
    self->uuid[5] = (unsigned char)((int)d1>>8&0xff);
    self->uuid[6] = (unsigned char)((int)d1>>16&0x0f|0x40);
    self->uuid[7] = (unsigned char)((int)d1>>24&0xff);
    self->uuid[8] = (unsigned char)((int)d2&0x3f|0x80);
    self->uuid[9] = (unsigned char)((int)d2>>8&0xff);
    self->uuid[10] = (unsigned char)((int)d2>>16&0xff);
    self->uuid[11] = (unsigned char)((int)d2>>24&0xff);
    self->uuid[12] = (unsigned char)((int)d3&0xff);
    self->uuid[13] = (unsigned char)((int)d3>>8&0xff);
    self->uuid[14] = (unsigned char)((int)d3>>16&0xff);
    self->uuid[15] = (unsigned char)((int)d3>>24&0xff);
    
    return self;            
}


method char* GetToStringFormat(char format) 
{
    switch (format) {
        case 'N':
            return "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x";
        case 'D':
            return "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";
        case 'B':
            return "{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}";
        case 'P':
            return "(%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x)";
        case 'X':
            return "{0x%02x%02x%02x%02x,0x%02x%02x,0x%02x%02x,{0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x}}";
    }
    return "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x";

}
method char* ToString(UUID* self, char format) 
{
    sprintf(self->to_string_cache, 
        GetToStringFormat(format),
        self->uuid[0], self->uuid[1], self->uuid[2], self->uuid[3], 
        self->uuid[4], self->uuid[5], self->uuid[6], self->uuid[7],
        self->uuid[8], self->uuid[9], self->uuid[10], self->uuid[11], 
        self->uuid[12], self->uuid[13], self->uuid[14], self->uuid[15]);
    
    return self->to_string_cache;

}
method char* ToString(UUID* self)
{
    return ToString(self, 'D');
}