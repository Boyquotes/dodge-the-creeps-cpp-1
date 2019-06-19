#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Transform.hpp>
#include <random>
#include <String.hpp>

namespace godot {
  class Enemy : public RigidBody2D {
    GODOT_CLASS(Enemy, RigidBody2D)

    public:
    int min_speed = 150;
    int max_speed = 250;

    Enemy();
    ~Enemy();

    static void _register_methods();
    void _init();
    void _process(float delta);
    void _ready();
    void _on_visibility_screen_exited();
    void _on_start_game();

    private:
    String mob_types[3] = {"walk", "swim", "fly"};
    std::mt19937 rand;
    AnimatedSprite *animated_sprite;
    CollisionShape2D *collider;
  };
}

#endif
