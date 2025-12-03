#include "SceneGame.hpp"
#include "CollisionTypes.hpp"

void SceneGame::InitPlayerAndCam() {
  Player.Phy = new Pebble::Obj(Space, {0, 0}, {32, 32}, 16);
  Player.Phy->setCollisionType((int)CollisionTypes::Player);
  Player.cooldown = 0.0f;
  Player.Health = 100;

  Cam = {.offset = {Frax::ScreenSize.x / 2, Frax::ScreenSize.y / 2},
         .target = Player,
         .rotation = 0.0f,
         .zoom = 1.0f};
}

void SceneGame::UpdatePlayer(const float &dt) {

  if (Player.Health == 0)
    return;

#ifdef PLATFORM_ANDROID
  Controls->Update(dt);
#else
  // Zoom
  Cam.zoom +=
      GetMouseWheelMove() * (IsKeyDown(KEY_LEFT_CONTROL) ? 0.5f : 0.125f);
  Cam.zoom = std::max(Cam.zoom, 1.0f);
  if (IsKeyPressed(KEY_Z))
    Cam.zoom = 1.0f;

  // Shooting
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && Player.cooldown <= 0 &&
      GetTouchPointCount() == 0) {
    Player.cooldown = 0.25f;
    bullets->Shoot(Player.Phy);
  }

  // Debug / testing
  if (IsKeyPressed(KEY_X))
    Player.Phy->setVelocity(cpvzero);

  if (IsKeyDown(KEY_W) && fuel > 0) {
    Player.Phy->applyForce({0, -pow(2, 19) * dt});
    fuel -= 0.5 * dt;
    fuel = std::max(fuel, 0.0f);
  }

  // Aim player towards cursor
  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), Cam);
  cpVect playerPos = Player.Phy->getPosition();
  float angle =
      atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x) + PI / 2;
  Player.Phy->setAngle(angle);
#endif

  // Collision / health
  if (Player.Phy->Collision) {
    Player.Health--;
    if (Player.Health == 0)
      PlaySound(explosion);
    Player.Phy->Collision = false;
  }

  if (Player.cooldown > 0)
    Player.cooldown -= dt;
  Player.Phy->setAngularVelocity(0);
}