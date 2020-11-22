#include "core/ranged_enemy.h"
namespace tank_hero {
RangedEnemy::RangedEnemy(const vec2 &position, float speed, const vec2 *target)
    : Enemy(position, speed, target),
      Ranged(kEnemyBulletSize, kEnemyBulletSpeed, kEnemyReloadTime) {}
}  // namespace tank_hero