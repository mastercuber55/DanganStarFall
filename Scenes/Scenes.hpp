#include <Frax.hpp>
// #define PHYSAC_NO_THREADS // this fixed the crashses
#include <physac.h>
#include <cstdlib>
#undef max
#include <raymath.h>
#include <vector> // Required for stars and asteroids
// #define PLATFORM_ANDROID

struct PhyObj : Frax::Rect {
    PhysicsBody Body;

    void RectInit(float density);
    void CircleInit(float density);

    void PhyDraw();

	PhyObj(Rectangle Destination, Color Tint);	
	PhyObj(										
		Rectangle Destination, 
		std::string TextureFile, 
		Rectangle Source = { 0, 0, -1, -1 }
	);
	~PhyObj();

    operator PhysicsBody() const;
};

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

struct Bullet : Vector2 {
    float Radian;
    void operator=(Vector2 NewPos);
    operator Vector2() const;
};

struct SceneGame : Frax::Scene {

    #ifdef PLATFORM_ANDROID
        SceneTouchControls Controls;
    #endif
     
    Sound shoot;

    Camera2D Cam;
    PhyObj Player;
    std::vector<Vector2> Stars;
    std::vector<Bullet> Bullets;
    std::vector<PhyObj> Asteroids;

    SceneGame();

    void Update() override;
    void Draw() override;
    
    ~SceneGame();
};