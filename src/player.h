#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <Input.hpp>
#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>
#include <Transform.hpp>
#include <algorithm>
#include <string>
#include <String.hpp>
#include <Array.hpp>
#include <OS.hpp>
#include <Vector2.hpp>

namespace godot {
  class Player : public Area2D {
    GODOT_CLASS(Player, Area2D)

    public:
    int speed;
    Player();
    ~Player();

    static void _register_methods();
    void _init();
    void _process(float delta);
    void _ready();
    void _on_body_entered();
    void start(Vector2 pos);
  
    private:
    Vector2 screen_size;
    AnimatedSprite *animated_sprite;
    CollisionShape2D *collider;

  };
}


#endif
