#include QMK_KEYBOARD_H
#include "common.h"

user_config_t user_config;

void init_user_config() {
  user_config.raw = eeconfig_read_user();
}

bool is_jis_mode(void) {
  return user_config.is_jis_mode;
}

void set_jis_mode(bool is_jis_mode) {
  user_config.is_jis_mode = is_jis_mode;
  eeconfig_update_user(user_config.raw);
}

bool is_command_mode(void) {
  return user_config.is_command_mode;
}

void set_command_mode(bool is_command_mode) {
  user_config.is_command_mode = is_command_mode;
  eeconfig_update_user(user_config.raw);
}
