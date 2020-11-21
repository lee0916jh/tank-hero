#include "visualizer/tank_hero_app.h"
namespace tank_hero::app {
TankHeroApp::TankHeroApp()
    : game_(kWindowSize, kObstacles),
      camera_offset_(kWindowSize / 2, kWindowSize / 2) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void TankHeroApp::setup() {
  heart_img_ = ci::gl::Texture2d::create(loadImage(loadAsset("heart.png")));
  wall_img_ = ci::gl::Texture2d::create(loadImage(loadAsset("wall.png")));
  tank_body_img_ =
      ci::gl::Texture2d::create(ci::loadImage(loadAsset("tank_body.png")));
  tank_gun_img_ =
      ci::gl::Texture2d::create(ci::loadImage(loadAsset("tank_gun.png")));
  melee_enemy_img_ =
      ci::gl::Texture2d::create(ci::loadImage(loadAsset("melee_enemy.png")));
}

void TankHeroApp::update() {
  AdjustCameraOffset();
  game_.SpawnEnemy();

  if (mouse_down_ && game_.TankIsLoaded()) {
    game_.FireBullet(mouse_pos_ + camera_offset_);
  }
  game_.HandleTankMovement(move_keys_);
  game_.Update();
  if (ReadyToIncreaseDifficulty()) game_.IncreaseDifficulty();
}

void TankHeroApp::draw() {
  ci::gl::clear(kBgColor);

  if (game_.IsOn()) {
    DrawObstacles();
    DrawTank();
    DrawEnemies();
    DrawBullets();
    DisplayGameStatus();
  } else {
    DrawGameEndScreen();
  }
}

void TankHeroApp::DrawTank() const {
  vec2 window_center(kWindowSize / 2, kWindowSize / 2);
  const Tank& tank = game_.GetTank();
  float tank_body_rotation = CalcRotation(tank.GetDirection());
  float tank_gun_rotation = CalcRotation(mouse_pos_ - window_center);

  DrawRotatedImage(tank_body_img_, tank.GetPosition(), tank_body_rotation);
  DrawRotatedImage(tank_gun_img_, tank.GetPosition(), tank_gun_rotation);
}

void TankHeroApp::DrawEnemies() const {
  for (const Enemy& enemy : game_.GetEnemies()) {
    float rotation = CalcRotation(enemy.GetPosition());
    DrawRotatedImage(melee_enemy_img_, enemy.GetPosition(), rotation);
  }
}

void TankHeroApp::DrawBullets() const {
  ci::gl::color(kBulletColor);
  for (const Bullet& bullet : game_.GetBullets()) {
    ci::gl::drawSolidCircle(bullet.GetPosition() - camera_offset_,
                            bullet.GetColliderRadius());
  }
}
void TankHeroApp::DrawObstacles() const {
  for (const Obstacle& obstacle : game_.GetObstacles()) {
    ci::gl::draw(wall_img_,
                 ci::Rectf(obstacle.GetTopLeft() - camera_offset_,
                           obstacle.GetBottomRight() - camera_offset_));
  }
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

void TankHeroApp::mouseUp(MouseEvent event) { mouse_down_ = false; }

void TankHeroApp::AdjustCameraOffset() {
  const vec2& tank_pos = game_.GetTank().GetPosition();

  // if tank is in the middle of map camera follows the tank
  if (tank_pos.x > kWindowSize / 2.0 &&
      tank_pos.x < kFieldWidth - (kWindowSize / 2.0)) {
    camera_offset_.x = tank_pos.x - kWindowSize / 2.0;
  }
  // if tank is close to the edge of the map camera stops following tank.
  else if (tank_pos.x <= kWindowSize / 2.0) {
    camera_offset_.x = 0;
  } else {
    camera_offset_.x = kFieldWidth - kWindowSize;
  }

  if (tank_pos.y > kWindowSize / 2.0 &&
      tank_pos.y < kFieldWidth - (kWindowSize / 2.0)) {
    camera_offset_.y = tank_pos.y - kWindowSize / 2.0;
  } else if (tank_pos.y <= kWindowSize / 2.0) {
    camera_offset_.y = 0;
  } else {
    camera_offset_.y = kFieldWidth - kWindowSize;
  }
}

void TankHeroApp::DisplayGameStatus() const {
  vec2 text_pos(kTextMargin, kTextMargin);
  ci::gl::drawString("LIFE: ", text_pos, kTextColor, kTextFont);

  vec2 heart_top_left = vec2(3 * kTextMargin, kTextMargin);
  vec2 heart_bottom_right =
      heart_top_left + vec2(kHeartImgWidth, kHeartImgWidth);
  for (size_t i = 0; i < game_.GetCurrentLife(); i++) {
    ci::gl::draw(heart_img_, ci::Rectf(heart_top_left, heart_bottom_right));
    heart_top_left.x += kTextMargin;
    heart_bottom_right.x += kTextMargin;
  }

  text_pos.y += kTextMargin;
  ci::gl::drawString(
      "Reload Time: " + std::to_string(game_.GetReloadTime()) + " sec",
      text_pos, kTextColor, kTextFont);

  text_pos.y += kTextMargin;
  ci::gl::drawString("Kills: " + std::to_string(game_.GetKillCount()), text_pos,
                     kTextColor, kTextFont);
}

void TankHeroApp::DrawGameEndScreen() const {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  vec2 center(kWindowSize / 2, kWindowSize / 2);
  ci::gl::drawStringCentered("GAME OVER", center, kGameOverColor,
                             kGameOverFont);
}

bool TankHeroApp::ReadyToIncreaseDifficulty() {
  if (increase_difficulty_timer_.getSeconds() > kIncreaseDifficultyThreshold) {
    increase_difficulty_timer_.start();
    return true;
  }
  return false;
}

void TankHeroApp::DrawRotatedImage(Texture2dRef image, const vec2& position,
                                   float rotation) const {
  vec2 img_center = image->getSize() / 2;

  ci::gl::pushModelView();
  ci::gl::translate(position - camera_offset_);
  ci::gl::rotate(rotation);
  ci::gl::translate(-img_center);

  ci::gl::draw(image);
  ci::gl::popModelView();
}

float TankHeroApp::CalcRotation(const vec2& direction) const {
  float angle = acos(glm::dot(vec2(0, -1), glm::normalize(direction)));
  return direction.x > 0 ? angle : 4 * glm::pi<float>() - angle;
}

}  // namespace tank_hero::app
