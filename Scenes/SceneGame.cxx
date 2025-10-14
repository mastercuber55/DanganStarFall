#include "Scenes.hpp"
#include <cstdio>
#include <memory>
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

SceneGame::SceneGame() : Player({0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

  Space = cpSpaceNew();

  Player.Phy = new Pebble::Obj(Space, {0, 0}, {32, 32}, 16);
  Player.Phy->setCollisionType((int)CollisionTypes::Player);
  Player.cooldown = 0.0f;
  Player.Health = 100;

  Cam = {.offset = {Frax::ScreenSize.x / 2, Frax::ScreenSize.y / 2},
         .target = Player,
         .rotation = 0.0f,
         .zoom = 1.0f};
  
  explosion = LoadSound("Assets/explosion.wav");

  asteroids = std::make_unique<SceneAsteroids>(this);
  bullets = std::make_unique<SceneBullets>(this);
  stars = std::make_unique<SceneStars>(this);
  enemies = std::make_unique<SceneEnemies>(this);

  #ifdef PLATFORM_ANDROID
    Controls = std::make_unique<SceneAndroid>(this);
  #endif

  auto handlerBulletAsteroid = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Asteroid);
  handlerBulletAsteroid->beginFunc = bulletSomethingBegin;

  auto handlerBulletEnemy = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Enemy);
  handlerBulletEnemy->beginFunc = bulletSomethingBegin;

  auto handlerBulletPlayer = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Player);
  handlerBulletPlayer->beginFunc = bulletSomethingBegin;

  Discord::Update("A Danganronpa Fan Game <3", "BEING EXECUTED HAHAHA");
}

void SceneGame::Update(float dt) {

  // Preparing variables
  float angle = Player.Phy->getAngle();
  float thrust = pow(2, 19) * dt;

  // Handling Inputs

  if (Player.Health > 0) {
#ifdef PLATFORM_ANDROID
    Controls->Update(dt);
#else
    // Zoom handling.
    Cam.zoom += GetMouseWheelMove() *
                (IsKeyDown(KEY_LEFT_CONTROL) ? 1.0f / 2 : 1.0f / 8);
    if (Cam.zoom < 1)
      Cam.zoom = 1;
    if (IsKeyPressed(KEY_Z))
      Cam.zoom = 1;

    // Dangan
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && Player.cooldown <= 0 &&
        GetTouchPointCount() == 0) {
      Player.cooldown = 0.25f;
      bullets->Shoot(Player.Phy);
    }

    // useful while testing.
    if (IsKeyPressed(KEY_X))
      Player.Phy->setVelocity(cpvzero);

    if (IsKeyDown(KEY_W))
      Player.Phy->applyForce({0, -thrust});

    Vector2 Mouse = GetScreenToWorld2D(GetMousePosition(), Cam);
    cpVect playerPos = Player.Phy->getPosition();
    angle = atan2(Mouse.y - playerPos.y, Mouse.x - playerPos.x) + PI / 2;
    Player.Phy->setAngle(angle);
#endif
    if (Player.Phy->Collision) {
      Player.Health--;
      if (Player.Health == 0)
        PlaySound(explosion);
      Player.Phy->Collision = false;
    }

    if (Player.cooldown > 0.0f)
      Player.cooldown -= dt;
    Cam.target = Player.GetCenter();
    Player.Phy->setAngularVelocity(0);

    bullets->Update(dt);
    stars->Update(dt);
    asteroids->Update(dt);
    enemies->Update(dt);
    Kills += enemies->FrameKills;
  }

  cpSpaceStep(Space, dt);

  if (GetRandomValue(0, 100) < 10 * dt) {
    asteroids->Spawn();
    enemies->Spawn();
  }

  Discord::Callbacks();
}

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

  if (Player.Health <= 0) {
    DrawText(TextFormat("You Died.\n Kills: %d", Kills),
             Frax::ScreenSize.x / 2 - 96, Frax::ScreenSize.y / 2 - 64, 48, RED);
  }

#ifdef PLATFORM_ANDROID
  Controls->Draw();
#endif
}

SceneGame::~SceneGame() {}