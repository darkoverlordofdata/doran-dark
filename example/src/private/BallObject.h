/**
 * BallObject class
 */
#pragma once

$implementation( BallObject );

$ivar( Position,    sizeof( Vec2 ), "!" );
$ivar( Size,        sizeof( Vec2 ), "!" );
$ivar( Velocity,    sizeof( Vec2 ), "!" );
$ivar( Color,       sizeof( Vec3 ), "!" );
$ivar( Rotation,    sizeof( GLfloat ), "f" );
$ivar( IsSolid,     sizeof( GLfloat ), "B" );
$ivar( Destroyed,   sizeof( GLfloat ), "B" );
$ivar( Sprite,      sizeof( GLfloat ), "@" );
$ivar( Name,        sizeof( GLchar ), "*" );
$ivar( Radius,      sizeof( float ), "f" );
$ivar( Stuck,       sizeof( bool ), "B" );

$method( ToString,      (BallObjectToString)ToString, "$@:v" );
$method( Equals,        DSObject_Equals, "B@:@@" );
$method( GetHashCode,   DSObject_GetHashCode, "l@:v" );
$method( Dispose,       DSObject_Dispose, "v@:v" );

$method( Draw,          (BallObjectDraw)Draw, "v@:@" );
$method( Move,          (BallObjectMove)Move, "v@:iI" );
$method( Reset,         (BallObjectReset)Reset, "v@:!!" );

$end;
