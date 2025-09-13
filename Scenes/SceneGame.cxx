#include "Scenes.hpp"
#include <math.h>

// TODO: MAKE THRUST SPRITE
// I want to have random aah asteroids around the screen

SceneGame::SceneGame() : Player({Frax::ScreenSize.x/2, Frax::ScreenSize.y/2, 32, 32}, "Assets/Chiaki Ship.png") {
    InitPhysics();
    SetPhysicsGravity(0, 0);

    Player.PhyInit(32);

    Cam = {
		.offset = { Frax::ScreenSize.x/2, Frax::ScreenSize.y/2 },
		.target = Player.GetCenter(),
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
    Vector2 force = { speed * cosf(angle), speed * sinf(angle) };
    
    #ifdef PLATFORM_ANDROID
        Controls.Update(Player, force);
    #endif
     
    // Owo, whats this?? basically since we are now using dynamic resolutions so it won't look bad in fullscreen, it would be convinent to allow players to zoom in to get a clear view, while making sure they don't zoom out of default 1 (b/w 0 and 1) in order to get benifits
    Cam.zoom += GetMouseWheelMove() * 1/8; 
    if(Cam.zoom < 1) Cam.zoom = 1;
    if(IsKeyPressed(KEY_Z)) Cam.zoom = 1; 

    // YAY LETS INVENT DANGAN FINALLY
    // if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    //     PhysicsBody body = CreatePhysicsBodyRectangle(Player, 4, 4, 16);
    //     PhysicsAddForce(body, force);
    // }

	if(IsKeyDown(KEY_W))  PhysicsAddForce(Player, force);
    // if(IsKeyDown(KEY_S)) might add reverse thrust later
	if(IsKeyDown(KEY_A)) Player.Rotation -= 5;
	if(IsKeyDown(KEY_D)) Player.Rotation += 5;
    
    RunPhysicsStep();
    Cam.target = Player.GetCenter();

    for (int i = GetPhysicsBodiesCount() - 1; i > 0; i--) {
        auto body = GetPhysicsBody(i);
        float dx = body->position.x - Cam.target.x;
        float dy = body->position.y - Cam.target.y;

        if (
            dx < -Frax::ScreenSize.x/2 ||
            dx >  Frax::ScreenSize.x/2 ||
            dy < -Frax::ScreenSize.y/2 ||
            dy >  Frax::ScreenSize.y/2
        )  DestroyPhysicsBody(body);
    }

    for(Vector2 &star : Stars) {

        // Calculate how far is the star from the Camera's center
        float dx = star.x - Cam.target.x;
        float dy = star.y - Cam.target.y;

        // If the star is away more than half the screen then we add the screen width or height 
        // which results in it being transported in a fixed position but being a star, its irralevent
        // and goes unnoticed in front of the star, that is our player.
        if (dx < -Frax::ScreenSize.x/2)  star.x += Frax::ScreenSize.x;
        if (dx >  Frax::ScreenSize.x/2)  star.x -= Frax::ScreenSize.x;
        if (dy < -Frax::ScreenSize.y/2) star.y += Frax::ScreenSize.y;
        if (dy >  Frax::ScreenSize.y/2) star.y -= Frax::ScreenSize.y;
    }
}

void SceneGame::Draw() {
    
    BeginMode2D(Cam);

        for(Vector2 &star : Stars) {
            DrawPixel(star.x, star.y, WHITE);
        }

        for (int i = GetPhysicsBodiesCount() - 1; i > 0; i--) {
            auto body = GetPhysicsBody(i);
            DrawCircleV(body->position, 2, RED);
        }

        Player.PhyDraw();
    EndMode2D();

    #ifdef PLATFORM_ANDROID
        Controls.Draw();
    #endif
}

SceneGame::~SceneGame() {
    ClosePhysics();
}