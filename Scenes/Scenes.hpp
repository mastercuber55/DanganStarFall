#include "../Systems/index.hpp"

#ifdef PLATFORM_ANDROID

struct SceneTouchControls : Frax::Scene {

  Vector2 joyBase;
  Vector2 joyValue;
  Vector2 joyKnob;
  float joyRadius;

  Vector2 BtnA;
  Vector2 BtnB;
  float btnRadius;

  SceneTouchControls();

  void Update(Entity* Player, float thrust, float dt, cpSpace* Space, Sound* shootSound);
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

  int Kills = 0;

  cpSpace *Space;

  Camera2D Cam;
  Entity Player;

  SceneGame();

  void Update(float dt) override;
  void Draw() override;

  ~SceneGame();
};