// Moonlander port of the ZMK Corne keymap in ~/Documents/zmk-config/config/corne.keymap.
//
// The 42 Corne keys keep their exact relative positions: the three alpha rows sit
// on the Moonlander's rows 2-4 (so the Corne home row lands on the Moonlander home
// row) and the three thumbs per side sit on the thumb cluster. Every other key is
// KC_NO so the two boards behave identically -- except the left mission-control
// key, which replaces the Corne's Bluetooth-coupled OS switch.

#include QMK_KEYBOARD_H

enum layers {
    BASE,       // 0 - Windows default (Dvorak)
    RAISE,      // 1 - Windows raise
    MAC,        // 2 - Mac default (GUI<->CTRL swapped)
    MAC_RAISE,  // 3 - Mac raise (Cmd browser shortcuts)
    LOWER,      // 4 - shared lower
    FN,         // 5 - function keys (raise+lower via conditional layer)
};

// The Corne switched OS by switching Bluetooth profile (&bt_win / &bt_mac). The
// Moonlander is wired, so the switch is explicit instead. All three write the
// default layer to EEPROM, so unplugging and moving between machines keeps the
// platform you last chose.
enum custom_keycodes {
    PLAT_TG = SAFE_RANGE,  // toggle between BASE and MAC (left mission-control key)
    PLAT_WIN,              // was &bt_win
    PLAT_MAC,              // was &bt_mac
};

// Browser/tab shortcuts. In ZMK these were one-binding macros; QMK expresses them
// as plain modded keycodes, so the macros are gone.
#define PREV_TAB LCTL(LSFT(KC_TAB))
#define NEXT_TAB LCTL(KC_TAB)
#define CLOSE_TB LCTL(KC_W)
#define REOPEN_T LCTL(LSFT(KC_T))
#define NAV_BACK LALT(KC_LEFT)
#define NAV_FWD  LALT(KC_RGHT)

#define CLOSE_TM LGUI(KC_W)
#define REOPEN_M LGUI(LSFT(KC_T))
#define NAV_BK_M LGUI(KC_LEFT)
#define NAV_FW_M LGUI(KC_RGHT)

// Bottom-row mods (ZMK &bml / &bmr / &bml_s / &bmr_s).
#define BR_SCLN LGUI_T(KC_SCLN)
#define BR_Q    LALT_T(KC_Q)
#define BR_J    LCTL_T(KC_J)
#define BR_K    LSFT_T(KC_K)
#define BR_M    RSFT_T(KC_M)
#define BR_W    RCTL_T(KC_W)
#define BR_V    LALT_T(KC_V)
#define BR_Z    RGUI_T(KC_Z)

// Mac variants: GUI and CTRL trade places, ALT and SHIFT stay put.
#define MR_SCLN LCTL_T(KC_SCLN)
#define MR_J    LGUI_T(KC_J)
#define MR_W    RGUI_T(KC_W)
#define MR_Z    RCTL_T(KC_Z)

#define ESC_CTL LCTL_T(KC_ESC)

// Guarded the way &bt_clr_td guarded Bluetooth-clear on the Corne: a single tap
// does nothing, and only a second tap inside the tapping term fires. It sits in
// the same key position, on FN, so reaching the bootloader means holding both
// thumb layer keys and then double-tapping -- not something a stray press finds.
enum tap_dances {
    TD_BOOT,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0 -- Windows default
    [BASE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    XXXXXXX,     XXXXXXX, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
        ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,     XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        CW_TOGG, BR_SCLN, BR_Q,    BR_J,    BR_K,    KC_X,                          KC_B,    BR_M,    BR_W,    BR_V,    BR_Z,    KC_SLSH,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          PLAT_TG,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_DEL,  MO(LOWER), KC_SPC,    KC_ENT,  MO(RAISE), XXXXXXX
    ),

    // Layer 1 -- Windows raise
    [RAISE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        NAV_BACK,PREV_TAB,NEXT_TAB,CLOSE_TB,REOPEN_T,NAV_FWD, XXXXXXX,     XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,     XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, _______,                       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, KC_SPC,      KC_ENT,  _______, _______
    ),

    // Layer 2 -- Mac default (GUI<->CTRL swapped on the bottom row)
    [MAC] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    XXXXXXX,     XXXXXXX, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
        ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,     XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        CW_TOGG, MR_SCLN, BR_Q,    MR_J,    BR_K,    KC_X,                          KC_B,    BR_M,    MR_W,    BR_V,    MR_Z,    KC_SLSH,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          PLAT_TG,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_DEL,  MO(LOWER), KC_SPC,    KC_ENT,  MO(MAC_RAISE), XXXXXXX
    ),

    // Layer 3 -- Mac raise (Cmd browser shortcuts)
    [MAC_RAISE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        NAV_BK_M,PREV_TAB,NEXT_TAB,CLOSE_TM,REOPEN_M,NAV_FW_M,XXXXXXX,     XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,     XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, _______,                       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, KC_SPC,      KC_ENT,  _______, _______
    ),

    // Layer 4 -- shared lower (highest index of the momentary layers, never shadowed)
    [LOWER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, XXXXXXX,     XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,     XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                       _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, KC_SPC,      KC_ENT,  _______, _______
    ),

    // Layer 5 -- function keys, reached by holding both raise and lower
    [FN] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TD(TD_BOOT), PLAT_WIN, PLAT_MAC, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,     XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_F11,  KC_F12,  _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______, KC_SPC,      KC_ENT,  _______, _______
    ),
};

// Handedness for CHORDAL_HOLD, standing in for ZMK's hold-trigger-key-positions.
// The thumbs are '*' (exempt from the opposite-hands rule) because KEYS_L and
// KEYS_R were both paired with THUMBS_NO_SPACE. Space is the one thumb left out
// of that list, so it stays 'L' -- and get_chordal_hold() below blocks it for the
// right-hand mods too.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      '*',    '*',      'R', 'R', 'R', 'R', 'R',
                        '*', '*', 'L',    '*', '*', '*'
);
// clang-format on

static void boot_dance_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        reset_keyboard();
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(boot_dance_finished),
};

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // The Esc/Ctrl pinky was a plain ZMK &mt with no positional restriction, so it
    // is allowed to hold against anything, including its own hand.
    if (tap_hold_keycode == ESC_CTL) {
        return true;
    }
    // Space is absent from THUMBS_NO_SPACE, so no bottom-row mod may hold against it.
    if (other_keycode == KC_SPC) {
        return false;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ESC_CTL:
            return TAPPING_TERM;  // ZMK &mt default
        default:
            return 280;  // bml/bmr/bml_s/bmr_s tapping-term-ms
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ESC_CTL:
            return 0;  // ZMK &mt default quick-tap-ms
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // ZMK &mt is flavor "hold-preferred"; the bottom-row mods are "balanced" and
    // fall through to PERMISSIVE_HOLD.
    return keycode == ESC_CTL;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        // bml_s/bmr_s and &mt carry no require-prior-idle-ms.
        case BR_K:
        case BR_M:
        case ESC_CTL:
            return 0;
        default:
            if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
                return FLOW_TAP_TERM;
            }
            return 0;
    }
}

// Replaces the ZMK conditional-layers node: RAISE+LOWER and MAC_RAISE+LOWER both
// resolve to FN.
layer_state_t layer_state_set_user(layer_state_t state) {
    if ((state & (1UL << LOWER)) && (state & ((1UL << RAISE) | (1UL << MAC_RAISE)))) {
        state |= 1UL << FN;
    } else {
        state &= ~(1UL << FN);
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case PLAT_TG:
            set_single_persistent_default_layer((default_layer_state & (1UL << MAC)) ? BASE : MAC);
            return false;
        case PLAT_WIN:
            set_single_persistent_default_layer(BASE);
            return false;
        case PLAT_MAC:
            set_single_persistent_default_layer(MAC);
            return false;
    }
    return true;
}
