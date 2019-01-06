#pragma once

$implementation(GameLevel);

$method(ToString,           (GameLevelToString)ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");
$method(Load,               Load, "@@:*ii");
$method(Draw,               (GameLevelDraw)Draw, "v@:@");
$method(IsCompleted,        IsCompleted, "B@:v");
$ivar(Bricks, sizeof(id), "@");

$end;
