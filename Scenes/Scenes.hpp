#include <Frax.hpp>
#define PHYSAC_NO_THREADS // this fixed the crashses
#include <physac.h>
#include <cstdlib>
#undef max
#include <raymath.h>
#include <vector> // Required for stars and asteroids
// #define PLATFORM_ANDROID

struct PhyRect : Frax::Rect {
    PhysicsBody Body;

    void PhyInit(float density);
    void PhyDraw();

	PhyRect(Rectangle Destination, Color Tint);	
	PhyRect(										
		Rectangle Destination, 
		std::string TextureFile, 
		Rectangle Source = { 0, 0, -1, -1 }
	);
	~PhyRect();

    operator PhysicsBody() const;
};

#ifdef PLATFORM_ANDROID

struct SceneTouchControls : Frax::Scene {

    Vector2 joyBase;
    Vector2 joyValue;
    Vector2 joyKnob;
    float joyRadius;

    SceneTouchControls();

    void Update(PhyRect & Player, Vector2 Force); // REmoved overide
    void Draw() override;
    
    ~SceneTouchControls();
};

#endif

struct SceneGame : Frax::Scene {

    #ifdef PLATFORM_ANDROID
        SceneTouchControls Controls;
    #endif
     
    Camera2D Cam;
    PhyRect Player;
    std::vector<Vector2> Stars;
    std::vector<PhysicsBody> Bullets;

    SceneGame();

    void Update() override;
    void Draw() override;
    
    ~SceneGame();
};