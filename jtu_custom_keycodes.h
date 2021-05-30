// Keycodes to use jis keycode in us keymap

#pragma once

enum jtu_custom_keycodes {
  JU_2 = SAFE_RANGE,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS,
  JU_AT,
  JU_CIRC,
  JU_AMPR,  
  JU_ASTR,
  JU_LPRN,
  JU_RPRN,
  JU_PIPE,
  JTU_SAFE_RANGE
};

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record);
