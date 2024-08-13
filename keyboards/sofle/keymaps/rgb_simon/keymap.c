// vim: set fdm=marker:
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define IS_MACOS !keymap_config.swap_lctl_lgui

// {{{ Definitions
enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _RAISE
};

enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_LOCK
};

// tap dance definitions
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

// Tap dance enums
enum {
    TD_LS, // super shift left
    TD_RS // super shift right
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void lsh_finished(tap_dance_state_t *state, void *user_data);
void lsh_reset(tap_dance_state_t *state, void *user_data);
void rsh_finished(tap_dance_state_t *state, void *user_data);
void rsh_reset(tap_dance_state_t *state, void *user_data);

// }}}

// {{{ Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                    |  6 ^ |  7 & |  8 * |  9 ( |  0 ) | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ` ~ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  \ | |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ; : |  ' " |
 * |------+------+------+------+------+------|  MUTE |    |  LOCK |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  , < |  . > |  / ? |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \   |MEH  | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

    [_BASE] = LAYOUT(
        KC_ESC ,     KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,                         KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 , KC_BSPC ,
        KC_TAB ,     KC_Q ,    KC_W ,    KC_E ,    KC_R ,    KC_T ,                         KC_Y ,    KC_U ,    KC_I ,    KC_O ,    KC_P ,  KC_GRV ,
        KC_BSLS ,    KC_A ,    KC_S ,    KC_D ,    KC_F ,    KC_G ,                         KC_H ,    KC_J ,    KC_K ,    KC_L , KC_SCLN , KC_QUOT ,
        TD(TD_LS),    KC_Z ,   KC_X ,    KC_C ,    KC_V ,    KC_B ,  KC_MUTE , KC_LOCK ,    KC_N ,    KC_M , KC_COMM ,  KC_DOT , KC_SLSH , TD(TD_RS),
                            KC_LGUI , KC_LALT , KC_LCTL , TT(_RAISE),   KC_SPC ,  KC_ENT ,  KC_MEH , KC_RCTL , KC_RALT , KC_RGUI
    ),
    /* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    | Home | PgDn | PgUp |  End |  Ins |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  F6  |  F7  |  F8  |  F9  |  F10 |                    | LStt | PrWd | NxWd | LEnd |   +  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |-------.    ,-------| Left | Down |  Up  | Rght |   -  |   _  |
 * |------+------+------+------+------+------|  MUTE |    |  LOCK |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|   [  |   ]  |   {  |   }  |      |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |RAISE | /Space  /       \Enter \  |MACWIN| RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
    [_RAISE] = LAYOUT(
        _______ ,   KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 ,                     KC_HOME , KC_PGDN , KC_PGUP ,  KC_END ,  KC_INS ,  KC_DEL ,
        _______ ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,  KC_F10 ,                     KC_LSTRT, KC_PRVWD, KC_NXTWD, KC_LEND , KC_PLUS , KC_EQUAL,
        XXXXXXX ,  KC_F11 ,  KC_F12 ,  KC_F13 ,  KC_F14 ,  KC_F15 ,                     KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, KC_MINUS, KC_UNDS ,
        KC_CAPS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , XXXXXXX , KC_CAPS ,
                          _______ , _______ , _______ , TO(_BASE) , _______ , _______ , CG_TOGG , _______ , _______ , _______
    ),
};

// }}}

// {{{ process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                if (IS_MACOS) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (IS_MACOS) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
            if (record->event.pressed) {
                if (IS_MACOS) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (IS_MACOS) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (IS_MACOS) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (IS_MACOS) {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (IS_MACOS) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (IS_MACOS) {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        // lock the screen (using MacOS Cmd+Ctl+Q shortcut)
        case KC_LOCK:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LGUI | MOD_LCTL));
                register_code(KC_Q);
            } else {
                unregister_mods(mod_config(MOD_LGUI | MOD_LCTL));
                unregister_code(KC_Q);
            }
    }
    return true;
}
// }}}

// {{{ Layers

// {{{ Layer LEDs
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_OFF}
);

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED - 50}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_TEAL - 50}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_PURPLE - 50}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_capslock_layer,
    my_layer1_layer,
    my_layer2_layer
);

void choose_layer(void) {
    rgblight_set_layer_state(0, IS_LAYER_ON(_BASE));
    rgblight_set_layer_state(2, IS_LAYER_ON(_RAISE));

    rgblight_set_layer_state(1, is_caps_word_on() || host_keyboard_led_state().caps_lock);
}

void caps_word_set_user(bool active) {
    choose_layer();
}

bool led_update_user(led_t led_state) {
    choose_layer();
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    choose_layer();
    return state;
}

// }}}

// }}}

// {{{ Tap dance

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
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

// Create an instance of 'td_tap_t' for the left and right shift tap dances
static td_tap_t lshtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t rshtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void lsh_finished(tap_dance_state_t *state, void *user_data) {
    lshtap_state.state = cur_dance(state);
    switch (lshtap_state.state) {
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_SINGLE_TAP: register_code16(KC_LPRN); break;
        case TD_DOUBLE_TAP: register_code16(KC_LCBR); break;
        case TD_TRIPLE_TAP: register_code(KC_LBRC); break;
        default: break;
    }
}

void lsh_reset(tap_dance_state_t *state, void *user_data) {
    switch (lshtap_state.state) {
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_SINGLE_TAP: unregister_code16(KC_LPRN); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_LCBR); break;
        case TD_TRIPLE_TAP: unregister_code(KC_LBRC); break;
        default: break;
    }
    lshtap_state.state = TD_NONE;
}

void rsh_finished(tap_dance_state_t *state, void *user_data) {
    rshtap_state.state = cur_dance(state);
    switch (rshtap_state.state) {
        case TD_SINGLE_HOLD: register_code(KC_RSFT); break;
        case TD_SINGLE_TAP: register_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP: register_code16(KC_RCBR); break;
        case TD_TRIPLE_TAP: register_code(KC_RBRC); break;
        default: break;
    }
}

void rsh_reset(tap_dance_state_t *state, void *user_data) {
    switch (rshtap_state.state) {
        case TD_SINGLE_HOLD: unregister_code(KC_RSFT); break;
        case TD_SINGLE_TAP: unregister_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_RCBR); break;
        case TD_TRIPLE_TAP: unregister_code(KC_RBRC); break;
        default: break;
    }
    rshtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsh_finished, lsh_reset),
    [TD_RS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsh_finished, rsh_reset)
};

// }}}

// {{{ OLED
#ifdef OLED_ENABLE

const char PROGMEM base_oled[] = {
    0x97, 0x98, 0x9F, 0x9F, 0x9F,
    0xB7, 0xB8, 0x9F, 0x9F, 0x9F
};

const char PROGMEM ly2_oled[] = {
    0x99, 0x9A, 0x9F, 0x9F, 0x9F,
    0xB9, 0xBA, 0x9F, 0x9F, 0x9F
};

void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(base_oled, false);
            break;
        case _RAISE:
            oled_write_P(ly2_oled, false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undef\n"), false);
    }

    // Host Keyboard LED Status
    bool caps_on = host_keyboard_led_state().caps_lock || is_caps_word_on();
    oled_write_P(caps_on ? PSTR("CAP  \n") : PSTR("     \n"), false);
}

const char PROGMEM macos_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4,
    0x8A, 0x8B, 0x8C, 0x8D, 0x8E,
    0xAA, 0xAB, 0xAC, 0xAD, 0xAE
};

const char PROGMEM linux_logo[] = {
    0x85, 0x86, 0x87, 0x88, 0x89,
    0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
    0xC5, 0xC6, 0xC7, 0xCC, 0xC9,
    0x8F, 0x90, 0x91, 0x92, 0x93,
    0xAF, 0xB0, 0xB1, 0xB2, 0xB3
};

void render_os(void) {
    if (IS_MACOS) {
        oled_write_P(macos_logo, false);
        // oled_write_ln_P(PSTR("MACOS\n"), false);
    } else {
        oled_write_P(linux_logo, false);
        // oled_write_ln_P(PSTR("LINUX\n"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_os();  // Renders a static logo
        // oled_scroll_left();  // Turns on scrolling
    }

    return false;
}
#endif

// }}}

// {{{ Encoders

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}

// }}}

// {{{ Keyboard post init
void keyboard_post_init_user(void) {
    // Enable LED layers
    rgblight_layers = my_rgb_layers;
}
// }}}
