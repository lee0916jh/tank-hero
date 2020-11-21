#include "core/obstacle.h"

#include <cmath>

namespace tank_hero {

Obstacle::Obstacle(const vec2& top_left, const vec2& bottom_right)
    : top_left_(top_left), bottom_right_(bottom_right) {}

void Obstacle::HandleCollisionWith(Bullet* bullet) const {
  HandleCollisionWith(static_cast<Movable*>(bullet));
}
void Obstacle::HandleCollisionWith(Tank* tank) const {
  HandleCollisionWith(static_cast<Movable*>(tank));
}
void Obstacle::HandleCollisionWith(Enemy* enemy) const {
  HandleCollisionWith(static_cast<Movable*>(enemy));
}

void Obstacle::HandleCollisionWith(Movable* movable) const {
  if (!this->DidCollideWith(*movable)) return;

  Bullet* bullet_ptr = dynamic_cast<Bullet*>(movable);
  if (bullet_ptr) {
    bullet_ptr->MakeInactive();  // bullet dies regardless of direction
    return;
  }

  string collision_direction = FindCollisionDirection(*movable);
  if (collision_direction == "left") {
    movable->SetPositionX(top_left_.x - movable->GetColliderRadius());
  } else if (collision_direction == "right") {
    movable->SetPositionX(bottom_right_.x + movable->GetColliderRadius());
  } else if (collision_direction == "top") {
    movable->SetPositionY(top_left_.y - movable->GetColliderRadius());
  } else if (collision_direction == "bottom") {
    movable->SetPositionY(bottom_right_.y + movable->GetColliderRadius());
  }
}

string Obstacle::FindCollisionDirection(const Movable& movable) const {
  string collision_direction;
  const vec2& movable_pos = movable.GetPosition();
  std::unordered_map<string, float> distances_to_wall = {
      {"left", abs(movable_pos.x - top_left_.x)},
      {"right", abs(movable_pos.x - bottom_right_.x)},
      {"top", abs(movable_pos.y - top_left_.y)},
      {"bottom", abs(movable_pos.y - bottom_right_.y)}};

  std::pair<string, float> wall_min_distance = *std::min_element(
      distances_to_wall.begin(), distances_to_wall.end(),
      [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

  return wall_min_distance.first;
}

bool Obstacle::DidCollideWith(const Movable& movable) const {
  vec2 center((bottom_right_.x + top_left_.x) / 2,
              (bottom_right_.y + top_left_.y) / 2);
  float width = bottom_right_.x - top_left_.x;
  float length = bottom_right_.y - top_left_.y;

  float x_diff = abs(center.x - movable.GetPosition().x);
  float y_diff = abs(center.y - movable.GetPosition().y);

  return x_diff < (movable.GetColliderRadius() + width / 2) &&
         y_diff < (movable.GetColliderRadius() + length / 2);
}

}  // namespace tank_hero