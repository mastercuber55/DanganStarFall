#include "Scenes.hpp"

/*
PhyRect(Rectangle Destination, Color Tint);	
	PhyRect(										
		Rectangle Destination, 
		std::string TextureFile, 
		Rectangle Source = { 0, 0, -1, -1 }
	);
	~PhyRect();
*/

PhyRect::PhyRect(Rectangle Destination, Color Tint) : Frax::Rect(Destination, Tint) {

}

PhyRect::PhyRect(										
    Rectangle Destination, 
    std::string TextureFile, 
    Rectangle Source
) : Frax::Rect(Destination, TextureFile, Source) {

}

void PhyRect::PhyInit(float density) {
    Body = CreatePhysicsBodyRectangle({ x, y }, w, h, density);
}

void PhyRect::PhyDraw() {
    x = Body->position.x;
    y = Body->position.y;

    Draw();
}

PhyRect::~PhyRect() {
    DestroyPhysicsBody(Body);
}