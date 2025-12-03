#include <memory>
#include <discord-rpc.hpp>
#include "Entity.hpp"
#include "Children/AllScenes.hpp"

struct SceneGame : Frax::Scene {

#ifdef PLATFORM_ANDROID
  std::unique_ptr<SceneAndroid> Controls;
#endif

  // Complex Child Scenes
  // Using unique_ptr because they can only have one parent scene.
  std::unique_ptr<SceneAsteroids> asteroids;
  std::unique_ptr<SceneBullets> bullets;
  std::unique_ptr<SceneStars> stars;
  std::unique_ptr<SceneEnemies> enemies;

  Sound shootSound;
  Sound explosion;

  int Kills = 0;
  float fuel = 100.0;

  cpSpace *Space;

  Camera2D Cam;
  Entity Player;

  SceneGame();

  void Update(const float &dt) override;
  void Draw() override;

  void InitColliders();
  
  void InitPlayerAndCam();
  void UpdatePlayer(const float &dt);

  void RecenterWorld(cpVect& playerPos);

  ~SceneGame();
};