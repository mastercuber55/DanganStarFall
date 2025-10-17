#include "Scenes.hpp"

SceneStars::SceneStars(SceneGame *ptr) {
  Parent = ptr;
  for (int i = 0; i < 1000; i++) {
    list.push_back(Frax::GetRandomPositionInside(ptr->Cam));
  }
}

void SceneStars::Update(float dt) {
  (void)dt;
  for (Vector2 &star : list) {

    float dx = star.x - Parent->Cam.target.x;
    float dy = star.y - Parent->Cam.target.y;

    if (dx < -Frax::ScreenSize.x / 2)
      star.x += Frax::ScreenSize.x;
    else if (dx > Frax::ScreenSize.x / 2)
      star.x -= Frax::ScreenSize.x;
    if (dy < -Frax::ScreenSize.y / 2)
      star.y += Frax::ScreenSize.y;
    else if (dy > Frax::ScreenSize.y / 2)
      star.y -= Frax::ScreenSize.y;
  }
}

void SceneStars::Draw() {
  for (auto &star : list) {
    DrawCircle(star.x, star.y, 1, WHITE);
  }
}