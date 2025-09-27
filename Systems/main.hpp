#include <Frax.hpp>
#include <pebble.hpp>
#include <raylib.h>
#include <vector>

namespace Asteroids {
extern std::vector<std::unique_ptr<Frax::Rect>> list;
void Spawn(Camera2D , cpSpace *);
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