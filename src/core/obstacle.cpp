#include "core/obstacle.h"

namespace tank_hero {

Obstacle::Obstacle(const vec2& top_left, const vec2& bottom_right)
    : top_left_(top_left), bottom_right_(bottom_right) {}

void Obstacle::HandleCollisionWith(Movable* movable) const {
  float obj_radius = movable->GetColliderRadius();
  vector<string> collision_directions = FindCollisionDirection(*movable);

  for (const string& direction : collision_directions) {
    Bullet* bullet_ptr = dynamic_cast<Bullet*>(movable);
    if (bullet_ptr) {
      bullet_ptr->GoesInactive();  // bullet dies regardless of direction
    } else if (direction == "left") {
      movable->SetPositionX(top_left_.x - obj_radius);
    } else if (direction == "right") {
      movable->SetPositionX(bottom_right_.x + obj_radius);
    } else if (direction == "top") {
      movable->SetPositionY(top_left_.y - obj_radius);
    } else if (direction == "bottom") {
      movable->SetPositionY(bottom_right_.y + obj_radius);
    }
  }
}

vector<string> Obstacle::FindCollisionDirection(const Movable& movable) const {
  vector<string> collision_directions;

  float left_x = top_left_.x, right_x = bottom_right_.x, top_y = top_left_.y,
        bottom_y = bottom_right_.y;
  vec2 center((right_x - left_x) / 2, (bottom_y - top_y) / 2);

  const vec2& obj_pos = movable.GetPosition();
  float obj_radius = movable.GetColliderRadius();

  if (obj_pos.x + obj_radius > left_x && obj_pos.x < center.x) {
    collision_directions.emplace_back("left");
  } else if (obj_pos.x - obj_radius < right_x && obj_pos.x > center.x) {
    collision_directions.emplace_back("right");
  }

  if (obj_pos.y + obj_radius > top_y && obj_pos.y < center.y) {
    collision_directions.emplace_back("top");
  } else if (obj_pos.y - obj_radius < bottom_y && obj_pos.y > center.y) {
    collision_directions.emplace_back("bottom");
  }

  return collision_directions;
}

}  // namespace tank_hero