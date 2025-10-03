#include "../Systems/index.hpp"

#ifdef PLATFORM_ANDROID

struct SceneTouchControls : Frax::Scene {

  Vector2 joyBase;
  Vector2 joyValue;
  Vector2 joyKnob;
  float joyRadius;

  SceneTouchControls();

  void Update(Pebble::Obj* Player, float Force, float dt);
  void Draw() override;

  ~SceneTouchControls();
};

#endif

struct SceneGame : Frax::Scene {

#ifdef PLATFORM_ANDROID
  SceneTouchControls Controls;
#endif

  Sound shootSound;
  Sound explosion;

  int Kills;

  cpSpace *Space;

  Camera2D Cam;
  Entity Player;

  SceneGame();

  void Update(float dt) override;
  void Draw() override;
  bool ShouldClose() override;

  ~SceneGame();
};