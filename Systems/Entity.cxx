#include "index.hpp"
#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_types.h>
#include <chipmunk/cpBody.h>
#include <chipmunk/cpPolyShape.h>
#include <chipmunk/cpShape.h>
#include <raylib.h>

void Entity::Draw() {
  cpVect pos = Phy->getPosition();

  SetCenter({static_cast<float>(pos.x), static_cast<float>(pos.y)});
  Rotation = Phy->getAngle() * RAD2DEG;

  Rect::Draw();
}

Entity::~Entity() {
  // delete Phy;
}