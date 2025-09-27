#include "../Systems/main.hpp"

enum class CollisionType : cpCollisionType {
  None, Player, Bullet, Asteroid
};

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

  cpSpace *Space;

  Camera2D Cam;
  Frax::Rect Player;
  Pebble::Obj* playerObj;

  SceneGame();

  void Update(float dt) override;
  void Draw() override;

  ~SceneGame();
};