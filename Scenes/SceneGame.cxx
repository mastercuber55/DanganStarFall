#include "Scenes.hpp"
#include <cstdio>
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

  shootSound = LoadSound("Assets/shoot.wav");
  explosion = LoadSound("Assets/explosion.wav");

  Stars::Init(Cam);
  Asteroids::Spawn(Cam, Space);

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
  Controls.Update(&Player, thrust, dt, Space, &shootSound);
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
    Player.Phy->setAngle(angle);
#endif
    if (Player.Phy->Collision) {
      Player.Health--;
      if(Player.Health == 0) PlaySound(explosion);
      Player.Phy->Collision = false;
    }

    if (Player.cooldown > 0.0f)
      Player.cooldown -= dt;
    Cam.target = Player.GetCenter();
    Player.Phy->setAngularVelocity(0);

    Bullets::Maintain(Cam);
    Stars::Maintain(Cam);
    Asteroids::Maintain(&explosion);
    Kills +=
        Enemies::Maintain(&explosion, Player.Phy->getPosition(), Space, dt);
  }

  cpSpaceStep(Space, dt);

  if (GetRandomValue(0, 100) < 10 * dt) {
    Asteroids::Spawn(Cam, Space);
    Enemies::Spawn(Cam, Space);
  }

  Discord::Callbacks();
}

void SceneGame::Draw() {

  DrawRectangleGradientV(0, 0, Frax::ScreenSize.x, Frax::ScreenSize.y,
                         {19, 16, 25, 255}, {35, 31, 82, 255});
  BeginMode2D(Cam);

  Stars::Draw();

  if (Player.Health > 0)
    Player.Draw();

  Bullets::Draw();
  Enemies::Draw();

  Asteroids::Draw();

  // DrawCircleLinesV(Player.GetCenter(), 200, RED);

  EndMode2D();

  DrawFPS(32, 32);
  DrawText(TextFormat("Health %d", (int)Player.Health), 32, 64, 32, WHITE);

  if (Player.Health <= 0) {
    DrawText(TextFormat("You Died.\n Kills: %d", Kills),
             Frax::ScreenSize.x / 2 - 96, Frax::ScreenSize.y / 2 - 64, 48,
             RED);
  }

#ifdef PLATFORM_ANDROID
  Controls.Draw();
#endif
}

SceneGame::~SceneGame() {}