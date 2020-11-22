#ifndef TANK_HERO_TANK_HERO_APP_H
#define TANK_HERO_TANK_HERO_APP_H

#include <cmath>
#include <set>
#include <vector>

#include "cinder/Font.h"
#include "cinder/Timer.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game.h"
#include "core/obstacle.h"
#include "game_view.h"

namespace tank_hero::visualizer {
using ci::Timer;
using ci::app::KeyEvent;
using ci::app::MouseEvent;
using glm::vec2;
using std::vector;

constexpr size_t kWindowSize = 1000;

const size_t kIncreaseDifficultyThreshold =
    5;  // difficulty will increase after this number of seconds.
const vector<Obstacle> kObstacles = {{vec2(0, 0), vec2(100, 100)},
                                     {vec2(200, 200), vec2(400, 800)}};

class TankHeroApp : public ci::app::App {
 public:
  TankHeroApp();

  void setup() override;
  void draw() override;
  void update() override;
  void keyDown(KeyEvent event) override;
  void keyUp(KeyEvent event) override;
  void mouseDown(MouseEvent event) override;
  void mouseDrag(MouseEvent event) override;
  void mouseUp(MouseEvent event) override;

 private:
  /// Calculates camera offset from the position of the tank.
  void AdjustCameraOffset();

  /// Checks if it's time to increase difficulty
  bool ReadyToIncreaseDifficulty();

  Game game_;
  GameView game_view_;

  vec2 camera_offset_;
  std::set<int> move_keys_;
  vec2 mouse_pos_;
  bool mouse_down_;

  Timer increase_difficulty_timer_;
};
}  // namespace tank_hero::visualizer
#endif  // TANK_HERO_TANK_HERO_APP_H
