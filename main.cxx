#define FRAX_IMPL
#define PEBBLE_IMPL
#include "Scenes/Scenes.hpp" // Includes the above's respective libraries

int main() {
  Frax::Init("DanganStarFall");
  
  SceneGame().Run();

  Frax::Close();

  return 0;
}