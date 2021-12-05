#include "quantum.h"


#define ACTION_TAP_DANCE_TAP_HOLD(kc1, kc2) { \
    .fn = { qk_tap_dance_tap_hold_each_tap, qk_tap_dance_tap_hold_finished, qk_tap_dance_tap_hold_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),  \
  }


// Tap Dance
/*
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
*/

// Tap dance enums
enum tap_dance {
	SLSH_BSLS
};

void qk_tap_dance_tap_hold_each_tap(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data);

//td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the tap dance. Put it here so it can be used in any keymap
//void x_finished(qk_tap_dance_state_t *state, void *user_data);
//void x_reset(qk_tap_dance_state_t *state, void *user_data);

// Ready to use Tap dance definitions, just put them on your layout
#define TD_SLSH_BSLS TD(SLSH_BSLS)
