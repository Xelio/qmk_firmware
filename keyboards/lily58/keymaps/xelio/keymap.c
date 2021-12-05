#include QMK_KEYBOARD_H
#include "led.h"
#include "host.h"
//#include "tap_dance.c"

// Combo
enum combos {
  CB_BKSP,
  CB_DEL,
  CB_CTRLALTDEL,
  CB_CTRLALTINS,
  CB_COMBO_LENGTH
};
uint16_t COMBO_LEN = CB_COMBO_LENGTH;

const uint16_t PROGMEM bspc_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM ctrlaltdel_combo[] = {KC_GESC, KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM ctrlaltins_combo[] = {KC_GESC, KC_1, KC_3, COMBO_END};

combo_t key_combos[] = {
  [CB_BKSP] = COMBO(bspc_combo, KC_BSPC),
  [CB_DEL] = COMBO(del_combo, KC_DEL),
  [CB_CTRLALTDEL] = COMBO(ctrlaltdel_combo, LCA(KC_DEL)),
  [CB_CTRLALTINS] = COMBO(ctrlaltins_combo, LCA(KC_INS)),
};

// Marco
enum custom_keycodes {
    CLR_LY = SAFE_RANGE,
    MC_UNDO, 
    MC_CUT, 
    MC_COPY, 
    MC_PASTE
};


enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * LT(0,KC_SLSH) refer to process_record_user(...)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC`~|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -_  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;: |RShift|
 * |------+------+------+------+------+------|   =+  |    |   '"  |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,< |   .> |/?  \||RCtrl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |AltGr | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,  KC_2,  KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,   KC_0,          KC_BSPC, \
  KC_TAB,   KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,          KC_MINS, \
  KC_LSFT,  KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,       KC_RSFT, \
  KC_LCTL,  KC_Z,  KC_X,  KC_C,    KC_V,    KC_B, KC_EQL,   KC_QUOT,  KC_N,    KC_M,    KC_COMM, KC_DOT, LT(0,KC_SLSH), KC_RCTL, \
                          KC_LGUI, KC_LALT, TT(_LOWER), KC_SPC, KC_ENT, TT(_RAISE), KC_RALT, KC_RGUI \
),

 /* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  Up  |      |      |                    |      | ins  | pgup | home | PSCR | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | HSft | Left | Down |Right |      |-------.    ,-------|BackSP| del  | pgdn | end  | SLCK |      |
 * |------+------+------+------+------+------|  CAPS |    | NUMLCK|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |      |-------|    |-------|      |_MOUSE|      |      | PAUS |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /Enter  /       \Space \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
  CLR_LY,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,      KC_F8,   KC_F9,   KC_F10,  KC_F11,\
  _______, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,                   XXXXXXX, KC_INS,     KC_PGUP, KC_HOME, KC_PSCR, KC_F12, \
  _______, KC_EXLM, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                   KC_BSPC, KC_DEL,     KC_PGDN, KC_END,  KC_SLCK, _______, \
  _______, MC_UNDO, MC_CUT, MC_COPY, MC_PASTE, XXXXXXX, KC_CAPS, KC_NLCK, XXXXXXX, TT(_MOUSE), XXXXXXX, XXXXXXX, KC_PAUS, _______, \
                              _______, _______, _______, KC_ENT, KC_SPC,  _______, _______, _______\
),
 
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   &  |                    |   -  |  7   |   8  |   9  |   \  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |(    <|)    >|  \|  |-------.    ,-------|   =+ |  4   |   5  |   6  |   .  |      |
 * |------+------+------+------+------+------|   `~  |    | CALC  |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   _  |-------|    |-------|   +  |  1   |   2  |   3  |   *  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Enter  /       \Space \  |RAISE |   0  | RGUI |
 *                   |      |      |      |/       /         \      \ |      | AltGr|      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  CLR_LY,  KC_F1,   KC_F2,   KC_F3,         KC_F4,         KC_F5,                       KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10,  KC_F11, \
  _______, KC_EXLM, KC_AT,   KC_LCBR,       KC_RCBR,       KC_AMPR,                     KC_PMNS, KC_7,  KC_8,  KC_9,  KC_PSLS, KC_F12, \
  _______, KC_HASH, KC_DLR,  LT(0,KC_LPRN), LT(0,KC_RPRN), KC_BSLS,                     KC_EQL,  KC_4,  KC_5,  KC_6,  KC_DOT,  _______, \
  _______, KC_PERC, KC_CIRC, KC_LBRC,       KC_RBRC,       KC_UNDS, KC_GRAVE,  KC_CALC, KC_PPLS, KC_1,  KC_2,  KC_3,  KC_PAST, _______, \
                                        _______, _______, _______,    KC_ENT, KC_SPC,    _______, RALT_T(KC_0),  _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |  V+  | Br+  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  <<  | play |  >>  |  V-  | Br-  |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      | Mute |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  CLR_LY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_BRIU,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLD, KC_BRID,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* MOUSE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY| XXXX | XXXX | XXXX | XXXX | XXXX |                    | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | XXXX | XXXX |MS_BT3| MS_U |MS_W_U| XXXX |                    | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | XXXX |MS_BT2| MS_L | MS_D | MS_R | XXXX |-------.    ,-------| XXXX | XXXX | XXXX | XXXX | LGUI | XXXX |
 * |------+------+------+------+------+------|  XXXX |    | XXXX  |------+------+------+------+------+------|
 * | XXXX | XXXX |MS_W_L|MS_W_R|MS_W_D| XXXX |-------|    |-------| XXXX |Trans |LShift|LCTRL | LAlt | XXXX |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | XXXX | XXXX |XXXX  | / MS_BT1/       \ XXXX \  |Trans | XXXX | XXXX |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_MOUSE] = LAYOUT(
  CLR_LY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_BTN3, KC_MS_U, KC_WH_U,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_R, KC_WH_D,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, XXXXXXX, KC_TRNS, XXXXXXX, XXXXXXX
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0,KC_SLSH):
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_SLSH);
      } else if (record->event.pressed) {
        tap_code16(KC_BSLS); // Intercept hold function to send backslash
      }
      return false;

    case LT(0,KC_LPRN):
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_LPRN);
      } else if (record->event.pressed) {
        tap_code16(KC_LABK); // Intercept hold function to send backslash
      }
      return false;

    case LT(0,KC_RPRN):
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_RPRN);
      } else if (record->event.pressed) {
        tap_code16(KC_RABK); // Intercept hold function to send backslash
      }
      return false;

    case MC_UNDO:
      if (record->tap.count && record->event.pressed) {
        tap_code16(C(KC_Z));
        return false;
      }
      break;
	  
    case MC_CUT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(C(KC_X));
        return false;
      }
      break;
	  
    case MC_COPY:
      if (record->tap.count && record->event.pressed) {
        tap_code16(C(KC_C));
        return false;
      }
      break;
	  
    case MC_PASTE:
      if (record->tap.count && record->event.pressed) {
        tap_code16(C(KC_V));
        return false;
      }
      break;
	
    case CLR_LY:
      layer_clear();
    case KC_GESC:
      if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        tap_code16(KC_CAPS);
      }
      if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {
        tap_code16(KC_NLCK);
      }
      if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        tap_code16(KC_SLCK);
      }
      break;
    }
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    // set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}