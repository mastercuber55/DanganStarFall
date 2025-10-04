#include "Scenes.hpp"
#include <raymath.h>

// Did you know that Scenes can overlap and run concurrently???
#ifdef PLATFORM_ANDROID
SceneTouchControls::SceneTouchControls() {
  joyRadius = 128;
  joyBase = {static_cast<float>(joyRadius * 1.5), Frax::ScreenSize.y - joyRadius * 2};
  joyKnob = joyBase;
  joyValue = {0, 0};
}

void SceneTouchControls::Update(Pebble::Obj* playerObj, float force, float dt) {

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    // Difference between finger and center

    Vector2 diff;
    if (GetTouchPointCount() != 0) {
      diff = Vector2Subtract(GetTouchPosition(0), joyBase);
    } else {
      diff = Vector2Subtract(GetMousePosition(), joyBase);
    }

    // Distance from center
    float len = Vector2Length(diff);

    // Make sure the knob doesn't leave the joystick
    if (len > joyRadius) {
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
    joyValue = {0, 0};
  }

  if (joyValue.y < 0) {
    playerObj->applyForce({force * -joyValue.y});
  }
  if (fabs(joyValue.x) > 0.1f) {
    float angle = playerObj->getAngle();
    float angleDelta = joyValue.x * 10 * dt;
    playerObj->setAngle(angle + angleDelta);
  }
}

void SceneTouchControls::Draw() {

  DrawCircleLinesV(joyBase, joyRadius, WHITE);
  DrawCircleV(joyKnob, joyRadius / 2, WHITE);
}

SceneTouchControls::~SceneTouchControls() {}
#endif