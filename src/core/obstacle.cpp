#include "core/obstacle.h"

#include <cmath>

#include "core/bullet.h"

namespace tank_hero {

Obstacle::Obstacle(const vec2& top_left, const vec2& bottom_right)
    : top_left_(top_left), bottom_right_(bottom_right) {}

void Obstacle::HandleCollisionWith(Movable* movable) const {
  if (!CheckCollision(*movable)) return;

  Bullet* bullet_ptr = dynamic_cast<Bullet*>(movable);
  if (bullet_ptr) {
    bullet_ptr->GoInactive();  // bullet dies regardless of direction
    return;
  }

  Direction collision_direction = FindCollisionDirection(*movable);
  switch (collision_direction) {
    case Direction::kLeft:
      movable->SetPositionX(top_left_.x - movable->GetColliderRadius());
      break;
    case Direction::kRight:
      movable->SetPositionX(bottom_right_.x + movable->GetColliderRadius());
      break;
    case Direction::kTop:
      movable->SetPositionY(top_left_.y - movable->GetColliderRadius());
      break;
    case Direction::kBottom:
      movable->SetPositionY(bottom_right_.y + movable->GetColliderRadius());
      break;
    default:
      break;
  }
}

bool Obstacle::CheckCollision(const Movable& movable) const {
  vec2 center((bottom_right_.x + top_left_.x) / 2,
              (bottom_right_.y + top_left_.y) / 2);
  float width = bottom_right_.x - top_left_.x;
  float length = bottom_right_.y - top_left_.y;

  float x_diff = abs(center.x - movable.GetPosition().x);
  float y_diff = abs(center.y - movable.GetPosition().y);

  return x_diff < (movable.GetColliderRadius() + width / 2) &&
         y_diff < (movable.GetColliderRadius() + length / 2);
}

Direction Obstacle::FindCollisionDirection(const Movable& movable) const {
  const vec2& movable_pos = movable.GetPosition();
  std::unordered_map<Direction, float> distances_to_wall = {
      {Direction::kLeft, abs(movable_pos.x - top_left_.x)},
      {Direction::kRight, abs(movable_pos.x - bottom_right_.x)},
      {Direction::kTop, abs(movable_pos.y - top_left_.y)},
      {Direction::kBottom, abs(movable_pos.y - bottom_right_.y)}};

  std::pair<Direction, float> wall_min_distance = *std::min_element(
      distances_to_wall.begin(), distances_to_wall.end(),
      [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

  return wall_min_distance.first;
}
}  // namespace tank_hero