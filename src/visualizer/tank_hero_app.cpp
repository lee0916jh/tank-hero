#include "visualizer/tank_hero_app.h"
namespace tank_hero::app {
TankHeroApp::TankHeroApp()
    : game_(kWindowSize), camera_offset_(kWindowSize / 2, kWindowSize / 2) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::update() {
  AdjustCameraOffset();
  if (frame_count_ % 10 == 0) game_.SpawnEnemy();
  frame_count_++;

  if (mouse_down_) game_.FireBullet(mouse_pos_);
  game_.HandleTankMovement(movement_keys_);
  game_.Update();
}

void TankHeroApp::draw() {
  ci::Color8u background_color(ci::Color("grey"));
  ci::gl::clear(background_color);

  DrawTank();
  DrawEnemies();
  DrawBullets();
}

void TankHeroApp::DrawTank() const {
  ci::gl::color(kTankColor);
  const Tank& tank = game_.GetTank();
  ci::Rectf tank_rect(tank.GetTopLeftCorner() - camera_offset_,
                      tank.GetBottomRightCorner() - camera_offset_);
  ci::gl::drawSolidRect(tank_rect);
}

void TankHeroApp::DrawEnemies() const {
  ci::gl::color(kEnemyColor);
  for (const Enemy& enemy : game_.GetEnemies()) {
    ci::gl::drawSolidCircle(enemy.GetPosition() - camera_offset_,
                            enemy.GetRadius());
  }
}

void TankHeroApp::DrawBullets() const {
  ci::gl::color(kBulletColor);
  for (const Bullet& bullet : game_.GetBullets()) {
    ci::gl::drawSolidCircle(bullet.GetPosition() - camera_offset_,
                            bullet.GetRadius());
  }
}

void TankHeroApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_SPACE) {
    game_.DropBomb();
  } else {
    movement_keys_.insert(event.getCode());
  }
}

void TankHeroApp::keyUp(KeyEvent event) {
  movement_keys_.erase(event.getCode());
}

void TankHeroApp::mouseDown(MouseEvent event) {
  mouse_down_ = true;
  mouse_pos_ = event.getPos();
}

void TankHeroApp::mouseDrag(MouseEvent event) { mouse_pos_ = event.getPos(); }

void TankHeroApp::mouseUp(MouseEvent event) { mouse_down_ = false; }

void TankHeroApp::AdjustCameraOffset() {
  const vec2& tank_pos = game_.GetTank().GetPosition();
  camera_offset_.x =
      (tank_pos.x > kWindowSize / 2) ? (tank_pos.x - kWindowSize / 2) : 0;
  camera_offset_.y =
      (tank_pos.y > kWindowSize / 2) ? (tank_pos.y - kWindowSize / 2) : 0;
}

}  // namespace tank_hero::app
