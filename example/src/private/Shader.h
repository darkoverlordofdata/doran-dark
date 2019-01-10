/**
 * Shader class
 */
#pragma once

$implementation( Shader );

$ivar( Id, sizeof( GLuint ), "I" );

$method( ToString,           (ShaderToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );

$method( Use,                (ShaderUse)Use, "@@:v" );
$method( Compile,            (ShaderCompile)Compile, "@@:**" );
$method( SetFloat,           SetFloat, "@@:*f" );
$method( SetInteger,         SetInteger, "@@:*i" );
$method( SetArray2f,         SetArray2f, "@@:*ff" );
$method( SetArray2,          SetArray2, "@@:*!" );
$method( SetArray3f,         SetArray3f, "@@:*fff" );
$method( SetArray3,          SetArray3, "@@:*!" );
$method( SetArray4f,         SetArray4f, "@@:*ffff" );
$method( SetArray4,          SetArray4, "@@:*!" );
$method( SetMatrix4,         SetMatrix4, "@@:*!" );
$method( SetMatrix,          SetMatrix, "@@:*!" );

$end;
