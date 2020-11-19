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

void Tank::KeepInMap(const size_t field_width) {
  if (position_.x < kTankWidth / 2) position_.x = kTankWidth / 2;
  if (position_.y < kTankWidth / 2) position_.y = kTankWidth / 2;
  if (position_.x > field_width - kTankWidth / 2)
    position_.x = field_width - kTankWidth / 2;
  if (position_.y > field_width - kTankWidth / 2)
    position_.y = field_width - kTankWidth / 2;
}

bool Tank::DidCollideWith(const Enemy& enemy) const {
  return glm::distance2(position_, enemy.GetPosition()) <
         powf(kTankWidth + enemy.GetRadius(), 2);
}

}  // namespace tank_hero
