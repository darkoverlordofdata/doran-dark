/**
 * Game class
 */
#pragma once

$implementation( Game );

$ivar( "State",     sizeof( GameState ), "i" );
$ivar( "Keys",      sizeof( bool ) * 1024, "B" );
$ivar( "Width",     sizeof( GLuint ), "I" );
$ivar( "Height",    sizeof( GLuint ), "I" );
$ivar( "Levels",    sizeof( id ), "@" );
$ivar( "Level",     sizeof( GLuint ), "I" );

$method( ToString,           (GameToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );

$method( Start,              (GameStart)Start, "@@:v" );
$method( ProcessInput,       (GameProcessInput)ProcessInput, "@@:v" ); 
$method( Update,             (GameUpdate)Update, "@@:f" );
$method( Render,             (GameRender)Render, "@@:f" );
$method( DoCollisions,       (GameDoCollisions)DoCollisions, "@@:v" );
$method( ResetLevel,         (GameResetLevel)ResetLevel, "@@:v" );
$method( ResetPlayer,        (GameResetPlayer)ResetPlayer, "@@:v" );
$method( SetKey,             (GameSetKey)SetKey, "@@:iB" );
$method( SetState,           (GameSetState)SetState, "@@:i" );

$end;
