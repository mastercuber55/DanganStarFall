#include "main.hpp"
#include <raylib.h>

namespace Asteroids {
std::vector<std::unique_ptr<Frax::Rect>> list;
void Spawn(Camera2D cam, cpSpace *space) {

  float radius = GetRandomValue(16, 128);
  Vector2 pos = Frax::GetRandomPositionOutside(cam, radius);
  float vel = GetRandomValue(0, 8);

  std::unique_ptr<Frax::Rect> Asteroid = std::make_unique<Frax::Rect>(
      Rectangle{pos.x, pos.y, radius * 2, radius * 2}, "Assets/Asteroid.png");

  auto Obj = new Pebble::Obj(space, {pos.x, pos.y}, radius, radius * 2);

  Obj->setAngularVelocity(vel);
  Obj->setAngle(vel); // Reusing ig.
  Obj->setVelocity({vel*100, 0});

  Asteroid->Data = Obj;

  list.push_back(std::move(Asteroid));
}
void Draw() {
  for (const auto &asteroid : list) {
    Pebble::Draw(asteroid.get());
  }
}
} // namespace Asteroids