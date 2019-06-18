#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <RigidBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Transform.hpp>
#include <PackedScene.hpp>
#include <random>
#include <Timer.hpp>
#include "player.h"
#include <Position2D.hpp>
#include <Path2D.hpp>
#include <PathFollow2D.hpp>
#include <cmath>
#include "hud.h"

namespace godot {
  class Main : public Node {
    GODOT_CLASS(Main, Node)

    public:
     Ref<PackedScene> mob;

    Main();
    ~Main();

    static void _register_methods();
    void _init();
    void _process(float delta);
    void _ready();
    void game_over();
    void new_game();

    void _on_start_timer_timeout();
    void _on_score_timer_timeout();
    void _on_mob_timer_timeout();

    private:
    Timer *start_timer;
    Timer *score_timer;
    Timer *mob_timer;
    Path2D *mob_path;
    PathFollow2D *mob_spawn_location;
    int _score;
    std::mt19937 rand;
    float rand_range(float min, float max);
    Hud *hud;
  };
}

#endif
