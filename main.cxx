#define FRAX_IMPL
#define PHYSAC_IMPLEMENTATION
#define RAYMATH_IMPLEMENTATION
#include "Scenes/Scenes.hpp" // Includes the above's respective libraries

int main () {
    Frax::Init(640, 480, "DanganStarFall");

    SceneGame().Run();

    Frax::Close();
}
