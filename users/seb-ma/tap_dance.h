#pragma once
#ifdef TAP_DANCE_ENABLE

/* Tap dance keys declarations */
enum tapdances {
    TD_COMM_QUOTE = 0, // Single: ','           Double: '''
    TD_GUIS,           // Single: KC_LGUI       Double: KC_APP
#ifdef MOUSEKEY_ENABLE
    TD_MS_BTNS,        // Single: KC_MS_BTN1    Double: KC_MS_BTN2
    TD_MS_ACCEL,       // Single: KC_MS_ACCEL0  Double: KC_MS_ACCEL1; Triple: KC_MS_ACCEL2
#endif
};

#endif // TAP_DANCE_ENABLE
