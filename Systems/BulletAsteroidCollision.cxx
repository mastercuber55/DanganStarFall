#include "index.hpp"
#include <chipmunk/chipmunk.h>
#include <chipmunk/cpArbiter.h>
#include <chipmunk/cpShape.h>
#include <raylib.h>

cpBool bulletAsteroidBegin(cpArbiter* arb, cpSpace* space, void * data) {
  cpShape * sBullet;
  cpShape*  sAsteroid;

  cpArbiterGetShapes(arb, &sBullet, &sAsteroid);

  auto Bullet = static_cast<Pebble::Obj *>(cpShapeGetUserData(sBullet));
  auto Asteroid = static_cast<Pebble::Obj *>(cpShapeGetUserData(sAsteroid));

  Bullet->ShouldDelete = true;
  Asteroid->ShouldDelete = true;

  return cpFalse;
}