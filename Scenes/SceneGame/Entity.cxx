#include "Entity.hpp"

void Entity::Draw() {
  cpVect pos = Phy->getPosition();

  SetCenter({static_cast<float>(pos.x), static_cast<float>(pos.y)});
  Rotation = Phy->getAngle() * RAD2DEG;

  Rect::Draw();
  // DrawHitbox();
}

void Entity::DrawHitbox() {
  cpVect pos = Phy->getPosition();

  if (Phy->Radius == 0) {
    DrawPolyLines({static_cast<float>(pos.x), static_cast<float>(pos.y)}, 4, Phy->Size.x*0.75, Rotation - 45, RED);
  } else {
    DrawCircleLines(pos.x, pos.y, Phy->Radius, RED);
  }
}

Entity::~Entity() {
  delete Phy;
}