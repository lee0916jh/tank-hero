#include "core/tank.h"

namespace tank_hero {
Tank::Tank(const vec2& position) : Movable(position, position, kDefaultSpeed) {}

void Tank::MoveUp() {
  direction_ = vec2(0, -1);
  Move();
}

void Tank::MoveDown() {
  direction_ = vec2(0, 1);
  Move();
}

void Tank::MoveLeft() {
  direction_ = vec2(-1, 0);
  Move();
}

void Tank::MoveRight() {
  direction_ = vec2(1, 0);
  Move();
}

vec2 Tank::GetTopLeftCorner() const {
  return position_ - vec2(kTankWidth / 2, kTankWidth / 2);
}

vec2 Tank::GetBottomRightCorner() const {
  return position_ + vec2(kTankWidth / 2, kTankWidth / 2);
}

}  // namespace tank_hero
