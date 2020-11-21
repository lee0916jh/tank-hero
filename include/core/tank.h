#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "bullet_config.h"
#include "cinder/gl/gl.h"
#include "enemy.h"
#include "movable.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankSize = 60;

constexpr unsigned kDefaultLife = 5;

class Enemy;
class Tank : public Movable {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
  const BulletConfig& GetBulletConfig() const { return bullet_config_; }
  const vec2& GetGunRotation() const { return gun_rotation_; }
  bool IsAlive() const { return life_ > 0; }
  size_t GetLifeCount() const { return life_; };
  void DecrementLife() { life_--; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void MoveUpLeft();
  void MoveUpRight();
  void MoveDownLeft();
  void MoveDownRight();

  /// Rotates gun towards the given direction.
  void RotateGun(const vec2& direction);

  /// Puts the tank back into the map if it went outside the map.
  /// \param field_width Size of the map
  void KeepInMap(const size_t field_width);

  /// Returns true only if this tank and the enemy collided with each other.
  /// \param enemy Enemy to check collision with
  bool DidCollideWith(const Enemy& enemy) const;

  /// Reduce this tank's reload time by given amount
  void ReduceReloadTime(float reduce_amount);

 private:
  vec2 gun_rotation_;
  BulletConfig bullet_config_;
  int life_ = kDefaultLife;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
