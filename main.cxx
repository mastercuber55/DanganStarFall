#define FRAX_IMPL
#include <Frax.hpp>
#include "Scenes/Scenes.hpp"

int main () {
    Frax::Init(640, 480, "DanganStarFall");

    SceneGame().Run();

    Frax::Close();
}
