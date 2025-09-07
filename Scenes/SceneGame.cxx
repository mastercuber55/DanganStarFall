#include "Scenes.hpp"
#include <math.h>

// TODO: MAKE THRUST SPRITE
// I want to have random aah asteroids around the screen

SceneGame::SceneGame() : Player({320, 240, 32, 32}, "Assets/Chiaki Ship.png") {
    InitPhysics();
    SetPhysicsGravity(0, 0);

    Player.PhyInit(32);

    Cam = {
		.offset = { 320, 240 },
		.target = Player,
		.rotation = 0.0f,
		.zoom = 1.0f
	};

    for(int i  = 0; i < 1000; i++) {
        Stars.push_back(Frax::GetRandomPosition(Cam));
    }
}

void SceneGame::Update() {

    float speed = 50;
    float angle = DEG2RAD * Player.Rotation;
    Vector2 force = { speed * cosf(angle), speed * sinf(angle) }; // f for float

    Controls.Update(Player, force);
    
	if(IsKeyDown(KEY_W)) {
        PhysicsAddForce(Player.Body, force);
    }
    if(IsKeyDown(KEY_S)) {
        // Might add reverse thrust later
    }
	if(IsKeyDown(KEY_A)) {
        Player.Rotation -= 5;
    }
	if(IsKeyDown(KEY_D)) {
        Player.Rotation += 5;
    }
    
    RunPhysicsStep();
    Cam.target = Player;

    // Vector2 screenToWorld = GetScreenToWorld2D({0,0}, Cam);
    // Vector2 screenToWorld2 = Vector2Add(screenToWorld, {640, 480})
    // This was so stupid of me

    for(Vector2 &star : Stars) {

        // Calculate how far is the star from the Camera's center
        float dx = star.x - Cam.target.x;
        float dy = star.y - Cam.target.y;

        // If the star is away more than half the screen then we add the screen width or height 
        // which results in it being transported in a fixed position but being a star, its irralevent
        // and goes unnoticed in front of the star, that is our player.
        if (dx < -320)  star.x += 640;
        if (dx >  320)  star.x -= 640;
        if (dy < -240) star.y += 480;
        if (dy >  240) star.y -= 480;
    }
}

void SceneGame::Draw() {
    
    BeginMode2D(Cam);

        for(Vector2 star : Stars) {
            DrawPixel(star.x, star.y, WHITE);
        }

        Player.PhyDraw();
    EndMode2D();

    Controls.Draw();
}

SceneGame::~SceneGame() {
    ClosePhysics();
}