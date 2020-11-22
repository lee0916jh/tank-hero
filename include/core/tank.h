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

constexpr float kDefaultSpeed = 3;
constexpr size_t kTankSize = 60;

constexpr int kInitialLifeCount = 5;
constexpr int kInitialBombCount = 5;

class Enemy;
class Tank : public Movable, public Ranged {
 public:
  explicit Tank(const vec2& position);

  // Getters and Setters
  const vec2& GetGunRotation() const { return gun_rotation_; }
  bool IsAlive() const { return life_ > 0; }
  bool HasBomb() const { return bomb_ > 0; }
  int GetLifeCount() const { return life_; };
  int GetBombCount() const { return bomb_; };
  void DecrementLife() { life_--; }
  void DecrementBombCount() { bomb_--; }

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void MoveUpLeft();
  void MoveUpRight();
  void MoveDownLeft();
  void MoveDownRight();

  /// Puts the tank back into the map if it went outside the map.
  /// \param field_width Size of the map
  void KeepInMap(const size_t field_width);

  /// Returns true only if this tank and the enemy collided with each other.
  /// \param enemy Enemy to check collision with
  bool DidCollideWith(const Enemy& enemy) const;

  /// Rotates the gun towards the direction
  void RotateGun(const vec2& direction);

 private:
  int life_ = kInitialLifeCount;
  int bomb_ = kInitialBombCount;
  vec2 gun_rotation_;
};
}  // namespace tank_hero

#endif  // TANK_HERO_TANK_H
