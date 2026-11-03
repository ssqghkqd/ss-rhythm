// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/input/key_code.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

namespace ss::defs
{
constexpr u32 KeyCount = 256;
constexpr u32 ButtonCount = 6;

// USB HID Usage Tables - Keyboard/Keypad Page (0x07)
// Usage ID values follow HID Usage Tables 1.7 verbatim.
// Only 0x00–0xFF are representable (KeyCode : u8).
// Reserved ranges are skipped.
enum class KeyCode : u8
{
    // ===== 0x00–0x03: protocol / error =====
    NO_EVENT = 0x00,        // Reserved (no event)
    ERROR_ROLLOVER = 0x01,  // Keyboard ErrorRollOver
    ERROR_POSTFAIL = 0x02,  // Keyboard POSTFail
    ERROR_UNDEFINED = 0x03, // Keyboard ErrorUndefined

    // ===== 0x04–0x1D: A–Z =====
    A = 0x04, // Keyboard a and A
    B = 0x05, // Keyboard b and B
    C = 0x06, // Keyboard c and C
    D = 0x07, // Keyboard d and D
    E = 0x08, // Keyboard e and E
    F = 0x09, // Keyboard f and F
    G = 0x0A, // Keyboard g and G
    H = 0x0B, // Keyboard h and H
    I = 0x0C, // Keyboard i and I
    J = 0x0D, // Keyboard j and J
    K = 0x0E, // Keyboard k and K
    L = 0x0F, // Keyboard l and L
    M = 0x10, // Keyboard m and M
    N = 0x11, // Keyboard n and N
    O = 0x12, // Keyboard o and O
    P = 0x13, // Keyboard p and P
    Q = 0x14, // Keyboard q and Q
    R = 0x15, // Keyboard r and R
    S = 0x16, // Keyboard s and S
    T = 0x17, // Keyboard t and T
    U = 0x18, // Keyboard u and U
    V = 0x19, // Keyboard v and V
    W = 0x1A, // Keyboard w and W
    X = 0x1B, // Keyboard x and X
    Y = 0x1C, // Keyboard y and Y
    Z = 0x1D, // Keyboard z and Z

    // ===== 0x1E–0x27: 1–0 =====
    NUM_1 = 0x1E, // Keyboard 1 and !
    NUM_2 = 0x1F, // Keyboard 2 and @
    NUM_3 = 0x20, // Keyboard 3 and #
    NUM_4 = 0x21, // Keyboard 4 and $
    NUM_5 = 0x22, // Keyboard 5 and %
    NUM_6 = 0x23, // Keyboard 6 and ^
    NUM_7 = 0x24, // Keyboard 7 and &
    NUM_8 = 0x25, // Keyboard 8 and *
    NUM_9 = 0x26, // Keyboard 9 and (
    NUM_0 = 0x27, // Keyboard 0 and )

    // ===== 0x28–0x38: controls & punctuation =====
    ENTER = 0x28,      // Keyboard Return (ENTER)
    ESC = 0x29,        // Keyboard ESCAPE
    BACKSPACE = 0x2A,  // Keyboard DELETE (Backspace)
    TAB = 0x2B,        // Keyboard Tab
    SPACE = 0x2C,      // Keyboard Spacebar
    MINUS = 0x2D,      // Keyboard - and _
    EQUAL = 0x2E,      // Keyboard = and +
    LBRACKET = 0x2F,   // Keyboard [ and {
    RBRACKET = 0x30,   // Keyboard ] and }
    BACKSLASH = 0x31,  // Keyboard \ and |
    HASH_TILDE = 0x32, // Keyboard Non-US # and ~
    SEMICOLON = 0x33,  // Keyboard ; and :
    APOSTROPHE = 0x34, // Keyboard ' and "
    GRAVE = 0x35,      // Keyboard Grave Accent and Tilde
    COMMA = 0x36,      // Keyboard , and <
    DOT = 0x37,        // Keyboard . and >
    SLASH = 0x38,      // Keyboard / and ?

    // ===== 0x39: caps lock =====
    CAPSLOCK = 0x39, // Keyboard Caps Lock

    // ===== 0x3A–0x45: F1–F12 =====
    F1 = 0x3A,  // Keyboard F1
    F2 = 0x3B,  // Keyboard F2
    F3 = 0x3C,  // Keyboard F3
    F4 = 0x3D,  // Keyboard F4
    F5 = 0x3E,  // Keyboard F5
    F6 = 0x3F,  // Keyboard F6
    F7 = 0x40,  // Keyboard F7
    F8 = 0x41,  // Keyboard F8
    F9 = 0x42,  // Keyboard F9
    F10 = 0x43, // Keyboard F10
    F11 = 0x44, // Keyboard F11
    F12 = 0x45, // Keyboard F12

    // ===== 0x46–0x4E: nav / UI =====
    PRINTSCREEN = 0x46, // Keyboard PrintScreen
    SCROLLLOCK = 0x47,  // Keyboard Scroll Lock
    PAUSE = 0x48,       // Keyboard Pause
    INSERT = 0x49,      // Keyboard Insert
    HOME = 0x4A,        // Keyboard Home
    PAGEUP = 0x4B,      // Keyboard PageUp
    DELETE = 0x4C,      // Keyboard Delete Forward
    END = 0x4D,         // Keyboard End
    PAGEDOWN = 0x4E,    // Keyboard PageDown

    // ===== 0x4F–0x52: arrow keys =====
    RIGHT = 0x4F, // Keyboard RightArrow
    LEFT = 0x50,  // Keyboard LeftArrow
    DOWN = 0x51,  // Keyboard DownArrow
    UP = 0x52,    // Keyboard UpArrow

    // ===== 0x53–0x63: keypad =====
    KP_NUMLOCK = 0x53,  // Keypad Num Lock and Clear
    KP_SLASH = 0x54,    // Keypad /
    KP_ASTERISK = 0x55, // Keypad *
    KP_MINUS = 0x56,    // Keypad -
    KP_PLUS = 0x57,     // Keypad +
    KP_ENTER = 0x58,    // Keypad ENTER
    KP_1 = 0x59,        // Keypad 1 and End
    KP_2 = 0x5A,        // Keypad 2 and Down Arrow
    KP_3 = 0x5B,        // Keypad 3 and PageDn
    KP_4 = 0x5C,        // Keypad 4 and Left Arrow
    KP_5 = 0x5D,        // Keypad 5
    KP_6 = 0x5E,        // Keypad 6 and Right Arrow
    KP_7 = 0x5F,        // Keypad 7 and Home
    KP_8 = 0x60,        // Keypad 8 and Up Arrow
    KP_9 = 0x61,        // Keypad 9 and PageUp
    KP_0 = 0x62,        // Keypad 0 and Insert
    KP_DOT = 0x63,      // Keypad . and Delete

    // ===== 0x64–0x67: misc =====
    NON_US_BACKSLASH = 0x64, // Keyboard Non-US \ and |
    APPLICATION = 0x65,      // Keyboard Application
    POWER = 0x66,            // Keyboard Power
    KP_EQUAL = 0x67,         // Keypad =

    // ===== 0x68–0x73: F13–F24 =====
    F13 = 0x68, // Keyboard F13
    F14 = 0x69, // Keyboard F14
    F15 = 0x6A, // Keyboard F15
    F16 = 0x6B, // Keyboard F16
    F17 = 0x6C, // Keyboard F17
    F18 = 0x6D, // Keyboard F18
    F19 = 0x6E, // Keyboard F19
    F20 = 0x6F, // Keyboard F20
    F21 = 0x70, // Keyboard F21
    F22 = 0x71, // Keyboard F22
    F23 = 0x72, // Keyboard F23
    F24 = 0x73, // Keyboard F24

    // ===== 0x74–0x81: app / media-ish =====
    EXECUTE = 0x74,  // Keyboard Execute
    HELP = 0x75,     // Keyboard Help
    MENU = 0x76,     // Keyboard Menu
    SELECT = 0x77,   // Keyboard Select
    STOP = 0x78,     // Keyboard Stop
    AGAIN = 0x79,    // Keyboard Again
    UNDO = 0x7A,     // Keyboard Undo
    CUT = 0x7B,      // Keyboard Cut
    COPY = 0x7C,     // Keyboard Copy
    PASTE = 0x7D,    // Keyboard Paste
    FIND = 0x7E,     // Keyboard Find
    MUTE = 0x7F,     // Keyboard Mute
    VOL_UP = 0x80,   // Keyboard Volume Up
    VOL_DOWN = 0x81, // Keyboard Volume Down

    // ===== 0x82–0x86: locking + keypad extra =====
    LOCKING_CAPS = 0x82,   // Keyboard Locking Caps Lock
    LOCKING_NUM = 0x83,    // Keyboard Locking Num Lock
    LOCKING_SCROLL = 0x84, // Keyboard Locking Scroll Lock
    KP_COMMA = 0x85,       // Keypad Comma
    KP_EQUAL_SIGN = 0x86,  // Keypad Equal Sign

    // ===== 0x87–0x8F: international =====
    INTERNATIONAL1 = 0x87, // Keyboard International1
    INTERNATIONAL2 = 0x88, // Keyboard International2
    INTERNATIONAL3 = 0x89, // Keyboard International3
    INTERNATIONAL4 = 0x8A, // Keyboard International4
    INTERNATIONAL5 = 0x8B, // Keyboard International5
    INTERNATIONAL6 = 0x8C, // Keyboard International6
    INTERNATIONAL7 = 0x8D, // Keyboard International7
    INTERNATIONAL8 = 0x8E, // Keyboard International8
    INTERNATIONAL9 = 0x8F, // Keyboard International9

    // ===== 0x90–0x98: LANG =====
    LANG1 = 0x90, // Keyboard LANG1
    LANG2 = 0x91, // Keyboard LANG2
    LANG3 = 0x92, // Keyboard LANG3
    LANG4 = 0x93, // Keyboard LANG4
    LANG5 = 0x94, // Keyboard LANG5
    LANG6 = 0x95, // Keyboard LANG6
    LANG7 = 0x96, // Keyboard LANG7
    LANG8 = 0x97, // Keyboard LANG8
    LANG9 = 0x98, // Keyboard LANG9

    // ===== 0x99–0xA4: misc system =====
    ALT_ERASE = 0x99,   // Keyboard Alternate Erase
    SYSREQ = 0x9A,      // Keyboard SysReq/Attention
    CANCEL = 0x9B,      // Keyboard Cancel
    CLEAR = 0x9C,       // Keyboard Clear
    PRIOR = 0x9D,       // Keyboard Prior
    RETURN = 0x9E,      // Keyboard Return
    SEPARATOR = 0x9F,   // Keyboard Separator
    OUT = 0xA0,         // Keyboard Out
    OPER = 0xA1,        // Keyboard Oper
    CLEAR_AGAIN = 0xA2, // Keyboard Clear/Again
    CRSEL_PROPS = 0xA3, // Keyboard CrSel/Props
    EXSEL = 0xA4,       // Keyboard ExSel
    // 0xA5–0xAF Reserved

    // ===== 0xB0–0xDD: keypad extensions =====
    KP_00 = 0xB0,               // Keypad 00
    KP_000 = 0xB1,              // Keypad 000
    THOUSANDS_SEPARATOR = 0xB2, // Thousands Separator
    DECIMAL_SEPARATOR = 0xB3,   // Decimal Separator
    CURRENCY_UNIT = 0xB4,       // Currency Unit
    CURRENCY_SUBUNIT = 0xB5,    // Currency Sub-unit
    KP_LPAREN = 0xB6,           // Keypad (
    KP_RPAREN = 0xB7,           // Keypad )
    KP_LBRACE = 0xB8,           // Keypad {
    KP_RBRACE = 0xB9,           // Keypad }
    KP_TAB = 0xBA,              // Keypad Tab
    KP_BACKSPACE = 0xBB,        // Keypad Backspace
    KP_A = 0xBC,                // Keypad A
    KP_B = 0xBD,                // Keypad B
    KP_C = 0xBE,                // Keypad C
    KP_D = 0xBF,                // Keypad D
    KP_E = 0xC0,                // Keypad E
    KP_F = 0xC1,                // Keypad F
    KP_XOR = 0xC2,              // Keypad XOR
    KP_CARET = 0xC3,            // Keypad ^
    KP_PERCENT = 0xC4,          // Keypad %
    KP_LT = 0xC5,               // Keypad <
    KP_GT = 0xC6,               // Keypad >
    KP_AMP = 0xC7,              // Keypad &
    KP_DBL_AMP = 0xC8,          // Keypad &&
    KP_PIPE = 0xC9,             // Keypad |
    KP_DBL_PIPE = 0xCA,         // Keypad ||
    KP_COLON = 0xCB,            // Keypad :
    KP_HASH = 0xCC,             // Keypad #
    KP_SPACE = 0xCD,            // Keypad Space
    KP_AT = 0xCE,               // Keypad @
    KP_EXCLAM = 0xCF,           // Keypad !
    KP_MEM_STORE = 0xD0,        // Keypad Memory Store
    KP_MEM_RECALL = 0xD1,       // Keypad Memory Recall
    KP_MEM_CLEAR = 0xD2,        // Keypad Memory Clear
    KP_MEM_ADD = 0xD3,          // Keypad Memory Add
    KP_MEM_SUBTRACT = 0xD4,     // Keypad Memory Subtract
    KP_MEM_MULTIPLY = 0xD5,     // Keypad Memory Multiply
    KP_MEM_DIVIDE = 0xD6,       // Keypad Memory Divide
    KP_PLUSMINUS = 0xD7,        // Keypad +/-
    KP_CLEAR = 0xD8,            // Keypad Clear
    KP_CLEAR_ENTRY = 0xD9,      // Keypad Clear Entry
    KP_BINARY = 0xDA,           // Keypad Binary
    KP_OCTAL = 0xDB,            // Keypad Octal
    KP_DECIMAL = 0xDC,          // Keypad Decimal
    KP_HEXADECIMAL = 0xDD,      // Keypad Hexadecimal
    // 0xDE–0xDF Reserved

    // ===== 0xE0–0xE7: modifiers =====
    LCTRL = 0xE0,  // Keyboard LeftControl
    LSHIFT = 0xE1, // Keyboard LeftShift
    LALT = 0xE2,   // Keyboard LeftAlt
    LGUI = 0xE3,   // Keyboard Left GUI
    RCTRL = 0xE4,  // Keyboard RightControl
    RSHIFT = 0xE5, // Keyboard RightShift
    RALT = 0xE6,   // Keyboard RightAlt
    RGUI = 0xE7,   // Keyboard Right GUI
    // 0xE8–0xFFFF Reserved
};

// USB HID Usage Tables - Button Page (0x09)
enum class ButtonCode : u8
{
    NONE = 0x00,   // No Button Pressed (Button Page Usage 0)
    LEFT = 0x01,   // 1
    RIGHT = 0x02,  // 2
    MIDDLE = 0x03, // Middle / Wheel-click
    X1 = 0x04,     // X1 / Back 侧键4
    X2 = 0x05,     // X2 / Forward 侧键5

    // 如需更多继续 BUTTON_6 .. BUTTON_N，HID 标准允许任意大
};
} // namespace ss::defs