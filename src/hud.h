#ifndef HUD_H
#define HUD_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <Label.hpp>
#include <Button.hpp>
#include <Timer.hpp>
#include <thread>
#include <chrono>
#include <string>

namespace godot {
  class Hud : public CanvasLayer {
    GODOT_CLASS(Hud, CanvasLayer)

    public:
    Hud();
    ~Hud();

    static void _register_methods();
    void _init();
    void _process(float delta);
    void _ready();
    void start(Vector2 pos);
    void show_message(String text);
    void show_game_over();
    void update_score(int score);
    void _on_start_button_pressed();
    void _on_message_timer_timeout();

    private:
    Label *score_label;
    Label *message_label;
    Button *start_button;
    Timer *message_timer;
  };
}


#endif
