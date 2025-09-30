#include "index.hpp"
#include <chipmunk/chipmunk_types.h>
#include <raylib.h>
#include <raymath.h>

namespace Enemies {
std::vector<Frax::Rect *> list;
void Spawn(Camera2D &cam, cpSpace *space) {
  Vector2 pos = Frax::GetRandomPositionInside(cam);

  auto Enemy =
      new Frax::Rect(Rectangle{pos.x, pos.y, 64, 64}, "Assets/Monokuma.png");

  auto Obj = new Pebble::Obj(space, {pos.x, pos.y}, {32, 32}, 32);

  Obj->setCollisionType((int)CollisionTypes::Enemy);

  Enemy->Data = Obj;

  list.push_back(Enemy);
}

void Maintain(Sound *explosion, cpVect player) {
  for (int i = 0; i < (int)list.size(); i++) {
    auto &enemy = list[i];
    auto box = std::any_cast<Pebble::Obj *>(enemy->Data);

    if (box->ShouldDelete) {
      delete box;
      delete enemy;
      list.erase(list.begin() + i);
      --i;
      PlaySound(*explosion);
      return;
    }

    auto pos = box->getPosition();

    int dist = Vector2Distance(
        {static_cast<float>(player.x), static_cast<float>(player.y)},
        {static_cast<float>(pos.x), static_cast<float>(pos.y)});

    if (dist > 300)
      continue;

    float currentAngle = box->getAngle();
    float targetAngle = atan2(player.y - pos.y, player.x - pos.x) - PI / 2;

    float angleDiff = targetAngle - currentAngle;
    angleDiff = Normalize(angleDiff, -PI, +PI);
    float rotationStep = 0.05;

    if (angleDiff > 0) {
      currentAngle += rotationStep;
    } else {
      currentAngle -= rotationStep;
    }

    box->setAngle(currentAngle);
    if (abs(angleDiff) < 1) {
      box->applyForce({0, -2000});
    }
  }
}

void Draw() {
  for (const auto &enemy : list) {
    Pebble::Draw(enemy);
  }
}
} // namespace Enemies
