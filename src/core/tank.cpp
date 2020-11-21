#include "core/tank.h"

namespace tank_hero {
Tank::Tank(const vec2& position)
    : Movable(position, position, kDefaultSpeed, kTankSize / 2) {}

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

void Tank::MoveUpLeft() {
  direction_ = glm::normalize(vec2(-1, -1));
  Move();
}

void Tank::MoveUpRight() {
  direction_ = glm::normalize(vec2(1, -1));
  Move();
}

void Tank::MoveDownLeft() {
  direction_ = glm::normalize(vec2(-1, 1));
  Move();
}

void Tank::MoveDownRight() {
  direction_ = glm::normalize(vec2(1, 1));
  Move();
}

void Tank::RotateGun(const vec2& direction) {
  gun_rotation_ = direction - position_;
}

void Tank::KeepInMap(const size_t field_width) {
  if (position_.x < collider_radius_) position_.x = collider_radius_;
  if (position_.y < collider_radius_) position_.y = collider_radius_;
  if (position_.x > field_width - collider_radius_) {
    position_.x = field_width - collider_radius_;
  }
  if (position_.y > field_width - collider_radius_) {
    position_.y = field_width - collider_radius_;
  }
}

bool Tank::DidCollideWith(const Enemy& enemy) const {
  return glm::distance2(position_, enemy.GetPosition()) <
         powf(kTankSize + enemy.GetColliderRadius(), 2);
}

void Tank::ReduceReloadTime(float reduce_amount) {
  bullet_config_.reload_time -= reduce_amount;
}

}  // namespace tank_hero
