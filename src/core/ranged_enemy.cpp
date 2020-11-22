#include "core/ranged_enemy.h"
namespace tank_hero {
RangedEnemy::RangedEnemy(const vec2 &position, float speed, const vec2 *target)
    : Enemy(position, speed, target),
      Ranged(kEnemyBulletSize, kEnemyBulletSpeed, kEnemyReloadTime) {}

void RangedEnemy::Move() {
  if (glm::distance2(*target_, position_) > powf(kRangedEnemyMinDistance, 2)) {
    Enemy::Move();
  }
}
}  // namespace tank_hero