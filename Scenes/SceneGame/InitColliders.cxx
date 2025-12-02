#include "../Scenes.hpp"

void SceneGame::InitColliders() {
    int targets[] = { 
        (int)CollisionTypes::Asteroid, 
        (int)CollisionTypes::Enemy, 
        (int)CollisionTypes::Player 
    };

    for (int target : targets) {
        auto handler = cpSpaceAddCollisionHandler(Space, (int)CollisionTypes::Bullet, target);
        handler->beginFunc = bulletSomethingBegin;
    }
}