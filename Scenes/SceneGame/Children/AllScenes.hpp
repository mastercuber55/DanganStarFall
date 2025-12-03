#pragma once
#include "Frax.hpp"
#include <vector>
#include <array>
#include "../Entity.hpp"

struct SceneGame;

namespace Pebble {
    struct Obj;
}

#ifdef PLATFORM_ANDROID
struct SceneAndroid : Frax::Scene {

  SceneGame* Parent;

  Vector2 joyBase;
  Vector2 joyValue;
  Vector2 joyKnob;
  float joyRadius;

  Vector2 BtnA;
  Vector2 BtnB;
  float btnRadius;

  SceneAndroid(SceneGame*);

  void Update(const float &dt) override;
  void Draw() override;

  ~SceneAndroid();
};

#endif

struct SceneAsteroids : Frax::Scene {

  SceneGame *Parent;

  std::vector<Entity *> list;

  void Spawn();

  void Update(const float &dt) override;
  void Draw() override;

  SceneAsteroids(SceneGame *);
};

struct SceneBullets : Frax::Scene {
  SceneGame *Parent;

  std::vector<Pebble::Obj *> list;
  Sound shootSound;

  void Shoot(Pebble::Obj *obj);

  void Update(const float &dt) override;
  void Draw() override;

  SceneBullets(SceneGame *);
};

struct SceneStars : Frax::Scene {
  SceneGame *Parent;
  std::array<Vector2, 1000> list;

  void Update(const float &dt) override;
  void Draw() override;

  SceneStars(SceneGame *);
};

struct SceneEnemies : Frax::Scene {
  SceneGame *Parent;
  std::vector<Entity *> list;
  int FrameKills;

  void Spawn();
  void Update(const float &dt) override;
  void Draw() override;

  SceneEnemies(SceneGame *);
};