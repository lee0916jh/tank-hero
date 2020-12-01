#include "bullet.h"
#include "enemy.h"

namespace tank_hero {

template <typename EnemyType>
typename vector<EnemyType>::iterator Bullet::GetKilledEnemy(
    vector<EnemyType>* enemies) {
  if (enemies->empty()) return enemies->end();
  if (dynamic_cast<Enemy*>(&enemies->at(0)) == nullptr) {
    throw std::invalid_argument("vector element is not of Enemy type.");
  }
  auto enemy_it = enemies->begin();
  while (enemy_it != enemies->end()) {
    if (this->DidHit(*enemy_it)) {
      this->GoInactive();
      return enemy_it;
    }
    enemy_it++;
  }
  return enemies->end();
}
}  // namespace tank_hero