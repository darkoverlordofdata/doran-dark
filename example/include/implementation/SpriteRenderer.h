/**
 * SpriteRenderer class
 */
#pragma once

$implementation( SpriteRenderer );

$ivar( shader,  sizeof( id ), "@" );
$ivar( VAO,     sizeof( GLuint ), "I" );

$method( ToString,           (SpriteRendererToString)ToString, "$@:v" );
$method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
$method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
$method( Dispose,            (SpriteRendererDispose)Dispose, "v@:v" );
$method( Draw,               (SpriteRendererDraw)Draw, "@@:@!!f!" );

$end;
