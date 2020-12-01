#include "core/enemy.h"

#include "catch2/catch.hpp"
#include "cinder/gl/gl.h"
#include "core/tank.h"

using glm::vec2;
using tank_hero::Enemy;

TEST_CASE("Enemy approaches the tank when they move", "[Move]") {
  vec2 target_pos(10, 10);
  SECTION("Approach from the right") {
    Enemy enemy(vec2(15, 10), 1, &target_pos);
    enemy.Move();
    REQUIRE(enemy.GetPosition() == vec2(14, 10));
  }
  SECTION("Approach from the left") {
    Enemy enemy(vec2(5, 10), 1, &target_pos);
    enemy.Move();
    REQUIRE(enemy.GetPosition() == vec2(6, 10));
  }
  SECTION("Approach from the top") {
    Enemy enemy(vec2(10, 0), 5, &target_pos);
    enemy.Move();
    REQUIRE(enemy.GetPosition() == vec2(10, 5));
  }
  SECTION("Approach from the bottom") {
    Enemy enemy(vec2(10, 20), 1, &target_pos);
    enemy.Move();
    REQUIRE(enemy.GetPosition() == vec2(10, 19));
  }
}