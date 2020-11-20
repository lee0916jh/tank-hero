#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"
#include "core/movable.h"
#include "enemy.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankSize = 30;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultBulletDelay = 1.5;
constexpr unsigned kDefaultLife = 3;

class Enemy;
class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
  vec2 GetTopLeftCorner() const;
  vec2 GetBottomRightCorner() const;
  float GetBulletSize() const { return bullet_size_; }
  float GetBulletSpeed() const { return bullet_speed_; }
  float GetReloadTime() const { return reload_time_; }
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
  float bullet_size_ = kDefaultBulletSize;
  float bullet_speed_ = kDefaultBulletSpeed;
  float reload_time_ = kDefaultBulletDelay;
  int life_ = kDefaultLife;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
