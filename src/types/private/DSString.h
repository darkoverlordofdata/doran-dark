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
$implementation( DSString );

$method( ToString,           DSString_ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );
$method( CompareTo,          DSString_CompareTo, "i@:@" );
$method( Dispose,            DSString_Dispose, "v@:v" );
$method( Length,             Length, "i@:v" );
$method( IsEmpty,            DSString_IsEmpty, "B@:v" );    
$method( CharAt,             DSString_CharAt, "c@:i" );
$method( CompareToIgnoreCase, DSString_CompareToIgnoreCase, "@:" );    
$method( Concat,             DSString_Concat, "v@:$" );
$method( Concatc,            DSString_Concatc, "v@:c" );
$method( Contains,           DSString_Contains, "B@:$" );
$method( CopyOf,             DSString_CopyOf, "$@:v" );
$method( EndsWith,           DSString_EndsWith, "B@:$" );
$method( StartsWith,         DSString_StartsWith, "B@:$" );
$method( GetBytes,           DSString_GetBytes, "b@:*" );
$method( IndexOf,            DSString_IndexOf, "i@:$" );
$method( LastIndexOf,        DSString_LastIndexOf, "i@:$" );
$method( ToLowerCase,        DSString_ToLowerCase, "$@:v" );
$method( ToUpperCase,        DSString_ToUpperCase, "$@:v" );
$method( Trim,               DSString_Trim, "$@:v" );

$ivar( value, sizeof( char* ), "*" );
$ivar( length, sizeof( int ), "i" );

$end;

