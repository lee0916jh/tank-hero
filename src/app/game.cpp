#include "app/game.h"

namespace tank_hero::app {

Game::Game(size_t window_width)
    : window_width_(window_width),
      tank_(vec2(window_width / 2, window_width / 2)) {}

void Game::HandleTankMovement(const std::set<int>& key) {
  bool a_pressed = false, s_pressed = false, d_pressed = false,
       w_pressed = false;
  for (int key : key) {
    if (key == KeyEvent::KEY_a) a_pressed = true;
    if (key == KeyEvent::KEY_s) s_pressed = true;
    if (key == KeyEvent::KEY_d) d_pressed = true;
    if (key == KeyEvent::KEY_w) w_pressed = true;
  }

  if (w_pressed) tank_.MoveUp();
  if (a_pressed) tank_.MoveLeft();
  if (d_pressed) tank_.MoveRight();
  if (s_pressed) tank_.MoveDown();
}

void Game::Draw() const {
  DrawTank();
  DrawEnemies();
  DrawBullets();
}

void Game::Update() {
  HandleBulletEnemyCollision();
  RemoveInvalidBullets();
  RemoveDeadEnemies();

  for (Bullet& bullet : bullets_) {
    bullet.Move();
  }
  for (Enemy& enemy : enemies_) {
    enemy.Move();
  }
}

void Game::DrawTank() const {
  ci::gl::color(kTankColor);
  ci::Rectf tank_rect(tank_.GetTopLeftCorner(), tank_.GetBottomRightCorner());
  ci::gl::drawSolidRect(tank_rect);
}

void Game::DrawEnemies() const {
  ci::gl::color(kEnemyColor);
  for (const Enemy& enemy : enemies_) {
    ci::gl::drawSolidCircle(enemy.GetPosition(), enemy.GetRadius());
  }
}

void Game::DrawBullets() const {
  ci::gl::color(kBulletColor);
  for (const Bullet& bullet : bullets_) {
    ci::gl::drawSolidCircle(bullet.GetPosition(), bullet.GetRadius());
  }
}

void Game::FireBullet(const vec2& mouse_pos) {
  bullets_.emplace_back(tank_, mouse_pos);
}

void Game::HandleBulletEnemyCollision() {
  for (Bullet& bullet : bullets_) {
    for (Enemy& enemy : enemies_) {
      if (bullet.DidHit(enemy)) {
        bullet.GoesInactive();
        enemy.Dies();
      }
    }
  }
}

void Game::RemoveInvalidBullets() {
  bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
                                [](const Bullet& bullet) {
                                  return !bullet.IsActive() ||
                                         bullet.IsOutOfMap(kFieldWidth);
                                }),
                 bullets_.end());
}

void Game::RemoveDeadEnemies() {
  enemies_.erase(
      std::remove_if(enemies_.begin(), enemies_.end(),
                     [](const Enemy& enemy) { return enemy.IsDead(); }),
      enemies_.end());
}

void Game::SpawnEnemy() {
  vec2 spawn_point =
      tank_.GetPosition() + ci::randVec2() * static_cast<float>(window_width_);
  enemies_.emplace_back(spawn_point, kInitialEnemySpeed, &tank_);
}

void Game::DropBomb() {
  enemies_.clear();
}

}  // namespace tank_hero::app