#include "index.hpp"
#include <raylib.h>

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

void Maintain(Sound *explosion) {
  for (int i = 0; i < (int)list.size(); i++) {
    auto &enemy = list[i];
    auto box = std::any_cast<Pebble::Obj *>(enemy->Data);

    if (box->ShouldDelete) {
      delete enemy;
      delete box;
      list.erase(list.begin() + i);
      --i;
      PlaySound(*explosion);
    }
  }
}

void Draw() {
  for (const auto &enemy : list) {
    Pebble::Draw(enemy);
  }
}
} // namespace Enemies
