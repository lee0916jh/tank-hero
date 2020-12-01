#include "core/obstacle.h"

#include "catch2/catch.hpp"
#include "cinder/gl/gl.h"
#include "core/bullet.h"
#include "core/tank.h"

using glm::vec2;
using tank_hero::Bullet;
using tank_hero::BulletConfig;
using tank_hero::Movable;
using tank_hero::Obstacle;
using tank_hero::Tank;

TEST_CASE("When a bullet and an obstacle collide, bullet dies") {
  Obstacle obstacle(vec2(10, 10), vec2(30, 30));
  BulletConfig config{1, 10};
  SECTION("Left collision") {
    vec2 spawn_pos(5, 20);
    Bullet bullet(spawn_pos, vec2(1, 0), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Right collision") {
    vec2 spawn_pos(35, 20);
    Bullet bullet(spawn_pos, vec2(-1, 0), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Top collision") {
    vec2 spawn_pos(20, 5);
    Bullet bullet(spawn_pos, vec2(0, 1), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
  SECTION("Bottom collision") {
    vec2 spawn_pos(20, 35);
    Bullet bullet(spawn_pos, vec2(0, -1), config);
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE(bullet.IsActive());  // did not collide yet
    bullet.Move();
    obstacle.HandleCollisionWith(&bullet);
    REQUIRE_FALSE(bullet.IsActive());
  }
}

TEST_CASE(
    "When a non-bullet object collide with obstacles, it gets pushed out.") {
  Obstacle obstacle(vec2(10, 10), vec2(30, 30));
  SECTION("Left collision") {
    vec2 spawn_pos(5, 20);
    Movable movable(spawn_pos, vec2(1, 0), 10);
    movable.Move();
    REQUIRE(movable.GetPosition() == vec2(15, 20));
    obstacle.HandleCollisionWith(&movable);
    REQUIRE(movable.GetPosition() == vec2(9, 20));  // collider radius: 1
  }
  SECTION("Right collision") {
    vec2 spawn_pos(35, 20);
    Movable movable(spawn_pos, vec2(-1, 0), 10);
    movable.Move();
    REQUIRE(movable.GetPosition() == vec2(25, 20));
    obstacle.HandleCollisionWith(&movable);
    REQUIRE(movable.GetPosition() == vec2(31, 20));  // collider radius: 1
  }
  SECTION("Top collision") {
    vec2 spawn_pos(20, 5);
    Movable movable(spawn_pos, vec2(0, 1), 10);
    movable.Move();
    REQUIRE(movable.GetPosition() == vec2(20, 15));
    obstacle.HandleCollisionWith(&movable);
    REQUIRE(movable.GetPosition() == vec2(20, 9));  // collider radius: 1
  }
  SECTION("Bottom collision") {
    vec2 spawn_pos(20, 35);
    Movable movable(spawn_pos, vec2(0, -1), 10);
    movable.Move();
    REQUIRE(movable.GetPosition() == vec2(20, 25));
    obstacle.HandleCollisionWith(&movable);
    REQUIRE(movable.GetPosition() == vec2(20, 31));  // collider radius: 1
  }
}