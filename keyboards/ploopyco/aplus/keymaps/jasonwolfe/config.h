/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
/* ===================== jasonwolfe customizations ===================== */

/* Carried over from my Madromys keymap. The A+ leaves this at the QMK
   default of 5. */
#define DEBOUNCE 15

/* Drag-scroll speed, ported from my Madromys setting of 64.0 on both axes.
   The divisors are NOT directly comparable between the two boards: the A+
   enables POINTING_DEVICE_HIRES_SCROLL with a 120x multiplier, so the host
   treats 120 wheel units as one notch. Effective ball counts per real notch
   is therefore (divisor * 120), where on the Madromys it was just (divisor).
   64 / 120 = 0.5333 reproduces the Madromys feel.
   A+ stock values were H 1.0 (=120 counts/notch) and V 0.3 (=36). */
#undef PLOOPY_DRAGSCROLL_DIVISOR_H
#undef PLOOPY_DRAGSCROLL_DIVISOR_V
#define PLOOPY_DRAGSCROLL_DIVISOR_H 0.5333
#define PLOOPY_DRAGSCROLL_DIVISOR_V 0.5333

/* Milliseconds the drag-scroll key must be held before it flips from
   tap-to-lock into momentary mode. See PKC_DRAG_SCROLL in keymap.c. */
#define DS_HOLD_TERM 150
