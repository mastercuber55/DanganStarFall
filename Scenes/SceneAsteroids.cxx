#include "Scenes.hpp"

SceneAsteroids::SceneAsteroids(SceneGame *ptr) {
  Parent = ptr;
}

void SceneAsteroids::Spawn() {
  float radius = GetRandomValue(16, 128);
  Vector2 pos = Frax::GetRandomPositionOutside(Parent->Cam, radius);
  float vel = GetRandomValue(-4, 4);

  auto Asteroid = new Entity(Rectangle{pos.x, pos.y, radius * 2, radius * 2},
                             "Assets/Asteroid.png");

  Asteroid->Health = radius * 2;

  Asteroid->Phy = new Pebble::Obj(Parent->Space, {pos.x, pos.y},
                                  Asteroid->Health / 2 * 0.75, radius * 2);

  Asteroid->Phy->setAngularVelocity(vel);
  Asteroid->Phy->setAngle(vel); // Reusing ig.
  Asteroid->Phy->applyImpulse({vel * 10000, 0});
  Asteroid->Phy->setCollisionType((int)CollisionTypes::Asteroid);

  list.push_back(Asteroid);
}

void SceneAsteroids::Update(float dt) {
  (void)dt;
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
    PlaySound(Parent->explosion);
  }
}

void SceneAsteroids::Draw() {
for (Entity *asteroid : list) {
    asteroid->Draw();
  }
}