// vim: set fdm=marker:
// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_FONT_H "qmkapplefont.c"

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define TAPPING_TERM 175

// two taps to activate the TT() layer tap-toggle
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD

#define CAPS_WORD_IDLE_TIMEOUT 3000

// {{{ split keyboard settings
// use EEPROM setting to determine handedness
// Elite-Pi must be flashed with
//   -bl uf2-split-left
// OR
//   -bl uf2-split-right
#define EE_HANDS

// sync
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
// }}}

// {{{ LEDs
#ifdef RGBLIGHT_LED_COUNT
#undef RGBLIGHT_LED_COUNT
#endif
#define RGBLIGHT_LED_COUNT 12

#ifdef RGBLED_SPLIT
#undef RGBLED_SPLIT
#endif
#define RGBLED_SPLIT {6, 6}

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

// }}}
