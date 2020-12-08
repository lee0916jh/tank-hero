#include <cstddef>
#include <vector>

#include "game.h"

namespace tank_hero {
using std::vector;

template <typename T>
void Game::HandleTankCollisionWith(vector<T>* dangerous_objects) {
  if (dangerous_objects->empty()) return;
  bool is_enemy = dynamic_cast<Enemy*>(&dangerous_objects->at(0)) != nullptr;
  bool is_bullet = dynamic_cast<Bullet*>(&dangerous_objects->at(0)) != nullptr;
  if (!is_bullet && !is_enemy) {
    throw std::invalid_argument(
        "The vector does not contain any dangerous object that can do harm to "
        "the tank");
  }

  for (size_t i = 0; i < dangerous_objects->size(); i++) {
    if (tank_.DidCollideWith(dangerous_objects->at(i))) {
      tank_.LoseLifeOrShield();
      dangerous_objects->erase(dangerous_objects->begin() + i);
      return;
    }
  }
}
}  // namespace tank_hero