#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"
#include "core/movable.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankWidth = 30;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8.0f;

struct BulletConfig {
  float size = kDefaultBulletSize;
  float speed = kDefaultBulletSpeed;
};

class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters
  vec2 GetTopLeftCorner() const;
  vec2 GetBottomRightCorner() const;
  float GetBulletSize() const { return bullet_config_.size; }
  float GetBulletSpeed() const { return bullet_config_.speed; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

 private:
  BulletConfig bullet_config_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
