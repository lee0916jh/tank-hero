#ifndef TANK_HERO_TANK_HERO_APP_H
#define TANK_HERO_TANK_HERO_APP_H

#include <set>

#include "cinder/Font.h"
#include "cinder/Timer.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game.h"

namespace tank_hero::app {
using ci::Timer;
using ci::app::KeyEvent;
using ci::app::MouseEvent;
using glm::vec2;

constexpr int kWindowSize = 1000;
const ci::Color kTextColor("black");
const ci::Font kTextFont("Arial", 20);
const ci::Color kGameOverColor("red");
const ci::Font kGameOverFont("Arial", 50);
const size_t kTextMargin = 30;
const size_t kHeartImgWidth = 20;
const size_t kIncreaseDifficultyThreshold =
    30;  // difficulty will increase after this number of seconds.

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
  void DrawTank() const;
  void DrawEnemies() const;
  void DrawBullets() const;
  void DisplayGameStatus() const;
  void DrawGameEndScreen() const;

  /// Calculates camera offset from the position of the tank.
  void AdjustCameraOffset();

  /// Checks if it's time to increase difficulty
  bool ReadyToIncreaseDifficulty();

  std::set<int> move_keys_;
  vec2 mouse_pos_;
  bool mouse_down_;
  Game game_;
  vec2 camera_offset_;
  Timer increase_difficulty_timer_;
  ci::gl::Texture2dRef heart_img_;
};
}  // namespace tank_hero::app
#endif  // TANK_HERO_TANK_HERO_APP_H
