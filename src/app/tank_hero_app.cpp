#include "app/tank_hero_app.h"
namespace tank_hero::app {
TankHeroApp::TankHeroApp() : game_(kWindowSize) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::update() {
  if (frame_count_ % 10 == 0) game_.SpawnEnemy();
  frame_count_++;

  if (mouse_down_) game_.FireBullet(mouse_pos_);
  game_.HandleTankMovement(held_keys_);
  game_.Update();
}

void TankHeroApp::draw() {
  ci::Color8u background_color(ci::Color("grey"));
  ci::gl::clear(background_color);

  game_.Draw();
}

void TankHeroApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_SPACE) {
    game_.DropBomb();
  } else {
    held_keys_.insert(event.getCode());
  }
}

void TankHeroApp::keyUp(KeyEvent event) { held_keys_.erase(event.getCode()); }

void TankHeroApp::mouseDown(MouseEvent event) {
  mouse_down_ = true;
  mouse_pos_ = event.getPos();
}

void TankHeroApp::mouseDrag(MouseEvent event) { mouse_pos_ = event.getPos(); }

void TankHeroApp::mouseUp(MouseEvent event) { mouse_down_ = false; }

}  // namespace tank_hero::app
