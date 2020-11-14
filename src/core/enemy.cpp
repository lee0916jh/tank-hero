#include "core/enemy.h"

namespace tank_hero {

Enemy::Enemy(const vec2& position, float speed, Tank* target)
    : position_(position), speed_(speed), target_(target) {}

void Enemy::ApproachTank() {
  vec2 direction = glm::normalize(target_->GetPosition() - position_);
  position_ += speed_ * direction;
}
}  // namespace tank_hero