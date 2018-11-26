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
#include <stdarg.h>
#include <dark/core.h>


char* STR_JOIN(int count, ...)
{
    int size = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);  

    /**
     * Caclulate length of the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args1, char*);
        size += strlen(str);
    }
    va_end(args1);
    char* result = calloc(size+1, sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args2, char*);
        strcat(result, str);
    }
    va_end(args2);
    return result;
}
