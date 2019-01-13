/**
 * GameLevel class
 */
#pragma once

$implementation( GameLevel );

$ivar( Bricks, sizeof( id ), "@" );

$method( ToString,           (GameLevelToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );

$method( Load,               (GameLevelLoad)Load, "@@:*ii" );
$method( Draw,               (GameLevelDraw)Draw, "v@:@" );
$method( IsCompleted,        (GameLevelIsCompleted)IsCompleted, "B@:v" );

$end;