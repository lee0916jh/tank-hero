#ifndef TANK_HERO_MOVABLE_H
#define TANK_HERO_MOVABLE_H
#include "cinder/gl/gl.h"

namespace tank_hero {
using glm::vec2;

class Movable {
 public:
  Movable(const vec2& position, const vec2& direction = vec2(0, 0),
          float speed = 0.0f, size_t size = 1);
  Movable(const Movable& source) = default;
  Movable& operator=(const Movable& source) = default;
  Movable(Movable&& source) = default;
  Movable& operator=(Movable&& source) = default;
  virtual ~Movable() = default;

  // Getters
  const vec2& GetPosition() const { return position_; }
  size_t GetSize() const { return size_; }

  /// Move this object 1 unit of time
  virtual void Move();

 protected:
  vec2 position_;
  vec2 direction_;
  float speed_;
  size_t size_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_MOVABLE_H
