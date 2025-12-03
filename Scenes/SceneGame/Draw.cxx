#include "SceneGame.hpp"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

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

  const Rectangle ProgBar = {48, 24, 24 * 8, 24};

  GuiProgressBar(ProgBar, "Health", "", &Player.Health, 0.0f, 100.0f);
  GuiProgressBar({ProgBar.x, ProgBar.y * 2.5f, ProgBar.width, ProgBar.height},
                 "Fuel", "", &fuel, 0.0f, 100.0f);

  if (Player.Health <= 0) {
    DrawText(TextFormat("You Died.\n Kills: %d", Kills),
             Frax::ScreenSize.x / 2 - 96, Frax::ScreenSize.y / 2 - 64, 48, RED);
  }

#ifdef PLATFORM_ANDROID
  Controls->Draw();
#endif
}