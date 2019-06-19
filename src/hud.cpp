#include "hud.h"

using namespace godot;

void Hud::_register_methods() {  
  register_method("_process", &Hud::_process);
  register_method("_ready", &Hud::_ready);
  register_method("show_game_over", &Hud::show_game_over);
  register_method("show_message", &Hud::show_message);
  register_method("start", &Hud::start);
  register_method("_on_start_button_pressed", &Hud::_on_start_button_pressed);
  register_method("_on_message_timer_timeout", &Hud::_on_message_timer_timeout);
  register_signal<Hud>("game_over");
  register_signal<Hud>("start_game");
  // register_signal<Simple>((String)"button_pressed", "node", GODOT_VARIANT_TYPE_OBJECT,
  //                           "data", GODOT_VARIANT_TYPE_STRING);
}

Hud::Hud() {}

Hud::~Hud() {}

void Hud::_init() {
}

void Hud::_ready() {
  message_timer = cast_to<Timer>(get_node("MessageTimer"));
  score_label = cast_to<Label>(get_node("ScoreLabel"));
  message_label = cast_to<Label>(get_node("MessageLabel"));
  start_button = cast_to<Button>(get_node("StartButton"));
}

void Hud::_process(float delta) {
}

void Hud::start(Vector2 pos) {
}

void Hud::show_message(String text) {
  message_timer->stop();
  message_label->set_text(text);
  message_label->show();
  message_timer->start();
}

void Hud::show_game_over() {
  this->show_message("Game Over");
  this->show_message("Dodge the\nCreeps!");

  this->message_timer->stop();
  this->start_button->show();
}

void Hud::update_score(int score) {
  score_label->set_text(String::num_int64(score));
}

void Hud::_on_start_button_pressed() {
  start_button->hide();
  emit_signal("start_game");
}

void Hud::_on_message_timer_timeout() {
  this->message_label->hide();
}
