#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"

namespace tank_hero {
using glm::vec2;

class Tank {
 public:
  Tank(const vec2& position);

 private:
  vec2 position_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
