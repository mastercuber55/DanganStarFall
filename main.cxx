#define FRAX_IMPL
#define RAYMATH_IMPLEMENTATION
#define RAYMUNK_IMPL
#include "Scenes/Scenes.hpp" // Includes the above's respective libraries

int main () {
    Frax::Init("DanganStarFall");

    SceneGame().Run();

    Frax::Close();
}