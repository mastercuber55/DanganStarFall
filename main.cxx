#define FRAX_IMPL
#define PHYSAC_IMPLEMENTATION

#include "Scenes/Scenes.hpp" // Includes Frax and Physac

int main () {
    Frax::Init(640, 480, "DanganStarFall");

    SceneGame().Run();

    Frax::Close();
}
