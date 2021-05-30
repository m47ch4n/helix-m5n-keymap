#pragma once

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _QWERTY_JP,
  _LOWER,
  _LOWER_JP,
  _RAISE,
  _RAISE_JP,
  _ADJUST
};

bool is_jp_mode(void);