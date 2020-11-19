#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"
#include "core/movable.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankWidth = 30;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultBulletDelay = .5f;

struct BulletConfig {
  float size = kDefaultBulletSize;
  float speed = kDefaultBulletSpeed;
  float delay = kDefaultBulletDelay;
};

class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters
  vec2 GetTopLeftCorner() const;
  vec2 GetBottomRightCorner() const;
  const BulletConfig& GetBulletConfig() const { return bullet_config_; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  void KeepInMap(const size_t field_width);

 private:
  BulletConfig bullet_config_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
