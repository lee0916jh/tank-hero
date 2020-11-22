#include "core/enemy.h"

namespace tank_hero {

Enemy::Enemy(const vec2& position, float speed, const vec2* target)
    : Movable(position, position, speed, kEnemyRadius), target_(target) {}

void Enemy::Move() {
  direction_ = glm::normalize(*target_ - position_);
  Movable::Move();
}
}  // namespace tank_hero