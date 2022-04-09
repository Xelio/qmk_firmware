#include QMK_KEYBOARD_H
#include "led.h"
#include "host.h"
//#include "tap_dance.c"


// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#define SFT_QUOT RSFT_T(KC_QUOT)

#define RALT_BSPC RALT_T(KC_BSPC)
#define RALT_0 RALT_T(KC_0)
#define RGUI_0 RGUI_T(KC_0)
#define DOT_SFT LT(0,KC_DOT)

// Hold for number
#define W_H1 LT(0,KC_W)
#define E_H2 LT(0,KC_E)
#define R_H3 LT(0,KC_R)
#define X_H4 LT(0,KC_X)
#define C_H5 LT(0,KC_C)
#define V_H6 LT(0,KC_V)
#define U_H7 LT(0,KC_U)
#define I_H8 LT(0,KC_I)
#define O_H9 LT(0,KC_O)
#define P_H0 LT(0,KC_P)

// Layer
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
};

// Combo
enum combos {
  CB_BSPC,
  CB_DEL,
  CB_BSPC_LOWER,
  CB_DEL_LOWER,
  CB_BSPC_OTHER,
  CB_DEL_OTHER,
  
  CB_LEFT,
  CB_RIGHT,
  CB_LEFT_LOWER,
  CB_RIGHT_LOWER,
  
  CB_CTRLALTDEL,
  CB_CTRLALTINS,
  
  CB_COMBO_LENGTH
};

// Macro
enum custom_keycodes {
  CLR_LY = SAFE_RANGE,
  LOWER_4,
  LOWER_5,
  LOWER_6,
  
  MC_SFLK,
  
  MC_UNDO,
  MC_CUT,
  MC_COPY,
  MC_PASTE,
  
  MCC_BSPC,
  MCC_BSDL,
  MCC_DEL,
  
  LT_UDQU,
};


// Combo
uint16_t COMBO_LEN = CB_COMBO_LENGTH;

const uint16_t PROGMEM del_combo[] = {SFT_J, CTL_K, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {CTL_K, ALT_L, COMBO_END};
const uint16_t PROGMEM del_lower_combo[] = {LOWER_4, LOWER_5, COMBO_END};
const uint16_t PROGMEM bspc_lower_combo[] = {LOWER_5, LOWER_6, COMBO_END};
const uint16_t PROGMEM del_other_combo[] = {MCC_BSDL, MCC_DEL, COMBO_END};
const uint16_t PROGMEM bspc_other_combo[] = {MCC_BSPC, MCC_BSDL, COMBO_END};

const uint16_t PROGMEM left_combo[] = {ALT_S, CTL_D, COMBO_END};
const uint16_t PROGMEM right_combo[] = {CTL_D, SFT_F, COMBO_END};
const uint16_t PROGMEM left_lower_combo[] = {KC_DLR, LT(0,KC_LPRN), COMBO_END};
const uint16_t PROGMEM right_lower_combo[] = {LT(0,KC_LPRN), LT(0,KC_RPRN), COMBO_END};

const uint16_t PROGMEM ctrlaltdel_combo[] = {KC_GESC, KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM ctrlaltins_combo[] = {KC_GESC, KC_1, KC_3, COMBO_END};

combo_t key_combos[] = {
  [CB_BSPC] = COMBO(bspc_combo, KC_BSPC),
  [CB_DEL] = COMBO(del_combo, KC_DEL),
  [CB_BSPC_LOWER] = COMBO(bspc_lower_combo, KC_BSPC),
  [CB_DEL_LOWER] = COMBO(del_lower_combo, KC_DEL),
  [CB_BSPC_OTHER] = COMBO(bspc_other_combo, KC_BSPC),
  [CB_DEL_OTHER] = COMBO(del_other_combo, KC_DEL),
  
  [CB_LEFT] = COMBO(left_combo, KC_LEFT),
  [CB_RIGHT] = COMBO(right_combo, KC_RGHT),
  [CB_LEFT_LOWER] = COMBO(left_lower_combo, KC_LEFT),
  [CB_RIGHT_LOWER] = COMBO(right_lower_combo, KC_RGHT),
  
  [CB_CTRLALTDEL] = COMBO(ctrlaltdel_combo, LCA(KC_DEL)),
  [CB_CTRLALTINS] = COMBO(ctrlaltins_combo, LCA(KC_INS)),
};



// Tap-Hold dual function key
typedef struct {
    uint16_t mod_tap_keycode;
    uint16_t tap_keycode;
    uint16_t hold_keycode;
} sTapHolds;

#define S_TAP_HOLD(kc1, kc2, kc3) { .mod_tap_keycode = kc1, .tap_keycode = kc2, .hold_keycode = kc3 }

sTapHolds th_keycodes[] = {
    S_TAP_HOLD(LT(0,KC_MINS), 0, KC_EQL),// tap -, hold =
    S_TAP_HOLD(LT(0,KC_SLSH), 0, KC_BSLS),// tap slash, hold backslash
    S_TAP_HOLD(LT(0,KC_LPRN), KC_LPRN, KC_LABK), // tap ( hold <
    S_TAP_HOLD(LT(0,KC_RPRN), KC_RPRN, KC_RABK), // tap ) hold >
    S_TAP_HOLD(LT(0,KC_COLN), KC_COLN, KC_SCLN), // tap : hold ;
    S_TAP_HOLD(LT(0,KC_BSLS), KC_BSLS, KC_PIPE), // tap \ hold |
    S_TAP_HOLD(LT(0,KC_QUOT), KC_QUOT, KC_DQUO), // tap ' hold "
    S_TAP_HOLD(LT(0,KC_GRAVE), KC_GRAVE, KC_TILD), // tap ` hold ~
    S_TAP_HOLD(LT(0,LT_UDQU), KC_UNDS, KC_QUES), // tap _ hold ?
    
    S_TAP_HOLD(W_H1, 0, KC_1),
    S_TAP_HOLD(E_H2, 0, KC_2),
    S_TAP_HOLD(R_H3, 0, KC_3),
    S_TAP_HOLD(X_H4, 0, KC_4),
    S_TAP_HOLD(C_H5, 0, KC_5),
    S_TAP_HOLD(V_H6, 0, KC_6),
    S_TAP_HOLD(U_H7, 0, KC_7),
    S_TAP_HOLD(I_H8, 0, KC_8),
    S_TAP_HOLD(O_H9, 0, KC_9),
    S_TAP_HOLD(P_H0, 0, KC_0)
};

const size_t th_keycodes_count = sizeof(th_keycodes) / sizeof(sTapHolds);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY 
 * Home row mods
 * ESC+1+2 = Ctrl + Alt + Del
 * ESC+1+3 = Ctrl + Alt + Ins
 * S + D = Left
 * D + F = Right
 * J + K = Del
 * K + L = Backspace
 * Hold / for \
 * Hold lower Backspace for AltGr
 * Shift + Esc = ~
 * GUI + Esc = `
 * 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC`~|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |  W_1 |  E_2 |  R_3 |   T  |                    |   Y  |  U_7 |  I_8 |  O_9 |  P_0 |-_  =+|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift| GUI_A| ALT_S| CTL_D| SFT_F|   G  |-------.    ,-------|   H  | SFT_J| CTL_K| ALT_L|GUI_;:|SFT_'"|
 * |------+------+------+------+------+------|   =+  |    |   '"  |------+------+------+------+------+------|
 * |LCtrl |   Z  |  X_4 |  C_5 |  V_6 |   B  |-------|    |-------|   N  |   M  |   ,< |.> ._^|/?  \||RCtrl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |AltGr |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,  KC_2,  KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_BSPC, \
  KC_TAB,   KC_Q,  W_H1,  E_H2,    R_H3,    KC_T,                     KC_Y,    U_H7,    I_H8,    O_H9,    P_H0,          LT(0,KC_MINS), \
  KC_LSFT,  GUI_A, ALT_S, CTL_D,   SFT_F,   KC_G,                     KC_H,    SFT_J,   CTL_K,   ALT_L,   GUI_SCLN,      SFT_QUOT, \
  KC_LCTL,  KC_Z,  X_H4,  C_H5,    V_H6,    KC_B, KC_EQL,   KC_QUOT,  KC_N,    KC_M,    KC_COMM, DOT_SFT, LT(0,KC_SLSH), KC_RCTL, \
                          KC_LGUI, KC_LALT, TT(_LOWER), KC_SPC, KC_ENT, TT(_RAISE), RALT_BSPC, KC_RGUI \
),

 /* RAISE
 * Combo del and backspace at the same position as default layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  Up  |      |      |                    |      | ins  | pgup | home | PSCR | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | SFLK | Left | Down |Right |      |-------.    ,-------|      |    De|l   Bk|SP    | SLCK |      |
 * |------+------+------+------+------+------|  CAPS |    | NUMLCK|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |      |-------|    |-------|      |_MOUSE| pgdn | end  | PAUS |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /Enter  /       \Space \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
  CLR_LY,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                     KC_F6,   KC_F7,      KC_F8,    KC_F9,    KC_F10,  KC_F11,\
  _______, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX,                   XXXXXXX, KC_INS,     KC_PGUP,  KC_HOME,  KC_PSCR, KC_F12, \
  _______, MC_SFLK, KC_LEFT, KC_DOWN, KC_RGHT,  XXXXXXX,                   XXXXXXX, MCC_DEL,    MCC_BSDL, MCC_BSPC, KC_SLCK, _______, \
  _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE, XXXXXXX, KC_CAPS, KC_NLCK, XXXXXXX, TT(_MOUSE), KC_PGDN,  KC_END,   KC_PAUS, _______, \
                              _______, _______, _______, KC_ENT, KC_SPC,  _______, _______, _______\
),
 
/* LOWER
 * 4 + 5 = Del
 * 5 + 6 = Backspace
 * Hold \ for /
 * Hold ( for <
 * Hold ) for >
 * Hold 0 for AltGr
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   &  |                    |   +  |  7   |   8  |   9  |   *  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |(    <|)    >|\    ||-------.    ,-------|   =+ |  4   |   5  |   6  |   .  |'    "|
 * |------+------+------+------+------+------| `    ~|    | CALC  |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   _  |-------|    |-------|   -  |  1   |   2  |   3  |   /? |:    ;|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Enter  /       \Space \  |RAISE |   0  |   0  |
 *                   |      |      |      |/       /         \      \ |      | AltGr| RGUI |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  CLR_LY,  KC_F1,   KC_F2,   KC_F3,         KC_F4,         KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11, \
  _______, KC_EXLM, KC_AT,   KC_LCBR,       KC_RCBR,       KC_AMPR,                                      KC_PPLS, KC_7,    KC_8,    KC_9,     KC_PAST, KC_F12, \
  _______, KC_HASH, KC_DLR,  LT(0,KC_LPRN), LT(0,KC_RPRN), LT(0,KC_BSLS),                               KC_EQL,  LOWER_4, LOWER_5, LOWER_6,  KC_DOT,  LT(0,KC_QUOT), \
  _______, KC_PERC, KC_CIRC, KC_LBRC,       KC_RBRC,       LT(0,LT_UDQU),   LT(0,KC_GRAVE),  KC_CALC,   KC_PMNS, KC_1,    KC_2,    KC_3,     KC_SLSH, LT(0,KC_COLN), \
                                        _______, _______, _______,                   KC_ENT, KC_SPC,     _______, RALT_0,  RGUI_0 \
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
 *                   |      |      |      | /Space  /       \Enter \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  CLR_LY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_BRIU,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLD, KC_BRID,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, KC_SPC,  KC_ENT,  _______, _______, _______ \
),
/* MOUSE
 * Combo del and backspace at the same position as default layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |CLR_LY| XXXX | XXXX | XXXX | XXXX | XXXX |                    | XXXX | XXXX | XXXX | XXXX | XXXX |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | XXXX | XXXX |MS_BT3| MS_U |MS_W_U| XXXX |                    | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | XXXX |MS_BT2| MS_L | MS_D | MS_R | XXXX |-------.    ,-------| XXXX |    Bk|SP  De|l     | LGUI | XXXX |
 * |------+------+------+------+------+------|  XXXX |    | XXXX  |------+------+------+------+------+------|
 * | XXXX | XXXX |MS_W_L|MS_W_R|MS_W_D| XXXX |-------|    |-------| XXXX |_MOUSE|LShift|LCTRL | LAlt | XXXX |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | XXXX | XXXX |XXXX  | / MS_BT1/       \ XXXX \  |Trans | XXXX | XXXX |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_MOUSE] = LAYOUT(
  CLR_LY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                     XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_BSPC,
  XXXXXXX, XXXXXXX, KC_BTN3, KC_MS_U, KC_WH_U,  XXXXXXX,                     XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R,  XXXXXXX,                     XXXXXXX, MCC_BSPC, MCC_BSDL, MCC_DEL,  KC_LGUI, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_R, KC_WH_D,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, TT(_MOUSE),  KC_LSFT,  KC_LCTL, KC_LALT, XXXXXXX,
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


// Mod-Tap and Marco
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // For _RAISE layer UNDO, CUT, COPY, PASTE
  // Remove shift and alt mod before sending key
  switch (keycode) {
    case MC_UNDO:
    case MC_CUT:
    case MC_COPY:
    case MC_PASTE:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
        }
        if (get_mods() & MOD_MASK_ALT) {
          del_mods(MOD_MASK_ALT);
        }
      }
  }
  // Press UNDO, CUT, COPY, PASTE
  if (record->event.pressed) {
    switch (keycode) {
      case MC_UNDO:
        register_code16(LCTL(KC_Z));
        return false;
      case MC_CUT:
        register_code16(LCTL(KC_X));
        return false;
      case MC_COPY:
        register_code16(LCTL(KC_C));
        return false;
      case MC_PASTE:
        register_code16(LCTL(KC_V));
        return false;
    }
  // Release UNDO, CUT, COPY, PASTE
  } else {
    switch (keycode) {
      case MC_UNDO:
        unregister_code16(LCTL(KC_Z));
        return false;
      case MC_CUT:
        unregister_code16(LCTL(KC_X));
        return false;
      case MC_COPY:
        unregister_code16(LCTL(KC_C));
        return false;
      case MC_PASTE:
        unregister_code16(LCTL(KC_V));
        return false;
    }
  }
  
  // Tap-Hold dual function key
  for (size_t i = 0; i < th_keycodes_count; i++) {
    if (keycode == th_keycodes[i].mod_tap_keycode) {
      if (!record->tap.count && record->event.pressed) {
        tap_code16(th_keycodes[i].hold_keycode); // Intercept hold function to send =
        return false;
      }
      if (record->tap.count && record->event.pressed && th_keycodes[i].tap_keycode != 0) {
        tap_code16(th_keycodes[i].tap_keycode);
        return false;
      }
      return true;
    }
  }
  
  // Other Marco or Mod-Tap
  switch (keycode) {
    case DOT_SFT:
      if (!record->tap.count && record->event.pressed && (!(get_mods() & MOD_MASK_SHIFT))) {
        // Intercept hold function and not pressing shift
        // ". <one-shot-shift>"
        tap_code(KC_DOT);
        tap_code(KC_SPC);
        add_oneshot_mods(MOD_BIT(KC_LSHIFT));
        return false;
      }
      return true;
      
      
    case LOWER_4:
      if (record->event.pressed) {
        register_code16(KC_4);
      } else {
        unregister_code16(KC_4);
      }
      return false;
      
    case LOWER_5:
      if (record->event.pressed) {
        register_code16(KC_5);
      } else {
        unregister_code16(KC_5);
      }
      return false;
      
    case LOWER_6:
      if (record->event.pressed) {
        register_code16(KC_6);
      } else {
        unregister_code16(KC_6);
      }
      return false;
    
    // Shift lock key, press it again or press other shift key to cancel it
    case MC_SFLK:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
        } else {
          add_mods(MOD_MASK_SHIFT);
        }
      }
      return false;
    case KC_LSFT:
    case KC_RSFT:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
        }
      }
      break;
    case SFT_F:
    case SFT_J:
    case SFT_QUOT:
      if (!record->tap.count && record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
        }
      }
    
    // Esc as panic button
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

// Longer tapping term for thumb key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DOT_SFT:
      return TAPPING_TERM + 200;
      
    case RALT_BSPC:
    case RALT_0:
    case RGUI_0:
      return TAPPING_TERM + 150;
      
    case GUI_A:
    case ALT_S:
    case CTL_D:
    case SFT_F:
    case SFT_J:
    case CTL_K:
    case ALT_L:
    case GUI_SCLN:
    case SFT_QUOT:
      return TAPPING_TERM + 70;
    
    case W_H1:
    case E_H2:
    case R_H3:
    case X_H4:
    case C_H5:
    case V_H6:
    case U_H7:
    case I_H8:
    case O_H9:
    case P_H0:
      return TAPPING_TERM + 150;
      
    default:
      return TAPPING_TERM;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // disable auto-repeat for quick tap followed by a hold 
    case GUI_A:
    case ALT_S:
    case CTL_D:
    case SFT_F:
    case SFT_J:
    case CTL_K:
    case ALT_L:
    case GUI_SCLN:
    case LT(0,KC_MINS):
    case LT(0,KC_SLSH):
    case LT(0,KC_LPRN):
    case LT(0,KC_RPRN):
    case LT(0,KC_COLN):
    case LT(0,KC_BSLS):
    case LT(0,KC_QUOT):
    case LT(0,KC_GRAVE):
    case LT(0,LT_UDQU):
    
    case W_H1:
    case E_H2:
    case R_H3:
    case X_H4:
    case C_H5:
    case V_H6:
    case U_H7:
    case I_H8:
    case O_H9:
    case P_H0:
      return true;
    default:
      return false;
  }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Immediately select the hold action when another key is tapped.
    case TT(_RAISE):
    case TT(_LOWER):
    case TT(_MOUSE):
      return true;
    // return true for layer key
    default:
      // Do not select the hold action when another key is tapped.
      return false;
  }
}