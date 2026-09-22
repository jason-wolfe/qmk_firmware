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

/* Drag-scroll speed: same feel as my Madromys (64 counts per notch at 900
   DPI; see the DPI note below for why the divisor here is 78).
   The A+ reports scroll in hi-res units (120 per notch), but many Windows
   apps drop anything under a full notch in each wheel message, and at
   ~1ms reports almost every drag-scroll report is a fraction of a notch.
   So use a Madromys-style divisor here and have pointing_device_task_user
   scale each whole notch up to 120 units by the hi-res multiplier.
   Every app then sees whole notches, just like on the Madromys. */
#undef PLOOPY_DRAGSCROLL_DIVISOR_H
#undef PLOOPY_DRAGSCROLL_DIVISOR_V
#define PLOOPY_DRAGSCROLL_DIVISOR_H 78.0
#define PLOOPY_DRAGSCROLL_DIVISOR_V 78.0

/* Pointer speed: each stock DPI step (600/900/1200/1600/2400) raised ~20%.
   The PMW3360 only takes multiples of 100. The DPI step is saved on the
   device, so scaling every step raises speed whichever one is selected.
   ploopyco.c defaults to step 0 when a keymap provides its own list, so
   keep the stock default of step 1 (now 1100).
   Drag scroll counts go up with DPI too, which is why the divisors above
   are 78 (64 * 1100 / 900) rather than the Madromys's 64. */
#define PLOOPY_DPI_OPTIONS { 700, 1100, 1400, 1900, 2900 }
#define PLOOPY_DPI_DEFAULT 1

/* Milliseconds the drag-scroll key must be held before it flips from
   tap-to-lock into momentary mode. See PKC_DRAG_SCROLL in keymap.c. */
#define DS_HOLD_TERM 150
