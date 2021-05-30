#include QMK_KEYBOARD_H
#include "common.h"

bool is_jp_mode(void) {
  return biton32(default_layer_state) == _QWERTY_JP;
}
