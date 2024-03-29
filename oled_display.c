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

/*
   How to Customize

   $ make helix/rev3_4rows:YOUR_KEYMAP:clean
   $ cp keyboards/helix/rev3_4rows/oled_display.c keyboards/helix/rev3_4rows/keymaps/YOUR_KEYMAP

   $ edit keyboards/helix/rev3_4rows/keymaps/YOUR_KEYMAP/oled_display.c
   $ make helix/rev3_4rows:YOUR_KEYMAP
   $ make helix/rev3_4rows:YOUR_KEYMAP:flash
 */

#include QMK_KEYBOARD_H
#include "lib/common.h"

#ifdef OLED_DRIVER_ENABLE

void render_status(void) {

  static const char lang_logo[][2][4] PROGMEM = {
    {
      {0x95, 0x96, 0x97, 0x00},
      {0xb5, 0xb6, 0xb7, 0x00}
    },
    {
      {0x98, 0x99, 0x9a, 0x00},
      {0xb8, 0xb9, 0xba, 0x00}
    }
  };

  static const char mod_logo[][3] PROGMEM = {
    [_GUI] = {0xd7, 0xd8, 0x00},
    [_CTRL] = {0xd9, 0xda, 0x00},
    [_ALT] = {0xdb, 0xdc, 0x00},
    [_SHIFT] = {0xdd, 0xde, 0x00},
  };

  static const char os_logo[][2][3] PROGMEM = {
    [_MAC] = {
      {0x9b, 0x9c, 0x00},
      {0xbb, 0xbc, 0x00}
    },
    [_WINDOWS] = {
      {0x9d, 0x9e, 0x00},
      {0xbd, 0xbe, 0x00}
    },
    [_GNOME] = {
      {0x9f, 0xd5, 0x00},
      {0xbf, 0xd6, 0x00}
    },
  };

  oled_write_P(!is_jis_mode() ? lang_logo[0][0] : lang_logo[1][0], false);
  oled_write_P(PSTR(" "), false);

  // Host Keyboard LED Status
  uint8_t mod_state = get_mods();
  oled_write_P(mod_state & MOD_MASK_GUI ? mod_logo[_GUI] : PSTR("  "), false);
  oled_write_P(mod_state & MOD_MASK_CTRL ? mod_logo[_CTRL] : PSTR("  "), false);
  oled_write_P(mod_state & MOD_MASK_ALT ? mod_logo[_ALT] : PSTR("  "), false);
  oled_write_P(mod_state & MOD_MASK_SHIFT ? mod_logo[_SHIFT] : PSTR("  "), false);

  oled_write_P(PSTR("\n"), false);
  oled_write_P(!is_jis_mode() ? lang_logo[0][1] : lang_logo[1][1], false);
  oled_write_P(PSTR(" "), false);

  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
      case _QWERTY:
          oled_write_P(PSTR("Default\n"), false);
          break;
      case _LOWER:
          oled_write_P(PSTR("Lower\n"), false);
          break;
      case _RAISE:
          oled_write_P(PSTR("Raise\n"), false);
          break;
      case _ADJUST:
          oled_write_P(PSTR("Adjust\n"), false);
          break;
      case _CONFIG:
          oled_write_P(PSTR("Config\n"), false);
          break;
      case _MIDI:
          oled_write_P(PSTR("MIDI\n"), false);
          break;
      default:
          // Or use the write_ln shortcut over adding '\n' to the end of your string
          oled_write_ln_P(PSTR("Undefined\n"), false);
  }

  oled_write_P(PSTR(" "), false);
  oled_write_P(os_logo[get_os_mode()][0], false);
  oled_write_P(PSTR(" "), false);

  // Host Keyboard Custom Mod Status
  oled_write_P(PSTR("Mod  : "), false);
  oled_write_P(mod_logo[get_custom_mod_key()], false);
  oled_write_P(PSTR("\n"), false);

  oled_write_P(PSTR(" "), false);
  oled_write_P(os_logo[get_os_mode()][1], false);
  oled_write_P(PSTR(" "), false);

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
  oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR\n") : PSTR("   \n"), false);
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void render_rgbled_status(void) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
    snprintf(buf, sizeof(buf), "LED %02d: HSV(%02d,%02d,%02d)",
      rgblight_get_mode(),
      rgblight_get_hue() / RGBLIGHT_HUE_STEP,
      rgblight_get_sat() / RGBLIGHT_SAT_STEP,
      rgblight_get_val() / RGBLIGHT_VAL_STEP);
    oled_write(buf, false);
  }
#endif
}

void oled_task_user(void) {
  if(is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    render_rgbled_status();
  }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_left()) {
    return OLED_ROTATION_180;
  }
  return rotation;
}

#endif
