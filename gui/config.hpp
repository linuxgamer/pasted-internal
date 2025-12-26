#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_keyboard.h>

#include "../vec.hpp"

struct button {
  int button;
  bool waiting = false;
};

struct Aim {
  bool master = true;

  bool auto_shoot = false;

  enum class TargetType {
    FOV,
    DISTANCE,
    LEAST_HEALTH,
    MOST_HEALTH
  } target_type = TargetType::FOV;
  
  bool silent = true;
  
  struct button key = {.button = -SDL_BUTTON_X1};
  bool use_key = false;
  
  float fov = 6;
  bool draw_fov = true;
  
  bool auto_scope = false;
  bool auto_unscope = false;
  bool scoped_only = true;
  
  bool ignore_friends = false;
};

struct Esp {
  bool master = true;

  struct Player {
    RGBA_float enemy_color = {.r = 1, .g = 0.2, .b = 0, .a = 1};
    RGBA_float team_color = {.r = 1, .g = 1, .b = 1, .a = 1};
    RGBA_float friend_color = {.r = 0, .g = 1, .b = 0.2, .a = 1};
    
    bool box = true;
    bool health_bar = true;    
    bool name = true;
    int hb_pos = 0;
    const char* hb_pos_items[2] = { "Left", "Right" };
    
    struct Flags {
      bool target_indicator = true;
      bool friend_indicator = true;
      int pos = 0;
      const char* pos_items[2] = { "Left", "Right" };
    } flags;
    
    bool friends = true;
    bool team = false;
  } player;

  struct Pickup {
    bool box = false;    
    bool name = true;
  } pickup;

  struct Intelligence {
    bool box = true;    
    bool name = true;
  } intelligence;
  
  struct Buildings {
    bool box = true;
    bool health_bar = true;    
    bool name = true;

    bool team = false;
  } buildings;
};

struct Visuals {

  struct Removals {
    bool scope = true;
    bool zoom = false;
  } removals;
  
  struct Thirdperson {
    struct button key = {.button = SDL_SCANCODE_LALT};
    bool enabled = true;
    float z = 150.0f;
    float y = 20.0f;
    float x = 0; 
  } thirdperson;
  
  bool override_fov = true;
  float custom_fov = 100;
};

struct Misc {

  struct Movement {
    bool bhop = true;
    bool no_push = true;
  } movement;

  struct Automatization {
    bool autovaccinator = false;
    bool autobackstab = false;
  } automatization;

  struct Exploits {
    bool bypasspure = true;
    bool no_engine_sleep = false;
  } exploits;
};

struct Navbot {
  bool master = false;

  bool walk = false;
  
  bool look_at_path = false;
  float look_smoothness = 50;

  bool do_objective = false;
};

struct Debug {
  int font_height = 16;
  int font_weight = 400;
  bool debug_render_all_entities = false;
  bool debug_draw_navbot_path = false;
  bool debug_draw_navmesh = false;
  bool debug_draw_navbot_goal = false;
  bool debug_draw_navbot_current_area = false;
  bool debug_draw_navbot_next_area = false;
};

struct Config {
  Aim aimbot;
  Esp esp;
  Visuals visuals;
  Misc misc;
  Navbot navbot;
  Debug debug;
};

inline static Config config;


static bool is_button_down(struct button button) {
  if (button.button >= 0) {
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
  
    if (keys[button.button] == 1)
      return true;

    return false;
  } else {
    Uint32 mouse_state = SDL_GetMouseState(NULL, NULL);

    if (mouse_state & SDL_BUTTON(-button.button))
      return true;

    return false;
  }  

  return false;
}

#endif
