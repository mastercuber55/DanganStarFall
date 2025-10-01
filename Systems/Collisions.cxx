#include "index.hpp"
#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_types.h>
#include <chipmunk/cpArbiter.h>
#include <chipmunk/cpShape.h>
#include <raylib.h>

cpBool bulletSomethingBegin(cpArbiter *arb, cpSpace *space, void *data) {
  cpShape *sBullet;
  cpShape *sSomething;

  cpArbiterGetShapes(arb, &sBullet, &sSomething);

  auto Bullet = static_cast<Pebble::Obj *>(cpShapeGetUserData(sBullet));
  auto Something = static_cast<Pebble::Obj *>(cpShapeGetUserData(sSomething));

  Bullet->ShouldDelete = true;
  Something->ShouldDelete = true;

  return cpFalse;
}