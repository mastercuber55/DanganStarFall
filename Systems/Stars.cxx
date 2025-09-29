#include "index.hpp"
#include <raylib.h>

namespace Stars {
std::vector<Vector2> list;
void Init(Camera2D &cam) {
  for (int i = 0; i < 1000; i++) {
    list.push_back(Frax::GetRandomPositionInside(cam));
  }
}
void Maintain(Camera2D &cam) {
  for (Vector2 &star : list) {

    float dx = star.x - cam.target.x;
    float dy = star.y - cam.target.y;

    if (dx < -Frax::ScreenSize.x / 2)
      star.x += Frax::ScreenSize.x;
    if (dx > Frax::ScreenSize.x / 2)
      star.x -= Frax::ScreenSize.x;
    if (dy < -Frax::ScreenSize.y / 2)
      star.y += Frax::ScreenSize.y;
    if (dy > Frax::ScreenSize.y / 2)
      star.y -= Frax::ScreenSize.y;
  }
}
void Draw() {

  int rand = GetRandomValue(0, 1);
  Color clr = WHITE;

  if (rand == 0)
    clr = {225, 247, 0, 255};

  for (auto &star : list) {
    DrawCircle(star.x, star.y, 1, clr);
  }
}
} // namespace Stars