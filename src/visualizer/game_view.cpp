#include "visualizer/game_view.h"

namespace tank_hero::visualizer {

GameView::GameView(const Game* game, size_t window_size,
                   const vec2* camera_offset)
    : game_(game),
      window_size_(window_size),
      camera_offset_(camera_offset),
      heart_img_(Texture2d::create(loadImage(loadAsset("heart.png")))),
      tank_body_img_(Texture2d::create(loadImage(loadAsset("tank_body.png")))),
      tank_gun_img_(Texture2d::create(loadImage(loadAsset("tank_gun.png")))),
      melee_enemy_img_(
          Texture2d::create(loadImage(loadAsset("melee_enemy.png")))),
      ranged_enemy_img_(
          Texture2d::create(loadImage(loadAsset("ranged_enemy.png")))) {}

void GameView::Draw() const {
  if (game_->IsOn()) {
    DrawTank();
    DrawEnemies();
    DrawBullets();
    DrawObstacles();
    DisplayGameStatus();
  } else {
    DrawGameEndScreen();
  }
}

void GameView::DrawTank() const {
  vec2 window_center(window_size_ / 2, window_size_ / 2);
  const Tank& tank = game_->GetTank();
  float tank_body_rotation = CalcRotation(tank.GetDirection());
  float tank_gun_rotation = CalcRotation(tank.GetGunRotation());

  DrawRotatedImage(tank_body_img_, tank.GetPosition(), tank_body_rotation);
  DrawRotatedImage(tank_gun_img_, tank.GetPosition(), tank_gun_rotation);
}

void GameView::DrawEnemies() const {
  for (const Enemy& enemy : game_->GetEnemies()) {
    float rotation = CalcRotation(enemy.GetPosition());
    DrawRotatedImage(melee_enemy_img_, enemy.GetPosition(), rotation);
  }
  for (const RangedEnemy& ranged_enemy : game_->GetRangedEnemies()) {
    float rotation = CalcRotation(ranged_enemy.GetPosition());
    DrawRotatedImage(ranged_enemy_img_, ranged_enemy.GetPosition(), rotation);
  }
}

void GameView::DrawBullets() const {
  ci::gl::color(kBulletColor);
  for (const Bullet& tank_bullet : game_->GetTankBullets()) {
    ci::gl::drawSolidCircle(tank_bullet.GetPosition() - *camera_offset_,
                            tank_bullet.GetColliderRadius());
  }
  ci::gl::color(ci::Color("red"));
  for (const Bullet& enemy_bullet : game_->GetEnemyBullets()) {
    ci::gl::drawSolidCircle(enemy_bullet.GetPosition() - *camera_offset_,
                            enemy_bullet.GetColliderRadius());
  }
}
void GameView::DrawObstacles() const {
  ci::gl::color(kObstacleColor);
  for (const Obstacle& obstacle : game_->GetObstacles()) {
    ci::gl::drawSolidRect(
        ci::Rectf(obstacle.GetTopLeft() - *camera_offset_,
                  obstacle.GetBottomRight() - *camera_offset_));
  }
}

void GameView::DisplayGameStatus() const {
  vec2 text_pos(kTextMargin, kTextMargin);
  ci::gl::drawString("LIFE: ", text_pos, kTextColor, kTextFont);

  vec2 heart_top_left = vec2(3 * kTextMargin, kTextMargin);
  vec2 heart_bottom_right =
      heart_top_left + vec2(kHeartImgWidth, kHeartImgWidth);

  ci::gl::color(ci::Color("white"));
  for (size_t i = 0; i < game_->GetCurrentLife(); i++) {
    ci::gl::draw(heart_img_, ci::Rectf(heart_top_left, heart_bottom_right));
    heart_top_left.x += kTextMargin;
    heart_bottom_right.x += kTextMargin;
  }

  text_pos.y += kTextMargin;
  ci::gl::drawString(
      "Reload Time: " + std::to_string(game_->GetReloadTime()) + " sec",
      text_pos, kTextColor, kTextFont);

  text_pos.y += kTextMargin;
  ci::gl::drawString("Kills: " + std::to_string(game_->GetKillCount()),
                     text_pos, kTextColor, kTextFont);
}

void GameView::DrawGameEndScreen() const {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  vec2 center(window_size_ / 2, window_size_ / 2);
  ci::gl::drawStringCentered("GAME OVER", center, kGameOverColor,
                             kGameOverFont);
}

void GameView::DrawRotatedImage(Texture2dRef image, const vec2& position,
                                float rotation) const {
  ci::gl::color(ci::Color("white"));

  vec2 img_center = image->getSize() / 2;

  ci::gl::pushModelView();
  ci::gl::translate(position - *camera_offset_);
  ci::gl::rotate(rotation);
  ci::gl::translate(-img_center);

  ci::gl::draw(image);
  ci::gl::popModelView();
}

float GameView::CalcRotation(const vec2& direction) const {
  float angle = acos(glm::dot(vec2(0, -1), glm::normalize(direction)));
  return direction.x > 0 ? angle : 2 * glm::pi<float>() - angle;
}

}  // namespace tank_hero::visualizer