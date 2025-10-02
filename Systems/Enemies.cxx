#include "index.hpp"
#include <chipmunk/chipmunk_types.h>
#include <raylib.h>
#include <raymath.h>

namespace Enemies {
std::vector<Entity *> list;
void Spawn(Camera2D &cam, cpSpace *space) {
  Vector2 pos = Frax::GetRandomPositionOutside(cam);

  Entity *Enemy =
      new Entity(Rectangle{pos.x, pos.y, 64, 64}, "Assets/Monokuma.png");

  Enemy->Health = 10;

  Enemy->Phy = new Pebble::Obj(space, {pos.x, pos.y}, {32, 32}, 32);
  Enemy->Phy->setCollisionType((int)CollisionTypes::Enemy);

  list.push_back(Enemy);
}

void Maintain(Sound *explosion, cpVect player, cpSpace *space, float dt) {
  for (int i = 0; i < (int)list.size(); i++) {
    auto &Enemy = list[i];

    if (Enemy->Phy->Collision) {
      Enemy->Phy->Collision = false;
      Enemy->Health--;
      Enemy->Tint = {255, 255, 255, static_cast<unsigned char>(22.5f * Enemy->Health)};
      if (Enemy->Health <= 0) {
        delete Enemy->Phy;
        delete Enemy;
        list.erase(list.begin() + i);
        --i;
        PlaySound(*explosion);
        return;
      }
    }

    if (Enemy->cooldown > 0.0f)
      Enemy->cooldown -= dt;

    auto pos = Enemy->Phy->getPosition();
    float currentAngle = Enemy->Phy->getAngle();
    float targetAngle = atan2(player.y - pos.y, player.x - pos.x) - PI / 2;
    float rotationStep = 0.05;
    float angleDiff = Normalize(targetAngle - currentAngle, -PI, +PI);
    float dist = Vector2Distance(
        {static_cast<float>(player.x), static_cast<float>(player.y)},
        {static_cast<float>(pos.x), static_cast<float>(pos.y)});

    if (angleDiff > 0) {
      currentAngle += rotationStep;
    } else {
      currentAngle -= rotationStep;
    }

    Enemy->Phy->setAngle(currentAngle);
    // box->setAngularVelocity(0);

    if (abs(angleDiff) > 1)
      continue;

    Enemy->Phy->applyForce({0, -dist * 2});

    if (dist > 200 || Enemy->cooldown > 0.0f)
      continue;

    Enemy->cooldown = 0.25f;
    Bullets::Shoot(Enemy->Phy, space);
  }
}

void Draw() {
  for (Entity *Enemy : list) {
    Enemy->Draw();
  }
}
} // namespace Enemies
