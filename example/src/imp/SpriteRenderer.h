/**
 * SpriteRenderer class
 */
#pragma once

$implementation( SpriteRenderer );

$method( ToString,           (SpriteRendererToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );
$method( DrawSprite,         DrawSprite, "@@:@!!f!" );

$ivar( shader,  sizeof( id ), "@" );
$ivar( VAO,     sizeof( GLuint ), "I" );

$end;
