#include "SceneGame.hpp"
#include "CollisionTypes.hpp"

cpBool bulletSomethingBegin(cpArbiter *arb, cpSpace *space, void *data) {

  (void)space;
  (void)data;
  
  cpShape *sBullet;
  cpShape *sSomething;

  cpArbiterGetShapes(arb, &sBullet, &sSomething);

  auto Bullet = static_cast<Pebble::Obj *>(cpShapeGetUserData(sBullet));
  auto Something = static_cast<Pebble::Obj *>(cpShapeGetUserData(sSomething));

  Bullet->Collision = true;
  Something->Collision = true;

  return cpFalse;
}

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