#include "index.hpp"

namespace Bullets {
std::vector<Pebble::Obj *> list;

void Shoot(Pebble::Obj* obj, cpSpace *space) {
  cpVect pos = obj->getPosition();
  auto bullet = new Pebble::Obj(space, pos, cpVect{1, 1}, 1);
  bullet->setAngle(obj->getAngle());
  bullet->applyImpulse({0, -pow(2, 9)});
  obj->applyImpulse({0, pow(2, 9)});

  bullet->setCollisionType((int)CollisionTypes::Bullet);

  list.push_back(bullet);
}
void Maintain(Camera2D &Cam) {

  for (int i = 0; i < (int)list.size(); i++) {

    auto bullet = list[i];

    if (bullet->ShouldDelete) {
      delete bullet;
      list.erase(list.begin() + i);
      continue;
    }
    
    auto pos = bullet->getPosition();
    float dx = pos.x - Cam.target.x;
    float dy = pos.y - Cam.target.y;

    if (dx < -Frax::ScreenSize.x / 2 || dx > Frax::ScreenSize.x / 2 ||
        dy < -Frax::ScreenSize.y / 2 || dy > Frax::ScreenSize.y / 2) {
      delete bullet;
      list.erase(list.begin() + i);
    }
  }
}

void Draw() {
  for (auto &bullet : list) {
    auto pos = cpBodyGetPosition(bullet->Body);
    DrawCircle(pos.x, pos.y, 2, { 0, 225, 0, 225 });
  }
}
} // namespace list