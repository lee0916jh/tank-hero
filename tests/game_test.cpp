#include "core/game.h"

#include <set>

#include "catch2/catch.hpp"
#include "cinder/app/App.h"
using glm::vec2;
using tank_hero::Game;

TEST_CASE("Tank Movement tests", "[HandleTankMovement]") {
  Game game(100);  // Tank spawns at (50,50) with speed of 2

  std::set<int> keys;
  vec2 mouse_position(0, 0);
  SECTION("Tank moves left") {
    keys.insert(ci::app::KeyEvent::KEY_a);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(48, 50));
  }
  SECTION("Tank moves right") {
    keys.insert(ci::app::KeyEvent::KEY_d);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(52, 50));
  }
  SECTION("Tank moves up") {
    keys.insert(ci::app::KeyEvent::KEY_w);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 48));
  }
  SECTION("Tank moves down") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(50, 52));
  }
  SECTION("Tank moves in diagonal directions") {
    keys.insert(ci::app::KeyEvent::KEY_s);
    keys.insert(ci::app::KeyEvent::KEY_a);  // left down
    game.HandleTankMovement(keys, mouse_position);
    REQUIRE(game.GetTank().GetPosition() == vec2(48, 52));
  }
}

TEST_CASE("Enemy spawns <window size> away from the player)",
          "[SpawnEnemies]") {
  Game game(100);
  for (size_t i = 0; i < 5; i++) {
    game.SpawnEnemies();
    REQUIRE(glm::distance(game.GetEnemies()[i].GetPosition(),
                          game.GetTank().GetPosition()) == Approx(100));
  }
}

TEST_CASE("DropBomb instantly kills all enemies", "[DropBomb]") {
  Game game(100);
  for (size_t i = 0; i < 100; i++) {
    game.SpawnEnemies();
  }
  REQUIRE(game.GetEnemies().size() == 100);
  game.DropBomb();
  REQUIRE(game.GetEnemies().size() == 0);
}
