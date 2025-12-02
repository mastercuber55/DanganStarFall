#include "../Scenes.hpp"

void SceneGame::Draw() {

  DrawRectangleGradientV(0, 0, Frax::ScreenSize.x, Frax::ScreenSize.y,
                         {19, 16, 25, 255}, {35, 31, 82, 255});
  BeginMode2D(Cam);

  stars->Draw();

  if (Player.Health > 0)
    Player.Draw();

  bullets->Draw();
  enemies->Draw();
  asteroids->Draw();

  // DrawCircleLinesV(Player.GetCenter(), 200, RED);

  EndMode2D();

  DrawFPS(32, 32);
  DrawText(TextFormat("Health %d", (int)Player.Health), 32, 64, 32, WHITE);
  DrawText(TextFormat("Fuel %f", fuel), 32, 32 * 3, 32, WHITE);

  if (Player.Health <= 0) {
    DrawText(TextFormat("You Died.\n Kills: %d", Kills),
             Frax::ScreenSize.x / 2 - 96, Frax::ScreenSize.y / 2 - 64, 48, RED);
             
  }

#ifdef PLATFORM_ANDROID
  Controls->Draw();
#endif
}