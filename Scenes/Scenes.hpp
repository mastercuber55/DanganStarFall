#include "../Systems/index.hpp"
#include <memory>

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

  void Update(Entity *Player, float thrust, float dt, cpSpace *Space,
              Sound *shootSound);
  void Draw() override;

  ~SceneTouchControls();
};

#endif

struct SceneAsteroids;
struct SceneBullets;
struct SceneStars;
struct SceneEnemies;

struct SceneGame : Frax::Scene {

#ifdef PLATFORM_ANDROID
  SceneTouchControls Controls;
#endif

  // Complex Child Scenes
  std::unique_ptr<SceneAsteroids> asteroids;
  std::unique_ptr<SceneBullets> bullets;
  std::unique_ptr<SceneStars> stars;
  std::unique_ptr<SceneEnemies> enemies;

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

struct SceneAsteroids : Frax::Scene {

  SceneGame *Parent;

  std::vector<Entity *> list;

  void Spawn();

  void Update(float dt) override;
  void Draw() override;

  SceneAsteroids(SceneGame *);
};

struct SceneBullets : Frax::Scene {
  SceneGame *Parent;

  std::vector<Pebble::Obj *> list;
  Sound shootSound;

  void Shoot(Pebble::Obj *obj);

  void Update(float dt) override;
  void Draw() override;

  SceneBullets(SceneGame *);
};

struct SceneStars : Frax::Scene {
  SceneGame *Parent;
  std::vector<Vector2> list;

  void Update(float dt) override;
  void Draw() override;

  SceneStars(SceneGame *);
};

struct SceneEnemies : Frax::Scene {
  SceneGame *Parent;
  std::vector<Entity *> list;
  int FrameKills;

  void Spawn();
  void Update(float dt) override;
  void Draw() override;

  SceneEnemies(SceneGame *);
};