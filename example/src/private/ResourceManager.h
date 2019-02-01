/**
 * ResourceManager class
 */
#pragma once

$implementation( ResourceManager );

$method( ToString,           (ResourceManagerToString)ToString, "$@:v" );
$method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
$method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
$method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );

$ResourceManager.Shaders = new(DSHashmap, of(Shader));
$ResourceManager.Textures = new(DSHashmap, of(Texture2D));
$ResourceManager.LoadShader = LoadShader;
$ResourceManager.GetShader = GetShader;
$ResourceManager.LoadTexture = LoadTexture;
$ResourceManager.GetTexture = GetTexture;
$ResourceManager.Dtor = Dtor;
$ResourceManager.loadShaderFromFile = loadShaderFromFile;
$ResourceManager.loadTextureFromFile = loadTextureFromFile;

$end;
