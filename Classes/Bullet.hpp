#include <raylib.h>

struct Bullet : Vector2 {
  float Radian;
  void operator=(Vector2 NewPos);
  operator Vector2() const;
};