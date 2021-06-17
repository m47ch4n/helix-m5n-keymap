#pragma once

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _CONFIG,
  _MIDI
};

typedef enum {
  _GUI = 0,
  _CTRL,
  _ALT,
  _SHIFT
} custom_mod_key_t;

typedef enum {
  _MAC,
  _WINDOWS,
  _GNOME
} os_mode_t;

typedef union {
  uint32_t raw;
  struct {
    bool is_jis_mode: 1;
    uint8_t custom_mod_key: 2;
    uint8_t os_mode: 2;
  };
} user_config_t;

void init_user_config(void);

bool is_jis_mode(void);
void set_jis_mode(bool is_jis_mode);

custom_mod_key_t get_custom_mod_key(void);
void set_custom_mod_key(custom_mod_key_t custom_mod_key);

os_mode_t get_os_mode(void);
void set_os_mode(os_mode_t os_mode);