#include QMK_KEYBOARD_H
#include "common.h"

user_config_t user_config;

void init_user_config() {
  user_config.raw = eeconfig_read_user();
}

bool is_jp_mode(void) {
  return user_config.is_jp_mode;
}

void set_jp_mode(bool is_jp_mode) {
  user_config.is_jp_mode = is_jp_mode;
  eeconfig_update_user(user_config.raw);
}
