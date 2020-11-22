#include <cstddef>
#include <vector>

#include "game.h"

namespace tank_hero {
using std::vector;

template <typename EnemyType>
void Game::HandleTankEnemiesCollisions(vector<EnemyType>* enemies) {
  for (size_t i = 0; i < enemies->size(); i++) {
    if (tank_.DidCollideWith(enemies->at(i))) {
      tank_.DecrementLife();
      enemies->erase(enemies->begin() + i);
      return;
    }
  }
}
}  // namespace tank_hero