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
#include "lib/a2j/translate_ansi_to_jis.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  OUT_TOG = SAFE_RANGE,
  CMD_TOG,
  COMMAND,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define CONFIG MO(_CONFIG)
#define RGB_MDI RGB_MOD
#define RGB_MDD RGB_RMOD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS, \
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RALT, \
    COMMAND, CONFIG , KC_ESC , KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_ENT , RAISE  , KC_RSFT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT),

  [_LOWER] = LAYOUT( \
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV , \
    _______, _______, _______, _______, KC_MINS, KC_LBRC,                   KC_RBRC, KC_EQL , _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ESC , KC_BSPC, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END ),

  [_RAISE] = LAYOUT( \
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV , \
    _______, _______, _______, _______, KC_MINS, KC_LBRC,                   KC_RBRC, KC_EQL , _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ESC , KC_DEL , _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END ),

  [_ADJUST] = LAYOUT( \
    KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
    _______, _______, _______, _______, KC_UNDS, KC_LCBR,                   KC_RCBR, KC_PLUS, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

  [_CONFIG] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CAPS, KC_PSCR, KC_PAUS, XXXXXXX, XXXXXXX, EEP_RST, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_NLCK, KC_INS , KC_DEL , XXXXXXX, XXXXXXX, RESET  , \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_SLCK, KC_APP , RGB_MDI, RGB_HUI, RGB_SAI, RGB_VAI, \
    CMD_TOG, CONFIG , OUT_TOG, XXXXXXX, XXXXXXX, XXXXXXX, MI_TOG , XXXXXXX, XXXXXXX, RGB_TOG, RGB_MDD, RGB_HUD, RGB_SAD, RGB_VAD),

  [_MIDI] = LAYOUT( \
    MI_C   , MI_F   , MI_As  , MI_Ds_1, MI_Gs_1, MI_Cs_2,                   MI_Gs_2, MI_Ds_2, MI_As_1, MI_F_1 , MI_C_1 , MI_G   , \
    MI_Cs  , MI_Fs  , MI_B   , MI_E_1 , MI_A_1 , MI_D_2 ,                   MI_G_2 , MI_D_2 , MI_A_1 , MI_E_1 , MI_B   , MI_Fs  , \
    MI_D   , MI_G   , MI_C_1 , MI_F_1 , MI_As_1, MI_Ds_2,                   MI_Fs_2, MI_Cs_2, MI_Gs_1, MI_Ds_1, MI_As  , MI_F   , \
    MI_Ds  , MI_Gs  , MI_Cs_1, MI_Fs_1, MI_B_1 , MI_E_2 , MI_TOG , XXXXXXX, MI_F_2 , MI_C_2 , MI_G_1 , MI_D_1 , MI_A   , MI_E   )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case OUT_TOG:
      if (record->event.pressed) {
        set_jis_mode(!is_jis_mode());
      }
      return false;
    case MI_TOG:
      if (!record->event.pressed) {
        layer_invert(_MIDI);
      }
      return true;
    case CMD_TOG:
      if (!record->event.pressed) {
        set_command_mode(!is_command_mode());
      }
      return false;
    case COMMAND:
      if (record->event.pressed) {
        register_code(is_command_mode() ? KC_LGUI : KC_LCTL);
      } else {
        unregister_code(is_command_mode() ? KC_LGUI : KC_LCTL);
      }
      return false;
  }

  if (!is_jis_mode()) {
    return true;
  }

  return process_record_user_a2j(keycode, record);
}

void keyboard_post_init_user(void) {
  init_user_config();
}
