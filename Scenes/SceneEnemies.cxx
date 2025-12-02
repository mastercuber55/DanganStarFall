#include "Scenes.hpp"
#include <raymath.h>

SceneEnemies::SceneEnemies(SceneGame *ptr) { Parent = ptr; }

void SceneEnemies::Spawn() {
  Vector2 pos = Frax::GetRandomPositionOutside(Parent->Cam);

  Entity *Enemy =
      new Entity(Rectangle{pos.x, pos.y, 64, 64}, "Assets/Monokuma.png");

  Enemy->Health = 5;

  Enemy->Phy = new Pebble::Obj(Parent->Space, {pos.x, pos.y}, {32, 32}, 32);
  Enemy->Phy->setCollisionType((int)CollisionTypes::Enemy);

  list.push_back(Enemy);
}

void SceneEnemies::Update(const float &dt) {

  FrameKills = 0;

  for (int i = 0; i < (int)list.size(); i++) {
    auto &Enemy = list[i];

    if (Enemy->Phy->Collision) {
      Enemy->Phy->Collision = false;
      Enemy->Health--;
      Enemy->Tint = {255, 255, 255,
                     static_cast<unsigned char>(22.5f * 2.0f * Enemy->Health)};
      if (Enemy->Health <= 0) {
        FrameKills++;
        delete Enemy;
        list.erase(list.begin() + i);
        --i;
        PlaySound(Parent->explosion);
      }
    }

    if (Enemy->cooldown > 0.0f)
      Enemy->cooldown -= dt;

    auto pos = Enemy->Phy->getPosition();
    float currentAngle = Enemy->Phy->getAngle();
    float targetAngle =
        atan2(Parent->Player.y - pos.y, Parent->Player.x - pos.x) - PI / 2;
    float rotationStep = 0.05;
    float angleDiff = Normalize(targetAngle - currentAngle, -PI, +PI);
    float dist = Vector2Distance({(Parent->Player.x), (Parent->Player.y)}, {static_cast<float>((pos.x)), static_cast<float>((pos.y))});

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
    Parent->bullets->Shoot(Enemy->Phy);
  }
}

void SceneEnemies::Draw() {
  for (Entity *Enemy : list) {
    Enemy->Draw();
  }
}
