// vim: set fdm=marker:
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Helper macros
bool is_macos = true;

// {{{ Definitions
enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _RAISE
};

enum custom_keycodes {
    KC_MACLNX = QK_USER,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_LOCK,
    KC_EMDS
};

// Tap Dance keycodes
enum td_keycodes {
    LSFT_PAR,
    RSFT_PAR,
    LGUI_CBR,
    RGUI_CBR,
    LALT_BRC,
    RALT_BRC,
    LCTL_QUT,
    RCTL_DQT,
    MEH_TMUX
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void lsft_par_finished(tap_dance_state_t *state, void *user_data);
void lsft_par_reset(tap_dance_state_t *state, void *user_data);
void rsft_par_finished(tap_dance_state_t *state, void *user_data);
void rsft_par_reset(tap_dance_state_t *state, void *user_data);
void lgui_cbr_finished(tap_dance_state_t *state, void *user_data);
void lgui_cbr_reset(tap_dance_state_t *state, void *user_data);
void rgui_cbr_finished(tap_dance_state_t *state, void *user_data);
void rgui_cbr_reset(tap_dance_state_t *state, void *user_data);
void lalt_brc_finished(tap_dance_state_t *state, void *user_data);
void lalt_brc_reset(tap_dance_state_t *state, void *user_data);
void ralt_brc_finished(tap_dance_state_t *state, void *user_data);
void ralt_brc_reset(tap_dance_state_t *state, void *user_data);
void lctl_qut_finished(tap_dance_state_t *state, void *user_data);
void lctl_qut_reset(tap_dance_state_t *state, void *user_data);
void rctl_dqt_finished(tap_dance_state_t *state, void *user_data);
void rctl_dqt_reset(tap_dance_state_t *state, void *user_data);
void meh_tmux_finished(tap_dance_state_t *state, void *user_data);
void meh_tmux_reset(tap_dance_state_t *state, void *user_data);

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
        KC_ESC ,      KC_1 ,        KC_2 ,        KC_3 ,        KC_4 ,      KC_5 ,                            KC_6 ,        KC_7 ,        KC_8 ,        KC_9 ,    KC_0 , KC_BSPC ,
        KC_TAB ,      KC_Q ,        KC_W ,        KC_E ,        KC_R ,      KC_T ,                            KC_Y ,        KC_U ,        KC_I ,        KC_O ,    KC_P ,  KC_GRV ,
        KC_BSLS ,     KC_A ,        KC_S ,        KC_D ,        KC_F ,      KC_G ,                            KC_H ,        KC_J ,        KC_K ,        KC_L , KC_SCLN , KC_QUOT ,
        TD(LSFT_PAR) , KC_Z ,        KC_X ,        KC_C ,        KC_V ,      KC_B , KC_MUTE , KC_LOCK ,        KC_N ,        KC_M ,     KC_COMM ,      KC_DOT , KC_SLSH , TD(RSFT_PAR),
        TD(LGUI_CBR) , TD(LALT_BRC) , TD(LCTL_QUT) , TT(_RAISE),  KC_SPC ,  KC_ENT , TD(MEH_TMUX) , TD(RCTL_DQT) , TD(RALT_BRC) , TD(RGUI_CBR)
    ),
    /* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |MACLNX|  F1  |  F2  |  F3  |  F4  |  F5  |                    | Home | PgDn | PgUp |  End |  Ins |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  F6  |  F7  |  F8  |  F9  |  F10 |                    | LStt | PrWd | NxWd | LEnd |   +  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |-------.    ,-------| Left | Down |  Up  | Rght |   -  |   _  |
 * |------+------+------+------+------+------|  MUTE |    |  LOCK |------+------+------+------+------+------|
 * | Cword|      |      |      |      |      |-------|    |-------|   [  |   ]  |   {  |   }  |   —  | Caps |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |RAISE | /Space  /       \Enter \  |      | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
    [_RAISE] = LAYOUT(
        KC_MACLNX ,   KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 ,                     KC_HOME , KC_PGDN , KC_PGUP ,  KC_END ,  KC_INS ,  KC_DEL ,
        _______ ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,  KC_F10 ,                     KC_LSTRT, KC_PRVWD, KC_NXTWD, KC_LEND , KC_PLUS , KC_EQUAL,
        XXXXXXX ,  KC_F11 ,  KC_F12 ,  KC_F13 ,  KC_F14 ,  KC_F15 ,                     KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, KC_MINUS, KC_UNDS ,
        CW_TOGG , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_EMDS , KC_CAPS ,
        _______ , _______ , _______ , TO(_BASE) , _______ , _______ , _______ , _______ , _______ , _______
    ),
};

// }}}

// {{{ tap Dance

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

#define TD_FINISHED(name, hold, tap) \
void name##_finished(tap_dance_state_t *state, void *user_data) { \
    td_state = cur_dance(state); \
    switch (td_state) { \
        case TD_SINGLE_TAP: \
            register_code16(tap); \
            break; \
        case TD_SINGLE_HOLD: \
            register_mods(MOD_BIT(hold)); \
            break; \
        case TD_DOUBLE_SINGLE_TAP: \
            tap_code16(tap); \
            register_code16(tap); \
            break; \
        default: \
            break; \
    } \
}

#define TD_RESET(name, hold, tap) \
void name##_reset(tap_dance_state_t *state, void *user_data) { \
    switch (td_state) { \
        case TD_SINGLE_TAP: \
            unregister_code16(tap); \
            break; \
        case TD_SINGLE_HOLD: \
            unregister_mods(MOD_BIT(hold)); \
            break; \
        case TD_DOUBLE_SINGLE_TAP: \
            unregister_code16(tap); \
            break; \
        default: \
            break; \
    } \
}

TD_FINISHED(lsft_par, KC_LSFT, KC_LPRN)
TD_FINISHED(rsft_par, KC_RSFT, KC_RPRN)
TD_FINISHED(lgui_cbr, KC_LGUI, KC_LCBR)
TD_FINISHED(rgui_cbr, KC_RGUI, KC_RCBR)
TD_FINISHED(lalt_brc, KC_LALT, KC_LBRC)
TD_FINISHED(ralt_brc, KC_RALT, KC_RBRC)
TD_FINISHED(lctl_qut, KC_LCTL, KC_QUOT)
TD_FINISHED(rctl_dqt, KC_RCTL, KC_DQT)
TD_FINISHED(meh_tmux, KC_MEH, C(KC_X))
TD_RESET(lsft_par, KC_LSFT, KC_LPRN)
TD_RESET(rsft_par, KC_RSFT, KC_RPRN)
TD_RESET(lgui_cbr, KC_LGUI, KC_LCBR)
TD_RESET(rgui_cbr, KC_RGUI, KC_RCBR)
TD_RESET(lalt_brc, KC_LALT, KC_LBRC)
TD_RESET(ralt_brc, KC_RALT, KC_RBRC)
TD_RESET(lctl_qut, KC_LCTL, KC_QUOT)
TD_RESET(rctl_dqt, KC_RCTL, KC_DQT)
TD_RESET(meh_tmux, KC_MEH, C(KC_X))

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [LSFT_PAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_par_finished, lsft_par_reset),
    [RSFT_PAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsft_par_finished, rsft_par_reset),
    [LGUI_CBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_cbr_finished, lgui_cbr_reset),
    [RGUI_CBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_cbr_finished, rgui_cbr_reset),
    [LALT_BRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_brc_finished, lalt_brc_reset),
    [RALT_BRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_brc_finished, ralt_brc_reset),
    [LCTL_QUT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_qut_finished, lctl_qut_reset),
    [RCTL_DQT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_dqt_finished, rctl_dqt_reset),
    [MEH_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, meh_tmux_finished, meh_tmux_reset)
};

// }}}

// {{{ process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MACLNX:
            if (record->event.pressed) {
                is_macos = !is_macos;
            }
            break;
        case KC_EMDS:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LALT | MOD_LSFT));
                register_code(KC_MINUS);
            } else {
                unregister_mods(mod_config(MOD_LALT | MOD_LSFT));
                unregister_code(KC_MINUS);
            }
            break;
        case KC_PRVWD:
            if (is_macos) {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_ESC);
                    unregister_code(KC_ESC);
                    register_code(KC_B);
                } else {
                    unregister_code(KC_B);
                }
            }
            break;
        case KC_NXTWD:
            if (is_macos) {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_ESC);
                    unregister_code(KC_ESC);
                    register_code(KC_F);
                } else {
                    unregister_code(KC_F);
                }
            }
            break;
        case KC_LSTRT:
            if (is_macos) {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_LEFT);
                }
            } else {
                if (record->event.pressed) {
                    register_mods(MOD_LCTL);
                    register_code(KC_A);
                } else {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_A);
                }
            }
            break;
        case KC_LEND:
            if (is_macos) {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_RIGHT);
                }
            } else {
                if (record->event.pressed) {
                    register_mods(MOD_LCTL);
                    register_code(KC_E);
                } else {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_E);
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

// {{{ Layer LEDs
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_OFF}
);

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED - 50}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_PURPLE - 50}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_capslock_layer,
    my_layer1_layer
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

// {{{ OLED
#ifdef OLED_ENABLE

void render_status(void) {
    static const char PROGMEM base_oled[] = {
        0x95, 0x96, 0x97, 0x98, 0x9F,
        0xB5, 0xB6, 0xB7, 0xB8, 0x9F
    };

    static const char PROGMEM raise_oled[] = {
        0x95, 0x96, 0x99, 0x9A, 0x9F,
        0xB5, 0xB6, 0xB9, 0xBA, 0x9F
    };

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(base_oled, false);
            break;
        case _RAISE:
            oled_write_P(raise_oled, false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    bool caps_on = host_keyboard_led_state().caps_lock || is_caps_word_on();
    oled_write_P(caps_on ? PSTR("CAPS \n") : PSTR("     \n"), false);
}

void render_os(void) {
    static const char PROGMEM inux_logo[] = {
        0x85, 0x86, 0x87, 0x88, 0x89,
        0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
        0x8F, 0x90, 0x91, 0x92, 0x93,
        0xAF, 0xB0, 0xB1, 0xB2, 0xB3
    };

    static const char PROGMEM macos_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4,
        0x8A, 0x8B, 0x8C, 0x8D, 0x8E,
        0xAA, 0xAB, 0xAC, 0xAD, 0xAE
    };

    if (is_macos) {
        oled_write_P(macos_logo, false);
        oled_write_P(PSTR("\n MAC "), false);
        // oled_write_ln_P(PSTR("MACOS\n"), false);
    } else {
        oled_write_P(inux_logo, false);
        oled_write_P(PSTR("\nLINUX"), false);
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
