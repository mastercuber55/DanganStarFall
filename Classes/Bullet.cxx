#include "Bullet.hpp"

Bullet::operator Vector2() const { return {this->x, this->y}; }
void Bullet::operator=(Vector2 NewPos) {
  this->x = NewPos.x;
  this->y = NewPos.y;
}