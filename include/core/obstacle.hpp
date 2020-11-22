#include "obstacle.h"

namespace tank_hero {
template <typename MovableType>
void Obstacle::HandleCollisionWith(vector<MovableType>* movables) const {
  if(movables->empty()) return;
  if(dynamic_cast<Movable*>(&movables->at(0)) == nullptr){
    throw std::invalid_argument("Elements are not of Movable type.");
  }
  for (MovableType& movable : *movables) {
    HandleCollisionWith(static_cast<Movable*>(&movable));
  }
}
}  // namespace tank_hero
