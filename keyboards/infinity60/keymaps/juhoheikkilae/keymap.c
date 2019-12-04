#include QMK_KEYBOARD_H
#include "led_controller.h"

#define _BASE 0

enum custom_keycodes {
  COMMENT = SAFE_RANGE,
  UNCOMMENT
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Bksp|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * |-----------------------------------------------------------'
     * |     |Alt|Gui  |         Space         |Alt  |Gui|   |     |
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT_60_ansi_split_bs_rshift(
      KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS, KC_GRV, \
      KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC, \
      MT(MOD_LCTL, KC_ESC),KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,  \
      KC_LSPO,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSPC,MO(1), \
      COMMENT,  KC_LALT,KC_LGUI,          KC_SPC,                KC_RALT,KC_RGUI,UNCOMMENT, RGUI(KC_L)),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     * |     |Alt|Gui  |         Space         |Alt  |Gui|   |     |
     * `-----------------------------------------------------------'
     */
    [1] = LAYOUT_60_ansi_split_bs_rshift(
      KC_PWR, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,   \
      KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS, KC_UP, KC_TRNS, KC_DEL,      \
      KC_TRNS,KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,KC_TRNS,KC_PAST,KC_PSLS,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,KC_PENT,            \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PPLS,KC_PMNS,KC_END, KC_PGDN,KC_DOWN,KC_TRNS,KC_TRNS,            \
      KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
};

// uint8_t led_all[63] = {
//     11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,
//      28,31,32,33,34,35,36,37,38,41,42,43,44,45,
//      46,47,48,51,52,53,54,55,56,57,58,61,62,
//       63,64,65,66,67,68,71,72,73,74,75,76,77,
//      78,81,82,83,84,86,87
// };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COMMENT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("kc"));
      }
      break;
    case UNCOMMENT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("ku"));
      }
  }
  return true;
}

uint8_t led_all[63] = {
    11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,
     28,31,32,33,34,35,36,37,38,41,42,43,44,45,
     46,47,48,51,52,53,54,55,56,57,58,61,62,
      63,64,65,66,67,68,71,72,73,74,75,76,77,
      81,82,83,84,85
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    led_controller_init();

    write_led_page(_BASE, led_all, 63);
    chThdSleepMilliseconds(10);

    chMBPost(&led_mailbox, _BASE, TIME_IMMEDIATE);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
