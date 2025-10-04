#include "index.hpp"
#include <raylib.h>

cpBool bulletSomethingBegin(cpArbiter *arb, cpSpace *space, void *data) {
  cpShape *sBullet;
  cpShape *sSomething;

  cpArbiterGetShapes(arb, &sBullet, &sSomething);

  auto Bullet = static_cast<Pebble::Obj *>(cpShapeGetUserData(sBullet));
  auto Something = static_cast<Pebble::Obj *>(cpShapeGetUserData(sSomething));

  Bullet->Collision = true;
  Something->Collision = true;

  return cpFalse;
}