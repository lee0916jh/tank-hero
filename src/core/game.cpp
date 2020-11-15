#include "core/game.h"

namespace tank_hero::visualizer {

Game::Game() : tank_(kSpawnPoint) {}

void Game::HandleKeyInputs(const std::set<int>& keys) {
  bool a_pressed = false, s_pressed = false, d_pressed = false,
       w_pressed = false;
  for (int key : keys) {
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
  if (counter % 100 == 0)
    enemies_.emplace_back(ci::randVec2(), kEnemySpeed, &tank_);

  HandleBulletEnemyCollision();
  RemoveInvalidBullets();
  RemoveDeadEnemies();
  for (Bullet& bullet : bullets_)
    bullet.Move();
  for (Enemy& enemy : enemies_)
    enemy.ApproachTank();
}

void Game::DrawTank() const {
  ci::gl::color(ci::Color("green"));
  ci::Rectf tank_rect(tank_.GetTopLeftCorner(), tank_.GetBottomRightCorner());
  ci::gl::drawSolidRect(tank_rect);
}

void Game::DrawEnemies() const {
  ci::gl::color(ci::Color("red"));
  for (const Enemy& enemy : enemies_) {
    ci::gl::drawSolidCircle(enemy.GetPosition(), enemy.GetRadius());
  }
}

void Game::DrawBullets() const {
  ci::gl::color(ci::Color("yellow"));
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

}  // namespace tank_hero::visualizer