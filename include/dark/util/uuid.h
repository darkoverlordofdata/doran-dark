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


/**
 * Generate an RFC 4122 compliant type 4 uuid
 * 
 */
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

    memcpy(&self->uuid[0], &d0, 8);
    memcpy(&self->uuid[4], &d1, 8);
    memcpy(&self->uuid[8], &d2, 8);
    memcpy(&self->uuid[12], &d3, 8);

    self->uuid[6] = self->uuid[6]&0x0f|0x40;
    self->uuid[8] = self->uuid[8]&0x3f|0x80;

    /**
     * 
     * todo: verify that its not a duplicate
     */

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
    // if (self->to_string_cache[0] == 0)
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