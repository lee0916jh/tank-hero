#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 1;

class Tank {
 public:
  explicit Tank(const vec2& position);

  // Getters
  const vec2& GetPosition() { return position_; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

 private:
  vec2 position_;
  float speed_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
