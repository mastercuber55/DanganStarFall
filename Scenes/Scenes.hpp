#include <Frax.hpp>
#include <physac.h>

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
    PhyRect Player;

    SceneGame();

    void Update() override;
    void Draw() override;
    
    ~SceneGame();
};