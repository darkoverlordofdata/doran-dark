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
#include <dark/core.h>
#include <dark/DSClass.h>
#include <stdlib.h>
#include <gc.h>
#include <ctype.h>
#include <stddef.h>

void __attribute__((constructor(101))) __objc_load()
{
    GC_INIT();
    GC_enable_incremental();
    objc_loadFramework();
}

/**
 *  stop the garbage collector
 */
void __attribute__((destructor)) __objc_unload()
{
}

#ifndef _WIN64
int strcmpi (const char *s1, const char *s2)
{
  const unsigned char *p1 = (const unsigned char *) s1;
  const unsigned char *p2 = (const unsigned char *) s2;
  unsigned char c1, c2;

  if (p1 == p2)
    return 0;

  do
    {
      c1 = tolower (*p1++);
      c2 = tolower (*p2++);
      if (c1 == '\0')
	break;
    }
  while (c1 == c2);
  
  return c1 - c2;
}
#endif


#ifndef _WIN64
strlwr(char *str)
{
  char *s;

  for(s = str; *s; s++)
    *s = tolower((unsigned char)*s);
  return str;
}
#endif

#ifndef _WIN64
strupr(char *str)
{
  char *s;

  for(s = str; *s; s++)
    *s = toupper((unsigned char)*s);
  return str;
}
#endif
