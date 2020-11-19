#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"
#include "core/movable.h"
#include "enemy.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankWidth = 30;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultBulletDelay = .5f;
constexpr unsigned kDefaultLife = 3;

struct BulletConfig {
  float size = kDefaultBulletSize;
  float speed = kDefaultBulletSpeed;
  float delay = kDefaultBulletDelay;
};

class Enemy;
class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters
  vec2 GetTopLeftCorner() const;
  vec2 GetBottomRightCorner() const;
  const BulletConfig& GetBulletConfig() const { return bullet_config_; }
  bool IsAlive() const { return life_ > 0; }
  void DecrementLife() { life_--; }
  size_t GetLifeCount() const { return life_; };

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  /// Puts the tank back into the map if it went outside the map.
  /// \param field_width Size of the map
  void KeepInMap(const size_t field_width);

  /// Returns true only if this tank and the enemy collided with each other.
  /// \param enemy Enemy to check collision with
  bool DidCollideWith(const Enemy& enemy) const;

 private:
  BulletConfig bullet_config_;
  int life_ = kDefaultLife;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
