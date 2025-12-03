#include "SceneGame.hpp"
#include "raygui.h"

SceneGame::SceneGame() : Player({0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

  Space = cpSpaceNew();

  GuiSetStyle(PROGRESSBAR, PROGRESS_PADDING, 0);

  this->InitPlayerAndCam();

  explosion = LoadSound("Assets/explosion.wav");

  asteroids = std::make_unique<SceneAsteroids>(this);
  bullets = std::make_unique<SceneBullets>(this);
  stars = std::make_unique<SceneStars>(this);
  enemies = std::make_unique<SceneEnemies>(this);

#ifdef PLATFORM_ANDROID
  Controls = std::make_unique<SceneAndroid>(this);
#endif

  this->InitColliders();

  discord::RPCManager::get()
    .getPresence()
      .setDetails("A Danganronpa Fan Game <3")
      .setState("BEING EXECUTED HAHAHA")
      .refresh();
}

SceneGame::~SceneGame() {}