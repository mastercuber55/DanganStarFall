#include <Frax.hpp>
#include <cstdlib>
#include <pebble.hpp>
#include <raymath.h>
#include <vector>
// #define PLATFORM_ANDROID
#include "../Classes/Bullet.hpp"

struct SceneGame : Frax::Scene {

#ifdef PLATFORM_ANDROID
  SceneTouchControls Controls;
#endif

  Sound shoot;
  Sound explosion;

  cpSpace *Space;

  Camera2D Cam;
  Frax::Rect Player;
  std::vector<Vector2> Stars;
  std::vector<Bullet> Bullets;

  SceneGame();

  void Update(float dt) override;
  void Draw() override;

  ~SceneGame();
};

#ifdef PLATFORM_ANDROID

struct SceneTouchControls : Frax::Scene {

  Vector2 joyBase;
  Vector2 joyValue;
  Vector2 joyKnob;
  float joyRadius;

  SceneTouchControls();

  void Update(PhyObj &Player, Vector2 Force); // REmoved overide
  void Draw() override;

  ~SceneTouchControls();
};

#endif