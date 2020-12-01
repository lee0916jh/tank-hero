#include <cstddef>
#include <vector>

#include "game.h"

namespace tank_hero {
using std::vector;

template <typename EnemyType>
void Game::HandleTankEnemiesCollisions(vector<EnemyType>* enemies) {
  if (enemies->empty()) return;
  if (dynamic_cast<Enemy*>(&enemies->at(0)) == nullptr) {
    throw std::invalid_argument("Elements are not of Enemy type.");
  }
  for (size_t i = 0; i < enemies->size(); i++) {
    if (tank_.DidCollideWith(enemies->at(i))) {
      tank_.DecrementLife();
      enemies->erase(enemies->begin() + i);
      return;
    }
  }
}
}  // namespace tank_hero