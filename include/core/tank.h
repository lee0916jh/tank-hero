#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "bullet_config.h"
#include "cinder/gl/gl.h"
#include "enemy.h"
#include "movable.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankSize = 30;

constexpr unsigned kDefaultLife = 5;

class Enemy;
class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
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

  /// Reduce this tank's reload time by given amount
  void ReduceReloadTime(float reduce_amount);

 private:
  BulletConfig bullet_config_;
  int life_ = kDefaultLife;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
