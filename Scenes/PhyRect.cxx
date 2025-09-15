#include "Scenes.hpp"
 
PhyObj::PhyObj(Rectangle Destination, Color Tint) : Frax::Rect(Destination, Tint) {
}

PhyObj::PhyObj(										
    Rectangle Destination, 
    std::string TextureFile, 
    Rectangle Source
) : Frax::Rect(Destination, TextureFile, Source) {

}

void PhyObj::RectInit(float density) {

    Body = CreatePhysicsBodyRectangle(this->GetCenter(), this->w, this->h, density);
}

void PhyObj::CircleInit(float density) {
    Body = CreatePhysicsBodyCircle(this->GetCenter(), this->w/2, density);
}

PhyObj::operator PhysicsBody() const {
	return this->Body;
}

void PhyObj::PhyDraw() {
    this->SetCenter(Body->position);
    Rotation = Body->orient * 180/PHYSAC_PI;
    Draw();
}

PhyObj::~PhyObj() {
    DestroyPhysicsBody(Body);
}

Bullet::operator Vector2() const {
	return { this->x, this->y };
}
void Bullet::operator=(Vector2 NewPos) {
	this->x = NewPos.x;
	this->y = NewPos.y;
}