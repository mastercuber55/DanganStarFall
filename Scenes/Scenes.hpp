#include <Frax.hpp>

struct SceneGame : Frax::Scene {
    Frax::Rect Player;

    SceneGame();

    void Update() override;
    void Draw() override;
    
    ~SceneGame();
};