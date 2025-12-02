#include "../Scenes.hpp"

void SceneGame::Update(const float &dt) {

  this->UpdatePlayer(dt);

  // Updating physics simulation.
  cpSpaceStep(Space, dt);

  // Random spawns
  if (GetRandomValue(0, 100) < 10 * dt) {
    asteroids->Spawn();
    enemies->Spawn();
  }

  cpVect playerPos = Player.Phy->getPosition();

  // Recentering the world if needed.
  if (fabs(playerPos.x) > 5000 || fabs(playerPos.y) > 5000) {
    this->RecenterWorld(playerPos);
  }

  Cam.target = {(float)playerPos.x, (float)playerPos.y};

  // Telling child scenes to update.
  stars->Update(dt);
  bullets->Update(dt);
  asteroids->Update(dt);
  if (Player.Health > 0) {
    enemies->Update(dt);
    Kills += enemies->FrameKills;
  }
}