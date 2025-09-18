#include "Scenes.hpp"
#include <math.h>

// TODO: ADD ASTEROIDS
// TODO: MAKE SOUND MANAGER

SceneGame::SceneGame() {

    space = cpSpaceNew();

    Player.Init(space, { 0, 0, 32, 32 }, 16);

    Cam = {
		.offset = { Frax::ScreenSize.x/2, Frax::ScreenSize.y/2 },
		.target = Player,
		.rotation = 0.0f,
		.zoom = 1.0f
	};

    for(int i  = 0; i < 1000; i++) {
        Stars.push_back(Frax::GetRandomPosition(Cam));
    }

    shoot = LoadSound("Assets/shoot.wav");
    explosion = LoadSound("Assets/explosion.wav");

    // auto asteroid = new PhyObj({128, 128, 64, 64}, "Assets/Asteroid.png");
    // Asteroids.push_back(asteroid);
    // Asteroids.back()->CircleInit(128);

}

void SceneGame::Update(float dt) {

    // Preparing variables
    float speed = 1420;
    float angle = Player.GetAngle();
    // Vector2 dir = { cosf(angle), sinf(angle) }; // Unit Vector
    // Vector2 force = Vector2Scale(dir, speed);
    
    #ifdef PLATFORM_ANDROID
        Controls.Update(Player, force);
    #endif
    
    // Handling Inputs
    // Owo, whats this?? basically since we are now using dynamic resolutions so it won't look bad in fullscreen, it would be convinent to allow players to zoom in to get a clear view, while making sure they don't zoom out of default 1 (b/w 0 and 1) in order to get benifits
    Cam.zoom += GetMouseWheelMove() * (IsKeyDown(KEY_LEFT_CONTROL) ? 1.0f/2 : 1.0f/8); 
    if(Cam.zoom < 1) Cam.zoom = 1;
    if(IsKeyPressed(KEY_Z)) Cam.zoom = 1; 

    // Dangan
    // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     Vector2 pos = Player.GetCenter();
    //     Bullets.push_back({pos.x, pos.y, Player.Body->orient});
    //     // PhysicsAddForce(Player, Vector2Scale(force, -4));
    //     PlaySound(shoot);
    // }

    // if(IsKeyPressed(KEY_X)) Player.Body->velocity = { 0, 0 }; // Useful for me while testing.
	if(IsKeyDown(KEY_W))  Player.ApplyForce({0, -10000});
    // // if(IsKeyDown(KEY_S)) might add reverse thrust later
	if(IsKeyDown(KEY_A)) angle -= speed * dt;
	if(IsKeyDown(KEY_D)) angle += speed * dt;
    Player.SetAngle(angle);

    // Handling events.
    cpSpaceStep(space, dt);
    Cam.target = Player;

    // Physics bodies outside of the screen die.                         
    for (int i = 0; i < (int)Bullets.size(); i++) {
        Bullet &bullet = Bullets[i];
        float dx = bullet.x - Cam.target.x;
        float dy = bullet.y - Cam.target.y;

        if (
            dx < -Frax::ScreenSize.x/2 ||
            dx >  Frax::ScreenSize.x/2 ||
            dy < -Frax::ScreenSize.y/2 ||
            dy >  Frax::ScreenSize.y/2
        )  {
            Bullets.erase(Bullets.begin() + i); 
        } else {
            bullet = Vector2Add(bullet, Vector2Scale({ cosf(bullet.Radian), sinf(bullet.Radian) }, 8));
            // for (auto j = 0; j < Asteroids.size(); j++) {
            //     if(CheckCollisionPointCircle(bullet, Asteroids[j]->GetCenter(), Asteroids[i]->w / 2)) {
            //         Bullets.erase(Bullets.begin() + i);
            //         Asteroids.erase(Asteroids.begin() + j);
            //         PlaySound(explosion);
            //     }
            // }
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

    // if(GetRandomValue(0, 100)/100.0f < 0.001) {
    //     Vector2 pos = Frax::GetRandomPosition(Cam);
    //     auto asteroid = new PhyObj({pos.x, pos.y, 64, 64}, "Assets/Asteroid.png");
    //     Asteroids.push_back(asteroid);
    //     Asteroids.back()->CircleInit(128);
    // }
}

void SceneGame::Draw() {
    
    BeginMode2D(Cam);

        for(auto &star : Stars) {
            DrawPixel(star.x, star.y, WHITE);
        }

        Player.Draw();

        for(auto &bullet : Bullets) {
            DrawCircleV(bullet, 2, RED);
        }

        // for(auto asteroid : Asteroids) {
        //     asteroid->PhyDraw();
        // }

        
    EndMode2D();

    // DrawText(TextFormat("Co-ordinates: (%d, %d)", (int)Player.x, (int)Player.y), 64, 64, 32, WHITE);
    
    // float dist = Vector2Length(Player); // distance from origin
    // DrawText(TextFormat("Distance: %d", int(dist)), 64, 128, 32, WHITE);

    #ifdef PLATFORM_ANDROID
        Controls.Draw();
    #endif
}

SceneGame::~SceneGame() {
    cpSpaceFree(space);
}