#include "main.h"

using namespace godot;

void Main::_register_methods() {  
  register_method("_process", &Main::_process);
  register_method("_ready", &Main::_ready);
  register_method("_init", &Main::_init);
  register_method("_on_start_timer_timeout", &Main::_on_start_timer_timeout);
  register_method("_on_score_timer_timeout", &Main::_on_score_timer_timeout);
  register_method("_on_mob_timer_timeout", &Main::_on_mob_timer_timeout);
  register_method("new_game", &Main::new_game);
  register_method("game_over", &Main::game_over);
  register_signal<Main>((char *)"start_game");
  register_property<Main, Ref<PackedScene>>("Mob", &Main::mob, nullptr);
}

Main::Main() {}

Main::~Main() {}

void Main::_init() {

  // init random number generator

  this->_score = 0;
}

void Main::_ready() {
  // Should check for null
  this->start_timer= cast_to<Timer>(get_node("StartTimer"));
  this->score_timer = cast_to<Timer>(get_node("ScoreTimer"));
  this->mob_timer = cast_to<Timer>(get_node("MobTimer"));
  this->mob_path = cast_to<Path2D>(get_node("MobPath"));
  this->mob_spawn_location = cast_to<PathFollow2D>(mob_path->get_node("MobSpawnLocation"));
  this->hud = cast_to<Hud>(get_node("HUD"));
  this->music = cast_to<AudioStreamPlayer>(get_node("Music"));
  this->death_sound = cast_to<AudioStreamPlayer>(get_node("DeathSound"));

}

void Main::_process(float delta) {
}

void Main::game_over() {
  mob_timer->stop();
  score_timer->stop();
  music->stop();
  death_sound->play();
  hud->show_game_over();
}

void Main::new_game() {
  this->_score = 0;

  music->play();

  Player *player = cast_to<Player>(get_node("Player"));
  Position2D *start_position = cast_to<Position2D>(get_node("StartPosition"));
  player->start(start_position->get_position());

  hud->update_score(_score);
  hud->show_message("Get Ready!");

  start_timer->start();
}

void Main::_on_start_timer_timeout() {
  mob_timer->start();
  score_timer->start();
}


void Main::_on_score_timer_timeout() {
  _score++;
  hud->update_score(_score);
}

void Main::_on_mob_timer_timeout() {
  std::uniform_int_distribution<int> dis(0, RAND_MAX);
  int random_int = dis(rand);
  mob_spawn_location->set_offset(random_int);

  RigidBody2D *mob_instance = cast_to<RigidBody2D>(mob->instance());

  add_child(mob_instance);

  float direction = mob_spawn_location->get_rotation() + (M_PI / 2);

  mob_instance->set_position(mob_spawn_location->get_position());

  direction += rand_range((-M_PI / 4), (M_PI / 4));
  mob_instance->set_rotation(direction);

  mob_instance->set_linear_velocity(Vector2{rand_range(150.0f, 250.0f), 0}.rotated(direction));

  hud->connect("start_game", mob_instance, "_on_start_game");
}

float Main::rand_range(float min, float max) {
  std::uniform_real_distribution<float> dis(min, max);
  return dis(rand); 
}
