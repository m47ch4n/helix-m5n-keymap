#pragma once

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

typedef union {
  uint32_t raw;
  struct {
    bool is_jis_mode: 1;
  };
} user_config_t;

void init_user_config(void);
bool is_jis_mode(void);
void set_jis_mode(bool is_jis_mode);
