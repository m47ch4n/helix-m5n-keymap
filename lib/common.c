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

custom_mod_key_t get_custom_mod_key(void) {
  return user_config.custom_mod_key;
}

void set_custom_mod_key(custom_mod_key_t custom_mod_key) {
  user_config.custom_mod_key = custom_mod_key;
  eeconfig_update_user(user_config.raw);
}

os_mode_t get_os_mode(void) {
  return user_config.os_mode;
}

void set_os_mode(os_mode_t os_mode) {
  user_config.os_mode = os_mode;
  eeconfig_update_user(user_config.raw);
}
