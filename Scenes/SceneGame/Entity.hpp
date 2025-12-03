#pragma once
#include "Frax.hpp"
#include "pebble.hpp"

struct Entity : Frax::Rect {
  float Health = 100;
  float cooldown = 0;
  Pebble::Obj *Phy;
  void Draw();
  void DrawHitbox();

  using Rect::Rect;
  ~Entity();
};