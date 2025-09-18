#include <Frax.hpp>
#include <cstdlib>
#undef max
#include <raymath.h>
#include <vector> // Required for stars and asteroids
// #define PLATFORM_ANDROID
#include <raymunk++.hpp>
#include "../Classes/Bullet.hpp"

#ifdef PLATFORM_ANDROID

struct SceneTouchControls : Frax::Scene {

    Vector2 joyBase;
    Vector2 joyValue;
    Vector2 joyKnob;
    float joyRadius;

    SceneTouchControls();

    void Update(PhyObj & Player, Vector2 Force); // REmoved overide
    void Draw() override;
    
    ~SceneTouchControls();
};

#endif

struct SceneGame : Frax::Scene {

    #ifdef PLATFORM_ANDROID
        SceneTouchControls Controls;
    #endif
     
    cpSpace* space;

    Sound shoot;
    Sound explosion;

    Camera2D Cam;
    PhyObj Player;
    std::vector<Vector2> Stars;
    std::vector<Bullet> Bullets;

    SceneGame();

    void Update(float dt) override;
    void Draw() override;
    
    ~SceneGame();
};