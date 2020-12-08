#include "core/ranged_enemy.h"
namespace tank_hero {
RangedEnemy::RangedEnemy(const vec2 &position, float speed, const vec2 *target)
    : Enemy(position, speed, target),
      Ranged(kEnemyBulletSize, kEnemyBulletSpeed, kEnemyReloadTime) {}

void RangedEnemy::Move() {
  direction_ = glm::normalize(*target_ - position_);
  if (glm::distance2(*target_, position_) > powf(kRangedEnemyMinDistance, 2)) {
    Movable::Move();
  }
}

Bullet RangedEnemy::FireBullet() {
  ResetReloadTimer();
  return Bullet(position_, direction_, bullet_config_);
}
}  // namespace tank_hero