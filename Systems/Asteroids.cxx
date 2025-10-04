#include "index.hpp"
#include <raylib.h>

namespace Asteroids {
std::vector<Entity *> list;
void Spawn(Camera2D cam, cpSpace *space) {

  float radius = GetRandomValue(16, 128);
  Vector2 pos = Frax::GetRandomPositionOutside(cam, radius);
  float vel = GetRandomValue(-4, 4);

  auto Asteroid = new Entity(Rectangle{pos.x, pos.y, radius * 2, radius * 2},
                             "Assets/Asteroid.png");

  Asteroid->Health = radius * 2;

  Asteroid->Phy = new Pebble::Obj(space, {pos.x, pos.y},
                                  Asteroid->Health / 2 * 0.75, radius * 2);

  Asteroid->Phy->setAngularVelocity(vel);
  Asteroid->Phy->setAngle(vel); // Reusing ig.
  Asteroid->Phy->applyImpulse({vel * 10000, 0});  
  Asteroid->Phy->setCollisionType((int)CollisionTypes::Asteroid);

  list.push_back(Asteroid);
}
void Maintain(Sound *explosion) {
  for (int i = 0; i < (int)list.size(); i++) {
    auto &asteroid = list[i];

    if (!asteroid->Phy->Collision)
      continue;

    asteroid->Health--;

    if (asteroid->Health > 0)
      continue;

    delete asteroid;
    list.erase(list.begin() + i);
    --i;
    PlaySound(*explosion);
  }
}
void Draw() {
  for (Entity *asteroid : list) {
    asteroid->Draw();
  }
}
} // namespace Asteroids