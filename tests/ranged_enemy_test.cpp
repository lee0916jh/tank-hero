#include "core/ranged_enemy.h"

#include "catch2/catch.hpp"
// Ranged enemy derives from Movable and Enemy classes.
// So this only tests overriden method.

using glm::vec2;
using tank_hero::BulletConfig;
using tank_hero::RangedEnemy;

TEST_CASE("Ranged enemies stops moving when its close enough to the player.") {
  vec2 target_pos(0, 0);

  SECTION("When a ranged enemy is far from player it approaches player.") {
    RangedEnemy ranged_enemy(vec2(0, 500), 10, &target_pos);
    REQUIRE(ranged_enemy.GetPosition() == vec2(0, 500));
    ranged_enemy.Move();
    REQUIRE(ranged_enemy.GetPosition() == vec2(0, 490));
  }
  SECTION(
      "If a ranged enemy is close enough (as defined in ranged_enemy.cpp),"
      "it stops moving") {
    RangedEnemy ranged_enemy(vec2(100, 100), 10, &target_pos);
    REQUIRE(ranged_enemy.GetPosition() == vec2(100, 100));
    ranged_enemy.Move();
    REQUIRE(ranged_enemy.GetPosition() == vec2(100, 100));
  }
}