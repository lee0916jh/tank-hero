#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr float kDefaultBulletSize = 5;
constexpr size_t kDefaultTankWidth = 30;

class Tank {
 public:
  explicit Tank(const vec2& position);

  // Getters
  const vec2& GetPosition() const { return position_; }
  vec2 GetTopLeftCorner() const;
  vec2 GetBottomRightCorner() const;
  float GetBulletSize() const { return bullet_size_; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

 private:
  vec2 position_;
  float speed_;
  float bullet_size_ = kDefaultBulletSize;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
