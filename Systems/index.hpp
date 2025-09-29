// #define ENABLE_FRAX_DEBUG
#include <Frax.hpp>
#include <chipmunk/chipmunk_types.h>
#include <discord_rpc.h>
#include <pebble.hpp>
#include <raylib.h>
#include <vector>

enum class CollisionTypes : cpCollisionType { None, Player, Bullet, Asteroid };

namespace Asteroids {
extern std::vector<std::unique_ptr<Frax::Rect>> list;
void Spawn(Camera2D, cpSpace *);
void Maintain(Sound *);
void Draw();
} // namespace Asteroids

namespace Bullets {
extern std::vector<Pebble::Obj *> list;
void Shoot(Pebble::Obj *playerObj, cpSpace *space);
void Maintain(Camera2D &);
void Draw();
} // namespace Bullets

namespace Stars {
extern std::vector<Vector2> list;
void Init(Camera2D &);
void Maintain(Camera2D &);
void Draw();
} // namespace Stars

namespace Discord {
extern DiscordRichPresence rpc;
void Init();
void Update(const std::string& details, const std::string& state);
void Close();
} // namespace Discord

cpBool bulletAsteroidBegin(cpArbiter *, cpSpace *, void *data);