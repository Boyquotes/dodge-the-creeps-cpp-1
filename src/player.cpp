#include "player.h"

using namespace godot;

void Player::_register_methods() {  
  register_method("_process", &Player::_process);
  register_method("_ready", &Player::_ready);
  register_method("_on_body_entered", &Player::_on_body_entered);
  register_property<Player, int>("speed", &Player::speed, 0);
  // register_signal<Simple>((String)"button_pressed", "node", GODOT_VARIANT_TYPE_OBJECT,
  //                           "data", GODOT_VARIANT_TYPE_STRING);
  register_signal<Player>((char *)"hit");
}

Player::Player() {}

Player::~Player() {}

void Player::_init() {
  speed = 400;
  Godot::print("In init!");
}

void Player::_ready() {
  Vector2 v{480, 720};
  OS *os = OS::get_singleton();
  os->set_window_size(v);
  Godot::print(os->get_screen_size());
  screen_size = get_viewport_rect().get_size();
  String screen = String("Screen size is x: {0} y: {1}")
    .format(Array::make(screen_size.x, screen_size.y));
  Godot::print(screen);
  animated_sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
  collider = cast_to<CollisionShape2D>(get_node("CollisionShape2D"));
  // Should check for null

  //hide();
}

void Player::_process(float delta) {
  Vector2 velocity{0, 0};

  Input *i = Input::get_singleton();
  if (i->is_action_pressed("ui_right")) {
    velocity.x += 1;
  }

  if (i->is_action_pressed("ui_left")) {
    velocity.x -= 1;
  }

  if (i->is_action_pressed("ui_down")) {
    velocity.y += 1;
  }

  if (i->is_action_pressed("ui_up")) {
    velocity.y -= 1;
  }

  if (velocity.length() > 0) {
    velocity = velocity.normalized() * speed;

    if (animated_sprite != nullptr) {
      animated_sprite->play();
    }
  } else {
    if (animated_sprite != nullptr) {
      animated_sprite->stop();
    }
  }

  Vector2 position = this->get_position();
  position += velocity * delta;
  position.x = std::clamp(position.x, 0.0f, screen_size.x);
  position.y = std::clamp(position.y, 0.0f, screen_size.y);

  this->set_position(position);

  if (velocity.x != 0) {
    animated_sprite->set_animation("right");
    animated_sprite->set_flip_v(false);
    // see note below about boolean assignment
    animated_sprite->set_flip_h(velocity.x < 0);
  } else if (velocity.y != 0) {
    animated_sprite->set_animation("up");
    animated_sprite->set_flip_v(velocity.y > 0);
  }
}

void Player::_on_body_entered() {
  Godot::print("entered body!");
  hide();
  emit_signal("hit");
  // disabling the area's collision shape can cause an error if it happens in the middle
  // of the engine's collision processing. Using set_deffered() allows us to ahve Godot wait to
  // disable the shape until it's safe to do so
  collider->set_deferred("disabled", true);
}

void Player::start(Vector2 pos) {
  this->set_position(pos);
  show();
  collider->set_disabled(false);
}
