/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "lib/common.h"
#include "lib/qmk-translate-ansi-to-jis/translate_ansi_to_jis.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  ADJUST = SAFE_RANGE,
  MOD_US,
  MOD_JP
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define RGB_MDI RGB_MOD
#define RGB_MDD RGB_RMOD
#define MOD_MAC LAG_NRM
#define MOD_WIN LAG_SWP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS, \
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RALT, \
    ADJUST , KC_CAPS, KC_APP , KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_ENT , RAISE  , KC_RSFT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT),

  [_LOWER] = LAYOUT( \
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV , \
    _______, _______, _______, _______, KC_MINS, KC_LBRC,                   KC_RBRC, KC_EQL , _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ESC , KC_BSPC, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END ),

  [_RAISE] = LAYOUT( \
    KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, \
    _______, _______, _______, _______, KC_UNDS, KC_LCBR,                   KC_RCBR, KC_PLUS, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ESC , KC_DEL , _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END ),

  [_ADJUST] = LAYOUT( \
    _______, _______, _______, _______, MOD_US , MOD_JP ,                   MOD_MAC, MOD_WIN, _______, _______, EEP_RST, RESET  , \
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, RGB_MDI, RGB_HUI, RGB_SAI, RGB_VAI, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MDD, RGB_HUD, RGB_SAD, RGB_VAD)
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* Left side encoder */
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  } else if (index == 1) { /* Right side encoder */
    if (clockwise) {
      tap_code(KC_DOWN);
    } else {
      tap_code(KC_UP);
    }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (is_jp_mode() && !process_record_user_taj(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case MOD_US:
      if (record->event.pressed) {
        set_jp_mode(false);
      }
      return false;
    case MOD_JP:
      if (record->event.pressed) {
        set_jp_mode(true);
      }
      return false;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      return false;
  }
  return true;
}

void keyboard_post_init_user(void) {
  init_user_config();
}


/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
