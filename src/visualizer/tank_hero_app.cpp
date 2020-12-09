#include "visualizer/tank_hero_app.h"

namespace tank_hero::visualizer {
TankHeroApp::TankHeroApp()
    : game_(kWindowSize, kObstacles),
      game_view_(&game_, kWindowSize, &camera_offset_),
      camera_offset_(kWindowSize / 2, kWindowSize / 2) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
  increase_difficulty_timer_.start();
}

void TankHeroApp::setup() {}

void TankHeroApp::update() {
  if (game_.IsOn()) {
    game_view_.AdjustCameraOffset();

    game_.HandleTankMovement(move_keys_, mouse_pos_ + camera_offset_);
    game_.Update();
    game_.SpawnEnemies();
    game_.SpawnItem();

    if (mouse_down_) game_.TryAndFireTankBullet();
    if (ReadyToIncreaseDifficulty()) game_.IncreaseDifficulty();
  }
}

void TankHeroApp::draw() {
  ci::Color8u background_color("grey");
  ci::gl::clear(background_color);

  game_view_.Draw();
}

void TankHeroApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_SPACE) {
    game_.DropBomb();
  } else {
    move_keys_.insert(event.getCode());
  }
}

void TankHeroApp::keyUp(KeyEvent event) { move_keys_.erase(event.getCode()); }

void TankHeroApp::mouseDown(MouseEvent event) {
  mouse_down_ = true;
  mouse_pos_ = event.getPos();
}

void TankHeroApp::mouseDrag(MouseEvent event) { mouse_pos_ = event.getPos(); }

void TankHeroApp::mouseUp(MouseEvent event) {
  mouse_pos_ = event.getPos();
  mouse_down_ = false;
}

bool TankHeroApp::ReadyToIncreaseDifficulty() {
  if (increase_difficulty_timer_.getSeconds() > kIncreaseDifficultyThreshold) {
    increase_difficulty_timer_.start();
    return true;
  }
  return false;
}
}  // namespace tank_hero::visualizer
