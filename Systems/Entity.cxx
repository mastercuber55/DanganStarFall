#include "index.hpp"
#include <raylib.h>

void Entity::Draw() {
  cpVect pos = Phy->getPosition();

  SetCenter({static_cast<float>(pos.x), static_cast<float>(pos.y)});
  Rotation = Phy->getAngle() * RAD2DEG;

  Rect::Draw();
}