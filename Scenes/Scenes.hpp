#include "../Systems/index.hpp"
#include <memory>
#include "discord-rpc.hpp"

struct SceneAsteroids;
struct SceneBullets;
struct SceneStars;
struct SceneEnemies;
struct SceneAndroid;

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
  std::vector<Vector2> list;

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