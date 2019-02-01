/**
 * GameLevel class
 */
#pragma once

$implementation( GameLevel );

$ivar( Bricks, sizeof( id ), "@" );

$method( ToString,           (GameLevelToString)ToString, "$@:v" );
$method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
$method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
$method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );

$method( Load,               (GameLevelLoad)Load, "@@:*ii" );
$method( Draw,               (GameLevelDraw)Draw, "v@:@" );
$method( IsCompleted,        (GameLevelIsCompleted)IsCompleted, "B@:v" );

$end;
