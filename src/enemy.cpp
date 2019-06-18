#include "enemy.h"

using namespace godot;

void Enemy::_register_methods() {  
  register_method("_process", &Enemy::_process);
  register_method("_ready", &Enemy::_ready);
  register_method("_on_visibility_screen_exited", &Enemy::_on_visibility_screen_exited);
  register_property<Enemy, int>("min_speed", &Enemy::min_speed, 150);
  register_property<Enemy, int>("max_speed", &Enemy::max_speed, 250);
  // register_signal<Simple>((String)"button_pressed", "node", GODOT_VARIANT_TYPE_OBJECT,
  //                           "data", GODOT_VARIANT_TYPE_STRING);
  register_signal<Enemy>((char *)"hit");
}

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::_init() {
  min_speed = 150;
  max_speed = 250;

  // init random number generator
  std::random_device rd;
  rand = std::mt19937{rd()};
  Godot::print("In init!");
}

void Enemy::_ready() {
  animated_sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
  collider = cast_to<CollisionShape2D>(get_node("CollisionShape2D"));
  // Should check for null
  // get random animation. get index from 0 to 2
  std::uniform_int_distribution<> dis(0, 2);
  int random_index = dis(rand);
  animated_sprite->set_animation(mob_types[random_index]);
  animated_sprite->play();

}

void Enemy::_process(float delta) {
}

void Enemy::_on_visibility_screen_exited() {
  queue_free();
}

