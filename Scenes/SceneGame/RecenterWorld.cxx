#include "SceneGame.hpp"

void SceneGame::RecenterWorld(cpVect& playerPos) {
    cpSpaceEachBody(
        Space,
        [](cpBody *body, void *data) {
          cpVect shift = *(cpVect *)data;
          cpBodySetPosition(body, cpvsub(cpBodyGetPosition(body), shift));
        },
        &playerPos);

    Cam.target.x -= playerPos.x;
    Cam.target.y -= playerPos.y;

    for (auto &star : stars->list) {
      star.x -= playerPos.x;
      star.y -= playerPos.y;
    }

    // Update playerPos after shift
    playerPos = Player.Phy->getPosition();
}