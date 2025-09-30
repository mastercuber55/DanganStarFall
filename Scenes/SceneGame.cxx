#include "Scenes.hpp"
#include <chipmunk/cpSpace.h>
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>

SceneGame::SceneGame() : Player({0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

  Space = cpSpaceNew();

  playerObj = new Pebble::Obj(Space, {4, 4}, {32, 32}, 16);
  Player.Data = playerObj;
  playerObj->setCollisionType((int)CollisionTypes::Player);

  Cam = {.offset = {Frax::ScreenSize.x / 2, Frax::ScreenSize.y / 2},
         .target = Player,
         .rotation = 0.0f,
         .zoom = 1.0f};

  shootSound = LoadSound("Assets/shoot.wav");
  explosion = LoadSound("Assets/explosion.wav");

  Stars::Init(Cam);
  Asteroids::Spawn(Cam, Space);

  auto handlerBulletAsteroid = cpSpaceAddCollisionHandler(Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Asteroid);
  handlerBulletAsteroid->beginFunc = bulletAsteroidBegin;

  auto handlerBulletEnemy = cpSpaceAddCollisionHandler(
      Space, (int)CollisionTypes::Bullet, (int)CollisionTypes::Enemy);
  handlerBulletEnemy->beginFunc = bulletEnemyBegin;

  Discord::Update("A Danganronpa Fan Game <3", "BEING EXECUTED HAHAHA");
}

void SceneGame::Update(float dt) {

  // Preparing variables
  float angle = playerObj->getAngle();
  float thrust = pow(2, 19) * dt;
  float angularSpeed = 8 * dt;

#ifdef PLATFORM_ANDROID
  Controls.Update(playerObj, thrust, dt);
#endif

  // Handling Inputs
  // Owo, whats this?? basically since we are now using dynamic resolutions so
  // it won't look bad in fullscreen, it would be convinent to allow players to
  // zoom in to get a clear view, while making sure they don't zoom out of
  // default 1 (b/w 0 and 1) in order to get benifits
  Cam.zoom +=
      GetMouseWheelMove() * (IsKeyDown(KEY_LEFT_CONTROL) ? 1.0f / 2 : 1.0f / 8);
  if (Cam.zoom < 1)
    Cam.zoom = 1;
  if (IsKeyPressed(KEY_Z))
    Cam.zoom = 1;

  // Dangan
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Bullets::Shoot(playerObj, Space);
    PlaySound(shootSound);
  }

  // useful while testing.
  if (IsKeyPressed(KEY_X))
    playerObj->setVelocity(cpvzero);

  if (IsKeyDown(KEY_W))
    playerObj->applyForce({thrust, 0});
  if (IsKeyDown(KEY_S))
    playerObj->applyForce({-thrust, 0});
  if (IsKeyDown(KEY_A))
    playerObj->setAngle(angle - angularSpeed);
  if (IsKeyDown(KEY_D))
    playerObj->setAngle(angle + angularSpeed);

  Cam.target = Player.GetCenter();
  playerObj->setAngularVelocity(0);
  cpSpaceStep(Space, dt);

  Bullets::Maintain(Cam);
  Stars::Maintain(Cam);
  Asteroids::Maintain(&explosion);
  Enemies::Maintain(&explosion);

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

  Pebble::Draw(&Player);

  Bullets::Draw();
  Asteroids::Draw();
  Enemies::Draw();

  EndMode2D();

  DrawText(TextFormat("Co-ordinates: (%d, %d)", (int)Player.x, (int)Player.y),
           64, 64, 32, WHITE);

  int dist = Vector2Length(Player); // distance from origin
  DrawText(TextFormat("Distance: %d", dist), 64, 128, 32, WHITE);

#ifdef PLATFORM_ANDROID
  Controls.Draw();
#endif
}

SceneGame::~SceneGame() {}