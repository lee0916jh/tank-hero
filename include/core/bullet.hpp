#include "bullet.h"

namespace tank_hero {
template <typename EnemyType>
bool Bullet::TryAndKillEnemy(vector<EnemyType>* enemies) {
  for (EnemyType& enemy : *enemies) {
    if (this->DidHit(enemy)) {
      enemy.Die();
      GoInactive();
      return true;
    }
  }
  return false;
}
}  // namespace tank_hero