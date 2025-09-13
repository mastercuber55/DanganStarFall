#include "Scenes.hpp"

// Did you know that Scenes can overlap and run concurrently???
SceneTouchControls::SceneTouchControls() {
    joyRadius = 64;
    joyBase = { 64 + 32, 480 - 64 - 32 };
    joyKnob = joyBase;
    joyValue = { 0, 0};
}

void SceneTouchControls::Update(PhyRect &Player, Vector2 force) {

    if(GetTouchPointCount() == 1) {
        // Difference between finger and center
        Vector2 diff = Vector2Subtract(GetTouchPosition(0), joyBase);

        // Distance from center
        float len = Vector2Length(diff);

        // Make sure the knob doesn't leave the joystick
        if(len > joyRadius) {
            // Vector2Scale multiplies it by joyRadius
            // Vector2Normalize makes it a unit vector
            // So diff have merely direction.
            diff = Vector2Scale(Vector2Normalize(diff), joyRadius);
        }

        // Since we calculated how far is the touch from the joyBase
        joyKnob = Vector2Add(joyBase, diff);
        // Vector2Scale will make the internal values between -1 and 1
        joyValue = Vector2Scale(diff, 1.0f / joyRadius);
    } else {
        joyKnob = joyBase;
        joyValue = { 0, 0};
    }
    
    if(joyValue.y < 0) {
        PhysicsAddForce(Player.Body, Vector2Scale(force, -joyValue.y));
    }
    if(fabs(joyValue.x) > 0.1f) {
        Player.Rotation += joyValue.x * 5;
    }
}

void SceneTouchControls::Draw() {

    DrawCircleLinesV(joyBase, 64, WHITE);
    DrawCircleV(joyKnob, 32, WHITE);
}

SceneTouchControls::~SceneTouchControls() {
    
}