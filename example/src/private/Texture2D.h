/**
 * Texture2D class
 */
#pragma once

$implementation( Texture2D );

$ivar( Id,              sizeof( GLuint ), "I" );
$ivar( path,            sizeof( char* ), "*" );
$ivar( Width,           sizeof( GLuint ), "I" );
$ivar( Height,          sizeof( GLuint ), "I" );
$ivar( InternalFormat,  sizeof( GLuint ), "I" );
$ivar( ImageFormat,     sizeof( GLuint ), "I" );
$ivar( WrapS,           sizeof( GLuint ), "I" );
$ivar( WrapT,           sizeof( GLuint ), "I" );
$ivar( FilterMin,       sizeof( GLuint ), "I" );
$ivar( FilterMag,       sizeof( GLuint ), "I" );

$method( ToString,          (Texture2DToString)ToString, "$@:v" );
$method( Equals,            DSObject_Equals, "B@:@@" );
$method( GetHashCode,       DSObject_GetHashCode, "l@:v" );
$method( Dispose,           DSObject_Dispose, "v@:v" );
$method( Generate,          (Texture2DGenerate)Generate, "v@:II*" );
$method( Bind,              (Texture2DBind)Bind, "v@:@" );

$end;

