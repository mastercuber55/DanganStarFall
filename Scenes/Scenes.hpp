#include <Frax.hpp>
#include <physac.h>
#undef max
#include <raymath.h>
#include <vector>

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
};

struct SceneGame : Frax::Scene {
    Camera2D Cam;
    PhyRect Player;
    std::vector<Vector2> Stars;
    std::vector<Vector2> Asteroids;

    SceneGame();

    void Update() override;
    void Draw() override;
    
    ~SceneGame();
};