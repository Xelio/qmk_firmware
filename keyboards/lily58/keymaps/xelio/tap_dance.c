#include "tap_dance.h"



void qk_tap_dance_tap_hold_each_tap(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
  if (state->count == 2) {
    tap_code16(pair->kc1);
	state->count = 1; // Reset the counter as we are using the first key
  }
}

void qk_tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) register_code16 (pair->kc1);
    // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
    else register_code16 (pair->kc2);
  }
}

void qk_tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data; 
  unregister_code16 (pair->kc1);
  unregister_code16 (pair->kc2);
}

 /*
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}
*/


// Create an instance of 'td_tap_t' for the 'x' tap dance.
/*
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_X); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    xtap_state.state = TD_NONE;
}
*/


// Map the functions to keys w/ the tap-dance function
qk_tap_dance_action_t tap_dance_actions[] = {
    //[X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
	[SLSH_BSLS] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_BSLS)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_SLSH_BSLS:
            return 300;
        default:
            return TAPPING_TERM;
    }
}

