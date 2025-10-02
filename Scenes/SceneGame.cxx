#include "Scenes.hpp"
#include <chipmunk/cpPolyShape.h>
#include <chipmunk/cpSpace.h>
#include <cstdio>
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

SceneGame::SceneGame() : Player({0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

  Space = cpSpaceNew();

  Player.Phy = new Pebble::Obj(Space, {4, 4}, {32, 32}, 16);
  Player.Phy->setCollisionType((int)CollisionTypes::Player);
  Player.cooldown = 0.0f;
  Player.Health = 100;

  Cam = {.offset = {Frax::ScreenSize.x / 2, Frax::ScreenSize.y / 2},
         .target = Player,
         .rotation = 0.0f,
         .zoom = 1.0f};

  shootSound = LoadSound("Assets/shoot.wav");
  explosion = LoadSound("Assets/explosion.wav");

  Stars::Init(Cam);
  Asteroids::Spawn(Cam, Space);

  auto handlerBulletAsteroid = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Asteroid);
  handlerBulletAsteroid->beginFunc = bulletSomethingBegin;

  // auto handlerBulletEnemy = cpSpaceAddCollisionHandler(
  //     Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Enemy);
  // handlerBulletEnemy->beginFunc = bulletSomethingBegin;

  auto handlerBulletPlayer = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Player);
  handlerBulletPlayer->beginFunc = bulletSomethingBegin;

  Discord::Update("A Danganronpa Fan Game <3", "BEING EXECUTED HAHAHA");
}

void SceneGame::Update(float dt) {

  // Preparing variables
  float angle = Player.Phy->getAngle();
  float thrust = pow(2, 19) * dt;

#ifdef PLATFORM_ANDROID
  Controls.Update(Player.Phy, thrust, dt);
#endif

  // Handling Inputs

  // Zoom handling.
  Cam.zoom +=
      GetMouseWheelMove() * (IsKeyDown(KEY_LEFT_CONTROL) ? 1.0f / 2 : 1.0f / 8);
  if (Cam.zoom < 1)
    Cam.zoom = 1;
  if (IsKeyPressed(KEY_Z))
    Cam.zoom = 1;

  // Dangan
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && Player.cooldown <= 0) {
    Player.cooldown = 0.25f;
    Bullets::Shoot(Player.Phy, Space);
    PlaySound(shootSound);
  }

  // useful while testing.
  if (IsKeyPressed(KEY_X))
    Player.Phy->setVelocity(cpvzero);

  if (IsKeyDown(KEY_W))
    Player.Phy->applyForce({0, -thrust});

  Vector2 Mouse = GetScreenToWorld2D(GetMousePosition(), Cam);
  cpVect playerPos = Player.Phy->getPosition();
  angle = atan2(Mouse.y - playerPos.y, Mouse.x - playerPos.x) + PI / 2;

  if (Player.Phy->ShouldDelete) {
    Player.Health--;
    Player.Phy->ShouldDelete = false;
  }

  if (Player.cooldown > 0.0f)
    Player.cooldown -= dt;
  Cam.target = Player.GetCenter();
  Player.Phy->setAngle(angle);
  Player.Phy->setAngularVelocity(0);
  cpSpaceStep(Space, dt);

  Bullets::Maintain(Cam);
  Stars::Maintain(Cam);
  Asteroids::Maintain(&explosion);
  Enemies::Maintain(&explosion, Player.Phy->getPosition(), Space, dt);

  if (GetRandomValue(0, 100) < 10 * dt) {
    Asteroids::Spawn(Cam, Space);
    Enemies::Spawn(Cam, Space);
  }

  Discord_RunCallbacks();
}

void SceneGame::Draw() {

  DrawRectangleGradientV(0, 0, Frax::ScreenSize.x, Frax::ScreenSize.y,
                         {19, 16, 25, 255}, {35, 31, 82, 255});
  BeginMode2D(Cam);

  Stars::Draw();

  Player.Draw();

  Bullets::Draw();
  Asteroids::Draw();
  Enemies::Draw();

  // DrawCircleLinesV(Player.GetCenter(), 200, RED);
  auto pos = Player.Phy->getPosition();
  DrawRectangleLines(pos.x - 16, pos.y - 16, 32, 32, RED);

  EndMode2D();

  DrawFPS(32, 32);
  DrawText(TextFormat("Health %f", Player.Health), 32, 64, 32, WHITE);

#ifdef PLATFORM_ANDROID
  Controls.Draw();
#endif
}

SceneGame::~SceneGame() {}