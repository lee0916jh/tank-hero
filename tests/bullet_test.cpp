#include "core/bullet.h"

#include <catch2/catch.hpp>
#include <vector>

#include "cinder/gl/gl.h"
#include "core/enemy.h"
#include "core/movable.h"
#include "core/ranged.h"
#include "core/tank.h"
using glm::vec2;
using tank_hero::Bullet;
using tank_hero::BulletConfig;
using tank_hero::Enemy;
using tank_hero::Movable;
using tank_hero::Tank;

TEST_CASE("Bullet Moves", "[Move]") {
  vec2 position(100, 100);
  BulletConfig config{5, 8};
  SECTION("Bullet Moves Right") {
    Bullet bullet(position, vec2(100, 0), config);
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(108, 100));  // default speed is 7
  }
  SECTION("Bullet Moves Left") {
    Bullet bullet(position, vec2(-100, 0), config);
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(92, 100));
  }
  SECTION("Bullet Moves Up") {
    Bullet bullet(position, vec2(0, -100), config);
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(100, 92));
  }
  SECTION("Bullet Moves Down") {
    Bullet bullet(position, vec2(0, 100), config);
    bullet.Move();
    REQUIRE(bullet.GetPosition() == vec2(100, 108));
  }
}

TEST_CASE("IsOutOfMap returns true when the bullet goes outside the map.",
          "[IsOutOfMap]") {
  vec2 position(5, 5);
  BulletConfig config{5, 8};
  SECTION("Bullet crosses boundary to the top") {
    Bullet bullet(position, vec2(5, 0), config);
    REQUIRE_FALSE(bullet.IsOutOfMap(10));  // 10 x 10 map
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the right") {
    Bullet bullet(position, vec2(10, 5), config);
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the bottom") {
    Bullet bullet(position, vec2(5, 10), config);
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
  SECTION("Bullet crosses boundary to the left") {
    Bullet bullet(position, vec2(0, 5), config);
    REQUIRE_FALSE(bullet.IsOutOfMap(10));
    bullet.Move();
    REQUIRE(bullet.IsOutOfMap(10));
  }
}

TEST_CASE("DidHit returns true only if it hits a Movable object", "[DidHit]") {
  vec2 position(0, 0);
  vec2 dummy_target(0, 0);
  BulletConfig config{3, 10};

  Bullet bullet(position, vec2(1, 0), config);
  Enemy enemy(vec2(15, 0), 0, &dummy_target);
  // enemy collider radius: 10

  REQUIRE_FALSE(bullet.DidHit(enemy));
  bullet.Move();
  REQUIRE(bullet.DidHit(enemy));
}

TEST_CASE("GetKilledEnemy returns iterator to the killed", "[GetKilledEnemy]") {
  vec2 spawn_pos(0, 0);
  vec2 direction(1, 0);
  BulletConfig config{1, 1};
  Bullet bullet(spawn_pos, direction, config);

  SECTION(
      "GetKilledEnemy throws exception if vector element type is not Enemy") {
    std::vector<Movable> not_enemies;
    not_enemies.emplace_back(spawn_pos);
    REQUIRE_THROWS_AS(bullet.GetKilledEnemy(&not_enemies),
                      std::invalid_argument);
  }
  SECTION(
      "GetKilledEnemy returns the iterator to the killed enemy if anyone is "
      "killed") {
    std::vector<Enemy> enemies;
    vec2 target(10, 10);
    enemies.emplace_back(spawn_pos + vec2(100, 100), 1, &target);
    enemies.emplace_back(spawn_pos, 1, &target);
    // the one at index 1 is being killed

    auto dead_enemy = bullet.GetKilledEnemy(&enemies);
    REQUIRE(dead_enemy == enemies.begin() + 1);
  }
  SECTION(
      "GetKilledEnemy returns the iterator to the end if no one is killed") {
    std::vector<Enemy> enemies;
    vec2 target(10, 10);
    enemies.emplace_back(spawn_pos + vec2(100, 100), 1, &target);
    enemies.emplace_back(spawn_pos + vec2(100, 100), 1, &target);
    // Enemies are (100,100) away. No one is getting killed

    auto dead_enemy = bullet.GetKilledEnemy(&enemies);
    REQUIRE(dead_enemy == enemies.end());
  }
}