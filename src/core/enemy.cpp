#include "core/enemy.h"

namespace tank_hero {

Enemy::Enemy(const vec2& position, float speed, Tank* target)
    : Movable(position, position, speed, kEnemyRadius), target_(target) {}

void Enemy::Move() {
  vec2 direction = glm::normalize(target_->GetPosition() - position_);
  position_ += speed_ * direction;
}
}  // namespace tank_hero