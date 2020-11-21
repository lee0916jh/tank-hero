#ifndef TANK_HERO_TANK_H
#define TANK_HERO_TANK_H

#include "cinder/gl/gl.h"
#include "enemy.h"
#include "movable.h"
#include "ranged.h"

namespace tank_hero {
using glm::vec2;

constexpr float kDefaultBulletSize = 5;
constexpr float kDefaultBulletSpeed = 8;
constexpr float kDefaultReloadTime = 1.5;

constexpr float kDefaultSpeed = 2;
constexpr size_t kTankSize = 60;

constexpr unsigned kDefaultLife = 5;

class Enemy;
class Tank : public Movable, public Ranged {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
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

  /// Rotates the gun towards the direction
  void RotateGun(const vec2& direction);

  /// Puts the tank back into the map if it went outside the map.
  /// \param field_width Size of the map
  void KeepInMap(const size_t field_width);

  /// Returns true only if this tank and the enemy collided with each other.
  /// \param enemy Enemy to check collision with
  bool DidCollideWith(const Enemy& enemy) const;

 private:
  int life_ = kDefaultLife;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
