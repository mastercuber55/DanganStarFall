#include "Scenes.hpp"

SceneGame::SceneGame() : Player({300, 200, 32, 32}, "Assets/Chiaki Ship.png") {
    InitPhysics();
    SetPhysicsGravity(0, 0);

    Player.PhyInit(32);

}

void SceneGame::Update() {

    RunPhysicsStep();

    float Force = 50;

	if(IsKeyDown(KEY_W)) {
        PhysicsAddForce(Player.Body, {0, -Force});
        Player.Rotation = 270;
    }
	if(IsKeyDown(KEY_A)) {
        PhysicsAddForce(Player.Body, {-Force, 0});
        Player.Rotation = 180;
    }
	if(IsKeyDown(KEY_S)) {
        PhysicsAddForce(Player.Body, {0, Force});
        Player.Rotation = 90;
    }
	if(IsKeyDown(KEY_D)) {
        PhysicsAddForce(Player.Body, {Force, 0});
        Player.Rotation = 0;
    }
}

void SceneGame::Draw() {
    Player.PhyDraw();
}

SceneGame::~SceneGame() {
    ClosePhysics();
}