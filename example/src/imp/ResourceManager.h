/**
 * ResourceManager class
 */
#pragma once

$implementation( ResourceManager );

$method( ToString,           (ResourceManagerToString)ToString, "$@:v" );
$method( Equals,             DSObject_Equals, "B@:@@" );
$method( GetHashCode,        DSObject_GetHashCode, "l@:v" );
$method( Dispose,            DSObject_Dispose, "v@:v" );

$ResourceManager.Shaders = NewDSHashmap();
$ResourceManager.Textures = NewDSHashmap();
$ResourceManager.LoadShader = LoadShader;
$ResourceManager.GetShader = GetShader;
$ResourceManager.LoadTexture = LoadTexture;
$ResourceManager.GetTexture = GetTexture;
$ResourceManager.Dtor = Dtor;
$ResourceManager.loadShaderFromFile = loadShaderFromFile;
$ResourceManager.loadTextureFromFile = loadTextureFromFile;

$end;
