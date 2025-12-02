#include "Scenes.hpp"
#include <chipmunk/chipmunk_types.h>
#include <raylib.h>

SceneBullets::SceneBullets(SceneGame *ptr) {
  Parent = ptr;
  shootSound = LoadSound("Assets/shoot.wav");
}

void SceneBullets::Shoot(Pebble::Obj *shooter) {
  cpFloat angle = shooter->getAngle();

  float safetyMargin = 2.0f; // extra distance to avoid collision.
  cpVect offset =
      cpv((shooter->Size.x / 2 + safetyMargin) * cosf(angle - PI / 2),
          (shooter->Size.x / 2 + safetyMargin) * sinf(angle - PI / 2));

  cpVect pos = cpvadd(shooter->getPosition(), offset);

  auto bullet = new Pebble::Obj(Parent->Space, pos, cpVect{1, 1}, 1);

  bullet->setAngle(angle);

  cpVect bulletVel = cpv(0, static_cast<cpFloat>(-pow(2, 9)));

  // Rotate in the angle of the shooter.
  bulletVel = cpvrotate(bulletVel, cpv(cosf(angle), sinf(angle)));

  // Make it relative to the shooter.
  bulletVel = cpvadd(bulletVel, shooter->getVelocity());

  bullet->setVelocity(bulletVel);

  shooter->applyImpulse({0, static_cast<cpFloat>(pow(2, 9))});
  // PlaySound(shootSound); so annoying aaa

  bullet->setCollisionType((int)CollisionTypes::Bullet);

  list.push_back(bullet);
}

void SceneBullets::Update(const float &dt) {
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