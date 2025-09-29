#include "index.hpp"
#include <algorithm>
#include <memory>
#include <raylib.h>

bool ShouldDeleteAsteroid(const std::unique_ptr<Frax::Rect> &asteroid) {
  auto box = std::any_cast<Pebble::Obj *>(asteroid->Data);
  return box->ShouldDelete;
}

namespace Asteroids {
std::vector<std::unique_ptr<Frax::Rect>> list;
void Spawn(Camera2D cam, cpSpace *space) {

  float radius = GetRandomValue(16, 128);
  Vector2 pos = Frax::GetRandomPositionOutside(cam, radius);
  float vel = GetRandomValue(-4, 4);

  std::unique_ptr<Frax::Rect> Asteroid = std::make_unique<Frax::Rect>(
      Rectangle{pos.x, pos.y, radius * 2, radius * 2}, "Assets/Asteroid.png");

  auto Obj = new Pebble::Obj(space, {pos.x, pos.y}, radius, radius * 2);

  Obj->setAngularVelocity(vel);
  Obj->setAngle(vel); // Reusing ig.
  Obj->applyImpulse({vel * 10000, 0});

  Obj->setCollisionType((int)CollisionTypes::Asteroid);

  Asteroid->Data = Obj;

  list.push_back(std::move(Asteroid));
}
void Maintain(Sound *explosion) {
  for (int i = 0; i < (int)list.size(); i++) {
    auto &asteroid = list[i];
    auto box = std::any_cast<Pebble::Obj *>(asteroid->Data);

    if (box->ShouldDelete) {
      delete box;
      asteroid.reset();
      list.erase(list.begin() + i);
      --i;
      // PlaySound(*explosion);
    }
  }
}
void Draw() {
  for (const auto &asteroid : list) {
    Pebble::Draw(asteroid.get());
  }
}
} // namespace Asteroids