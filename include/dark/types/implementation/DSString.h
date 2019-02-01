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
DSString* StringJoin(int count, ...);


$implementation( DSString );

$override( ToString,         (DSStringToString)ToString, "$@:v" );
$override( Equals,           (DSStringEquals)Equals, "B@:@@" );
$method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
$method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
$override( CompareTo,        (DSStringCompareTo)CompareTo, "i@:@" );
$method( Length,             (DSStringLength)Length, "i@:v" );
$method( IsEmpty,            (DSStringIsEmpty)IsEmpty, "B@:v" );    
$method( CharAt,             (DSStringCharAt)CharAt, "c@:i" );
$method( CompareToIgnoreCase, (DSStringCompareToIgnoreCase)CompareToIgnoreCase, "@:" );    
$method( Concat,             (DSStringConcat)Concat, "v@:$" );
$method( Concatc,            (DSStringConcatc)Concatc, "v@:c" );
$method( Contains,           (DSStringContains)Contains, "B@:$" );
$method( CopyOf,             (DSStringCopyOf)CopyOf, "$@:v" );
$method( EndsWith,           (DSStringEndsWith)EndsWith, "B@:$" );
$method( StartsWith,         (DSStringStartsWith)StartsWith, "B@:$" );
$method( GetBytes,           (DSStringGetBytes)GetBytes, "b@:*" );
$method( IndexOf,            (DSStringIndexOf)IndexOf, "i@:$" );
$method( LastIndexOf,        (DSStringLastIndexOf)LastIndexOf, "i@:$" );
$method( ToLowerCase,        (DSStringToLowerCase)ToLowerCase, "$@:v" );
$method( ToUpperCase,        (DSStringToUpperCase)ToUpperCase, "$@:v" );
$method( Trim,               (DSStringTrim)Trim, "$@:v" );
$method( Substring,          (DSStringSubstring)Substring, "$@:ii" );

$ivar( value, sizeof( char* ), "*" );
$ivar( length, sizeof( int ), "i" );

$DSString.Join = StringJoin;

$end;

