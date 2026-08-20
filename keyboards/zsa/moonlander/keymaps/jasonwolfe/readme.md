# jasonwolfe — Moonlander

A port of my ZMK Corne keymap (`~/Documents/zmk-config/config/corne.keymap`) to the
Moonlander. Dvorak, bottom-row mods, auto-shift on the alphas, six layers.

The port is deliberately strict: the 42 Corne keys sit in their exact relative
positions and every other key on the board is `KC_NO`, so the two keyboards behave
identically. The three Corne alpha rows land on the Moonlander's rows 2–4, which puts
the Corne home row on the Moonlander home row; the three thumbs per side land on the
thumb cluster. The number row, the bottom row, the inner index-stretch keys and the
right mission-control key are all dead.

The one intentional deviation is the **left mission-control key**, which toggles
between the Windows and Mac layouts. On the Corne this happened as a side effect of
switching Bluetooth profiles; the Moonlander is wired, so it needs its own key.

## Layers

```
0  BASE       Windows default (Dvorak)
1  RAISE      Windows raise — symbols, browser/tab shortcuts
2  MAC        Mac default — GUI and CTRL swapped on the bottom row
3  MAC_RAISE  Mac raise — Cmd-based browser shortcuts
4  LOWER      shared — numbers, arrows, nav, volume
5  FN         function keys — reached by holding raise + lower
```

`FN` is reached the same way as on the Corne: hold both thumb layer keys. ZMK's
`conditional_layers` node becomes `layer_state_set_user()`, which resolves both
`RAISE+LOWER` and `MAC_RAISE+LOWER` to `FN`.

## BASE

Dead keys omitted for clarity; `*` marks the OS toggle.

```
 TAB    '      ,      .      P      Y   │   F      G      C      R      L    BSPC
 ESC¹   A      O      E      U      I   │   D      H      T      N      S     -
 CAPS   ;²     Q³     J⁴     K⁵     X   │   B      M⁵     W⁴     V³     Z²    /

                              *  ┌──────────┐
                    DEL  LOWER  SPC │ ENT  RAISE
```

```
¹ hold = Ctrl     ² hold = GUI      ³ hold = Alt
⁴ hold = Ctrl     ⁵ hold = Shift
```

On `MAC`, superscripts 2 and 4 trade places (GUI ↔ Ctrl). Everything else is identical.

## What the ZMK behaviors became

| ZMK | QMK |
| --- | --- |
| `&as` / `&as_ht` / `&shifted` macros | built-in Auto Shift, `AUTO_SHIFT_TIMEOUT 170` |
| `&caps_word` + `continue-list` | `CAPS_WORD_ENABLE`, `CW_TOGG` (QMK's default continue set already matches) |
| `hold-trigger-key-positions` | `CHORDAL_HOLD` + `chordal_hold_layout[]` |
| `require-prior-idle-ms = <150>` | `FLOW_TAP_TERM 150` + `get_flow_tap_term()` |
| `flavor = "balanced"` | `PERMISSIVE_HOLD` |
| `flavor = "hold-preferred"` (the `&mt` Esc/Ctrl) | `get_hold_on_other_key_press()` |
| `tapping-term-ms` / `quick-tap-ms` | `get_tapping_term()` / `get_quick_tap_term()` |
| `conditional_layers` | `layer_state_set_user()` |
| tab/nav macros | plain modded keycodes, e.g. `LCTL(LSFT(KC_TAB))` |
| `&bt_win` / `&bt_mac` | `PLAT_WIN` / `PLAT_MAC` (persistent default-layer set) |
| `&bt_clr_td` | `TD(TD_BOOT)` — same position, same double-tap guard, now the bootloader |
| `&bt` | dropped — the Moonlander is wired |

`NO_AUTO_SHIFT_SPECIAL` and `NO_AUTO_SHIFT_NUMERIC` keep auto-shift restricted to the
alphas, matching the Corne, where only `&as`-wrapped keys auto-shift and
`TAB ' , . - /` plus the `LOWER` number row are plain.

Two details that needed explicit handling rather than a global setting:

- **Space is exempt from the mods.** The Corne's `THUMBS_NO_SPACE` list excludes the
  space thumb from every bottom-row mod's trigger positions. Handedness alone can't
  express this — marking space `'L'` covers the left-hand mods, and
  `get_chordal_hold()` rejects it for the right-hand mods.
- **The Esc/Ctrl pinky is unrestricted.** It was a plain `&mt` with no
  `hold-trigger-key-positions`, so `get_chordal_hold()` returns `true` for it and it
  can hold against its own hand.

### Known behavioral difference

ZMK's `hold-trigger-on-release` defers the hold/tap decision until the tap-hold key
itself is released. QMK's Chordal Hold decides when the *other* key is pressed or
released. `PERMISSIVE_HOLD` gets close, but fast same-hand rolls that ZMK would
resolve as taps may occasionally resolve as holds here. If that shows up in practice,
raise the 280 ms term in `get_tapping_term()` before reaching for anything else.

## Entering the bootloader

Hold both thumb layer keys to reach `FN`, then **double-tap the top-left key** (the
`TAB` position). A single tap does nothing — the second tap has to land within the
280 ms tapping term. This is the same guard `&bt_clr_td` used on the Corne, in the
same key position, so no paperclip is needed for a normal reflash.

## Build

```
qmk compile -kb zsa/moonlander -km jasonwolfe
```

Flash with ZSA's Wally, or `qmk flash -kb zsa/moonlander -km jasonwolfe`.
