#include "Scenes.hpp"
#include <raymath.h>

// Did you know that Scenes can overlap and run concurrently???
#ifdef PLATFORM_ANDROID
SceneTouchControls::SceneTouchControls() {
  joyRadius = 64 * 3;
  joyBase = {static_cast<float>(joyRadius * 1.5), Frax::ScreenSize.y - joyRadius * 2};
  joyKnob = joyBase;
  joyValue = {0, 0};

  btnRadius = 128;
  BtnA = { Frax::ScreenSize.x - 512 - 64, Frax::ScreenSize.y - 128 - btnRadius};
  BtnB = { Frax::ScreenSize.x - 256, Frax::ScreenSize.y - 128 - btnRadius};
}

void SceneTouchControls::Update(Entity* Player, float thrust, float dt, cpSpace* Space, Sound* shootSound) {
    int touchCount = GetTouchPointCount();
    bool joystickActive = false;
    bool buttonActive = false;

    for (int i = 0; i < touchCount; i++) {
        Vector2 touch = GetTouchPosition(i);

        // 👈 Left half: joystick
        if (touch.x < GetScreenWidth() / 2) {
            joystickActive = true;
            Vector2 diff = Vector2Subtract(touch, joyBase);
            float len = Vector2Length(diff);

            if (len > joyRadius)
                diff = Vector2Scale(Vector2Normalize(diff), joyRadius);

            joyKnob = Vector2Add(joyBase, diff);
            joyValue = Vector2Scale(diff, 1.0f / joyRadius);

            // instantly face joystick direction
            if (len > 5.0f) {
                float angle = atan2f(diff.y, diff.x) + PI / 2;
                Player->Phy->setAngle(angle);
            }
        }

        // 👉 Right half: buttons
        else {
            buttonActive = true;

            if (CheckCollisionPointCircle(touch, BtnA, btnRadius)) {
                Player->Phy->applyForce({0, -thrust});
            }
            else if (CheckCollisionPointCircle(touch, BtnB, btnRadius) && Player->cooldown <= 0) {
                Player->cooldown = 0.25f;
                Bullets::Shoot(Player->Phy, Space);
                PlaySound(*shootSound);
            }
        }
    }

    // reset joystick if no touch in left half
    if (!joystickActive) {
        joyKnob = joyBase;
        joyValue = {0, 0};
    }
}

void SceneTouchControls::Draw() {

  DrawCircleLinesV(joyBase, joyRadius, WHITE);
  DrawCircleV(joyKnob, joyRadius / 2, WHITE);

  DrawCircleLinesV(BtnA, btnRadius, WHITE);
  DrawCircleLinesV(BtnB, btnRadius, WHITE);
}

SceneTouchControls::~SceneTouchControls() {}
#endif