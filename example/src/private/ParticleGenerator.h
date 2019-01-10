/**
 * ParticleGenerator class
 */
#pragma once

$implementation( ParticleGenerator );

$ivar( particles,   sizeof( id ), "@" );
$ivar( amount,      sizeof( GLuint ), "I" );
$ivar( shader,      sizeof( id ), "@" );
$ivar( texture,     sizeof( id ), "@" );
$ivar( VAO,         sizeof( GLuint ), "I" );

$method( ToString,           (ParticleGeneratorToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );

$method( Update,             (ParticleGeneratorUpdate)Update, "v@:f@i!" );
$method( Draw,               (ParticleGeneratorDraw)Draw, "v@:@" );

$end;
