#include "Scenes.hpp"

SceneGame::SceneGame() : Player({ 0, 0, 32, 32}, "Assets/Chiaki Ship.png") {
    InitPhysics();
    SetPhysicsGravity(0, 0.5f);

    Player.PhyInit(32);

}

void SceneGame::Update() {

    RunPhysicsStep();

    int Speed = 16;

	if(IsKeyDown(KEY_W)) {
        Player.y += -Speed;
        Player.Rotation = 270;
    }
	if(IsKeyDown(KEY_A)) {
        Player.x += -Speed;
        Player.Rotation = 180;
    }
	if(IsKeyDown(KEY_S)) {
        Player.y += +Speed;
        Player.Rotation = 90;
    }
	if(IsKeyDown(KEY_D)) {
        Player.x += +Speed;
        Player.Rotation = 0;
    }
}

void SceneGame::Draw() {
    Player.PhyDraw();
}

SceneGame::~SceneGame() {
    ClosePhysics();
}