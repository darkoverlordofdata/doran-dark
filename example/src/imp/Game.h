#pragma once

$implementation(Game);

$method(ToString,           (GameToString)ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");

$method(Start,              Start, "@@:v");
$method(ProcessInput,       ProcessInput, "@@:v"); 
$method(Update,             Update, "@@:f");
$method(Render,             Render, "@@:f");
$method(DoCollisions,       DoCollisions, "@@:v");
$method(ResetLevel,         ResetLevel, "@@:v");
$method(ResetPlayer,        ResetPlayer, "@@:v");
$method(SetKey,             SetKey, "@@:iB");
$method(SetState,           SetState, "@@:i");

$ivar("State", sizeof(GameState), "i");
$ivar("Keys", sizeof(bool)*1024, "B");
$ivar("Width", sizeof(GLuint), "I");
$ivar("Height", sizeof(GLuint), "I");
$ivar("Levels", sizeof(id), "@");
$ivar("Level", sizeof(GLuint), "I");

$end;
