// #define ENABLE_FRAX_DEBUG
#include <Frax.hpp>
#include <chipmunk/chipmunk_types.h>
#include <discord_rpc.h>
#include <pebble.hpp>
#include <raylib.h>
#include <vector>

enum class CollisionTypes : cpCollisionType { None, Player, Bullet, Asteroid, Enemy };

struct Entity : Frax::Rect {
  float Health = 100;
  float cooldown = 0;
  Pebble::Obj *Phy;
  void Draw();

  using Rect::Rect;
};

namespace Asteroids {
void Spawn(Camera2D, cpSpace *);
void Maintain(Sound *);
void Draw();
} // namespace Asteroids

namespace Bullets {
void Shoot(Pebble::Obj *playerObj, cpSpace *space);
void Maintain(Camera2D &);
void Draw();
} // namespace Bullets

namespace Stars {
void Init(Camera2D &);
void Maintain(Camera2D &);
void Draw();
} // namespace Stars

namespace Enemies {
void Spawn(Camera2D &, cpSpace *);
void Maintain(Sound*, cpVect player, cpSpace*, float dt);
void Draw();
}

namespace Discord {
extern DiscordRichPresence rpc;
void Init();
void Update(const std::string& details, const std::string& state);
void Close();
} // namespace Discord

cpBool bulletSomethingBegin(cpArbiter *, cpSpace *, void *data);