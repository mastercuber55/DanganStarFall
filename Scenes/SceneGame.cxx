#include "Scenes.hpp"
#include <math.h>

SceneGame::SceneGame() : Player({0, 0, 32, 32}, "Assets/Chiaki Ship.png") {

    InitPhysics();
    SetPhysicsGravity(0, 0);

    Player.RectInit(32);
    Player.Body->freezeOrient = true;

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
    float angle = Player.Body->orient;
    Vector2 dir = { cosf(angle), sinf(angle) }; // Unit Vector
    Vector2 force = Vector2Scale(dir, speed);
    
    #ifdef PLATFORM_ANDROID
        Controls.Update(Player, force);
    #endif
     
    // Owo, whats this?? basically since we are now using dynamic resolutions so it won't look bad in fullscreen, it would be convinent to allow players to zoom in to get a clear view, while making sure they don't zoom out of default 1 (b/w 0 and 1) in order to get benifits
    Cam.zoom += GetMouseWheelMove() * 1/8; 
    if(Cam.zoom < 1) Cam.zoom = 1;
    if(IsKeyPressed(KEY_Z)) Cam.zoom = 1; 

    // Dangan
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 pos = Vector2Add(Player.GetCenter(), Vector2Scale(dir, 32));
        PhysicsBody body = CreatePhysicsBodyRectangle(pos, 1, 1, 128);
        Bullets.push_back(body);
        PhysicsAddForce(body, force);
        PhysicsAddForce(Player, Vector2Scale(force, -4));
    }

    if(IsKeyPressed(KEY_X)) Player.Body->velocity = { 0, 0 }; // Useful for me while testing.
	if(IsKeyDown(KEY_W))  PhysicsAddForce(Player, force);
    // if(IsKeyDown(KEY_S)) might add reverse thrust later
	if(IsKeyDown(KEY_A)) Player.Body->orient -= 0.1;
	if(IsKeyDown(KEY_D)) Player.Body->orient += 0.1;

    RunPhysicsStep();
    Cam.target = Player;

    // Physics bodies outside of the screen die.                         
    for (int i = GetPhysicsBodiesCount() - 1; i > 0; i--) {
        auto body = GetPhysicsBody(i);
        float dx = body->position.x - Cam.target.x;
        float dy = body->position.y - Cam.target.y;

        if (
            dx < -Frax::ScreenSize.x/2 ||
            dx >  Frax::ScreenSize.x/2 ||
            dy < -Frax::ScreenSize.y/2 ||
            dy >  Frax::ScreenSize.y/2
        )  {
            DestroyPhysicsBody(body); 
        }
    }

    for(Vector2 &star : Stars) {

        float dx = star.x - Cam.target.x;
        float dy = star.y - Cam.target.y;

        if (dx < -Frax::ScreenSize.x/2)  star.x += Frax::ScreenSize.x;
        if (dx >  Frax::ScreenSize.x/2)  star.x -= Frax::ScreenSize.x;
        if (dy < -Frax::ScreenSize.y/2) star.y += Frax::ScreenSize.y;
        if (dy >  Frax::ScreenSize.y/2) star.y -= Frax::ScreenSize.y;
    }
}

void SceneGame::Draw() {
    
    BeginMode2D(Cam);

        for(auto &star : Stars) {
            DrawPixel(star.x, star.y, WHITE);
        }

        Player.PhyDraw();
 
        for(auto body : Bullets) {
            DrawCircleV(body->position, 2, RED);
        }

        
    EndMode2D();

    DrawText(TextFormat("Co-ordinates: (%d, %d)", (int)Player.x, (int)Player.y), 64, 64, 32, WHITE);
    
    float dist = Vector2Length(Player); // distance from origin
    DrawText(TextFormat("Distance: %d", int(dist)), 64, 128, 32, WHITE);

    #ifdef PLATFORM_ANDROID
        Controls.Draw();
    #endif
}

SceneGame::~SceneGame() {
    ClosePhysics();
}