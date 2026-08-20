#pragma once

/* Ported from the ZMK Corne config at ~/Documents/zmk-config/config/corne.keymap.
 * Each define below names the ZMK behavior it replaces. */

/* ZMK &mt defaults (used by the Esc/Ctrl pinky key). The bottom-row mods want
 * 280ms instead and override this in get_tapping_term(). */
#define TAPPING_TERM 200

/* bml/bmr quick-tap-ms = <175>. &mt wants 0 and overrides in get_quick_tap_term(). */
#define QUICK_TAP_TERM 175

/* bml/bmr flavor = "balanced". &mt is "hold-preferred" and overrides in
 * get_hold_on_other_key_press(). */
#define PERMISSIVE_HOLD

/* bml/bmr hold-trigger-key-positions = <KEYS_R/KEYS_L THUMBS_NO_SPACE>,
 * i.e. the opposite-hands rule. Handedness is in chordal_hold_layout[] and the
 * space-bar exclusion is in get_chordal_hold(). */
#define CHORDAL_HOLD

/* bml/bmr require-prior-idle-ms = <150>. Not set on the shift mod-taps, which
 * opt out in get_flow_tap_term(). */
#define FLOW_TAP_TERM 150

/* Replaces the &as / &as_ht / &shifted macro trio. 170ms == as_ht tapping-term-ms.
 * The two NO_ defines restrict auto-shift to the alphas, matching the Corne where
 * only &as keys are wrapped -- TAB ' , . - / and the LOWER number row are plain. */
#define AUTO_SHIFT_TIMEOUT 170
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC
