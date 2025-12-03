#include "chipmunk/chipmunk_types.h"

enum class CollisionTypes : cpCollisionType {
  None,
  Player,
  Bullet,
  Asteroid,
  Enemy
};