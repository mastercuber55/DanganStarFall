#include "Scenes.hpp"
#include <raylib.h>

SceneBullets::SceneBullets(SceneGame *ptr) {
  Parent = ptr;
  shootSound = LoadSound("Assets/shoot.wav");
}

void SceneBullets::Shoot(Pebble::Obj *obj) {
  cpFloat angle = obj->getAngle();

  float safetyMargin = 2.0f; // extra distance to avoid collision
  cpVect offset = cpv((obj->Size.x / 2 + safetyMargin) * cosf(angle - PI / 2),
                      (obj->Size.x / 2 + safetyMargin) * sinf(angle - PI / 2));

  cpVect pos = cpvadd(obj->getPosition(), offset);

  auto bullet = new Pebble::Obj(Parent->Space, pos, cpVect{1, 1}, 1);

  bullet->setAngle(angle);
  bullet->applyImpulse({0, static_cast<cpFloat>(-pow(2, 9))});
  obj->applyImpulse({0, static_cast<cpFloat>(pow(2, 9))});
  PlaySound(shootSound);

  bullet->setCollisionType((int)CollisionTypes::Bullet);

  list.push_back(bullet);
}

void SceneBullets::Update(float dt) {
  (void)dt;
  for (int i = 0; i < (int)list.size(); i++) {

    auto bullet = list[i];

    if (bullet->Collision) {
      delete bullet;
      list.erase(list.begin() + i);
      continue;
    }

    auto pos = bullet->getPosition();
    float dx = pos.x - Parent->Cam.target.x;
    float dy = pos.y - Parent->Cam.target.y;

    if (dx < -Frax::ScreenSize.x / 2 || dx > Frax::ScreenSize.x / 2 ||
        dy < -Frax::ScreenSize.y / 2 || dy > Frax::ScreenSize.y / 2) {
      delete bullet;
      list.erase(list.begin() + i);
    }
  }
}

void SceneBullets::Draw() {
  for (auto &bullet : list) {
    auto pos = cpBodyGetPosition(bullet->Body);
    DrawCircle(pos.x, pos.y, 2, {0, 225, 0, 225});
  }
}