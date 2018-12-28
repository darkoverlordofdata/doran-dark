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
#include <dark/io/File.h>
/* 
 * File implementation
 */


// static bool isSlash(char c) {
//     return (c == slash) || (c == altSlash);
// }

static bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a shash onto a string
 */
// static char* slashify(char* p) {
//     if ((strlen(p) > 0) && (p[0] != slash)) return join(slashString, p);
//     else return p;
// }

char* File_ToString(File const this)
{
    return "dark.io.File";
}

/**
 * Initialize a new File
 */
File File_Ctor(File const this)
{
    Number_Ctor(this);

    this->ToString      = File_ToString;

    return this;
}

/**
 * new File
 * 
 * 
 */
File File_New()
{
    return File_Ctor(new(File));
}

