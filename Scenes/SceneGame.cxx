#include "Scenes.hpp"

SceneGame::SceneGame() : Player({ 0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

}

void SceneGame::Update() {

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
    Player.Draw();
}

SceneGame::~SceneGame() {

}