#include "bullet.h"

namespace tank_hero {
template <typename EnemyType>
bool Bullet::TryAndKillEnemy(vector<EnemyType>* enemies) {
  if (enemies->empty()) return false;
  if (dynamic_cast<Enemy*>(&enemies->at(0)) == nullptr) {
    throw std::invalid_argument("Elements are not of Enemy type.");
  }

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