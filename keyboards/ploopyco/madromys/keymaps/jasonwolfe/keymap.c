/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

extern bool is_drag_scroll;

#define DS_HOLD_TERM 150  // ms before hold activates momentary scroll

enum custom_keycodes {
    DRAG_KEY = SAFE_RANGE,
};

static bool     ds_key_held         = false;
static bool     ds_momentary_active = false;
static bool     ds_locked           = false;
static uint16_t ds_hold_timer       = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == DRAG_KEY) {
        if (record->event.pressed) {
            ds_key_held   = true;
            ds_hold_timer = timer_read();
        } else {
            ds_key_held = false;
            if (ds_momentary_active) {
                ds_momentary_active = false;
                if (!ds_locked) is_drag_scroll = false;
            } else {
                // quick tap: toggle lock
                ds_locked      = !ds_locked;
                is_drag_scroll = ds_locked;
            }
        }
        return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (ds_key_held && !ds_momentary_active && timer_elapsed(ds_hold_timer) >= DS_HOLD_TERM) {
        ds_momentary_active = true;
        is_drag_scroll      = true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( MS_BTN4, MS_BTN5, DRAG_KEY, MS_BTN2, MS_BTN1, MS_BTN3 )
};
