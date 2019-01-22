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
$implementation( DSFile );

$override( ToString,        (DSFileToString)ToString, "$@:v" );
$method( Equals,            DSObject_Equals, "B@:@@" );
$method( GetHashCode,       DSObject_GetHashCode, "l@:v" );
$method( Dispose,           DSObject_Dispose, "v@:v" );
$override( CompareTo,       (DSFileCompareTo)CompareTo, "i@:@" );
$method( IsInvalid,         (DSFileIsInvalid)IsInvalid, "B@:v");
$method( GetName,           (DSFileGetName)GetName, "$@:v" );
$method( GetParent,         (DSFileGetParent)GetParent, "$@:v" );
$method( GetParentFile,     (DSFileGetParentFile)GetParentFile, "$@:v" );
$method( IsAbsolute,        (DSFileIsAbsolute)IsAbsolute, "B@:v" );
$method( GetAbsolutePath,   (DSFileGetAbsolutePath)GetAbsolutePath, "$@:v" );
$method( GetAbsoluteFile,   (DSFileGetAbsoluteFile)GetAbsolutePath, "@@:v" );
$method( GetCanonicalPath,  (DSFileGetCanonicalPath)GetCanonicalPath, "$@:v");
$method( GetCanonicalFile,  (DSFileGetCanonicalFile)GetCanonicalFile, "@@:v");
$method( CanRead,           (DSFileCanRead)CanRead, "B@:v");
$method( CanWrite,          (DSFileCanWrite)CanWrite, "B@:v");
$method( Exists,            (DSFileExists)Exists, "B@:v");
$method( IsDirectory,       (DSFileIsDirectory)IsDirectory, "B@:v");
$method( IsFile,            (DSFileIsFile)IsFile, "B@:v");
$method( GetLength,         (DSFileGetLength)GetLength, "l@:v");

$DSFile.SeparatorChar = fs.GetSeparator();
$DSFile.Separator[0] = $DSFile.SeparatorChar;
$DSFile.Separator[1] = '\0';
$DSFile.PathSeparatorChar = fs.GetPathSeparator();
$DSFile.PathSeparator[0] = $DSFile.PathSeparatorChar;
$DSFile.PathSeparator[1] =  '\0';

$end;
