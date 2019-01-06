#pragma once

$implementation(GameObject);

$method(ToString,           (GameObjectToString)ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");
$method(Draw,               Draw, "v@:@");

$ivar(Position,  sizeof(Vec2), "!");
$ivar(Size, sizeof(Vec2), "!");
$ivar(Velocity, sizeof(Vec2), "!");
$ivar(Color, sizeof(Vec3), "!");
$ivar(Rotation, sizeof(GLfloat), "f");
$ivar(IsSolid, sizeof(GLfloat), "B");
$ivar(Destroyed, sizeof(GLfloat), "B");
$ivar(Sprite, sizeof(GLfloat), "@");
$ivar(Name, sizeof(GLfloat), "*");

$end;
