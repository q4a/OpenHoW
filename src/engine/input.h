/* OpenHoW
 * Copyright (C) 2017-2019 Mark Sowden <markelswo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#define INPUT_MAX_CONTROLLERS   4

enum {
    ACTION_MOVE_FORWARD,
    ACTION_MOVE_BACKWARD,
    ACTION_TURN_LEFT,
    ACTION_TURN_RIGHT,

    ACTION_AIM,
    ACTION_AIM_UP,
    ACTION_AIM_DOWN,

    ACTION_JUMP,

    ACTION_PAUSE,

    ACTION_FIRE,

    ACTION_SELECT,
    ACTION_DESELECT,

    INPUT_MAX_ACTIONS
};

enum {
    PORK_BUTTON_CROSS,
    PORK_BUTTON_CIRCLE,
    PORK_BUTTON_TRIANGLE,
    PORK_BUTTON_SQUARE,

    PORK_BUTTON_R1,
    PORK_BUTTON_R2,
    PORK_BUTTON_R3,

    PORK_BUTTON_L1,
    PORK_BUTTON_L2,
    PORK_BUTTON_L3,

    PORK_BUTTON_UP,
    PORK_BUTTON_DOWN,
    PORK_BUTTON_LEFT,
    PORK_BUTTON_RIGHT,

    PORK_BUTTON_START,
    PORK_BUTTON_SELECT,

    PORK_MAX_BUTTONS
};

enum {
    PORK_MOUSE_BUTTON_LEFT,
    PORK_MOUSE_BUTTON_RIGHT,
    PORK_MOUSE_BUTTON_MIDDLE,

    INPUT_MAX_MOUSE_BUTTONS
};

enum {
    INPUT_JOYSTICK_LEFT,
    INPUT_JOYSTICK_RIGHT,
    INPUT_JOYSTICK_TRIGGERS,

    INPUT_MAX_JOYSTICKS
};

enum {
    PORK_KEY_F1 = 128,
    PORK_KEY_F2,
    PORK_KEY_F3,
    PORK_KEY_F4,
    PORK_KEY_F5,
    PORK_KEY_F6,
    PORK_KEY_F7,
    PORK_KEY_F8,
    PORK_KEY_F9,
    PORK_KEY_F10,
    PORK_KEY_F11,
    PORK_KEY_F12,

    PORK_KEY_PAUSE,
    PORK_KEY_INSERT,
    PORK_KEY_HOME,

    PORK_KEY_UP,
    PORK_KEY_DOWN,
    PORK_KEY_LEFT,
    PORK_KEY_RIGHT,

    PORK_KEY_SPACE,

    PORK_KEY_PAGEUP,
    PORK_KEY_PAGEDOWN,

    PORK_KEY_LCTRL,
    PORK_KEY_LSHIFT,
    PORK_KEY_LALT,
    PORK_KEY_RCTRL,
    PORK_KEY_RSHIFT,
    PORK_KEY_RALT,

    PORK_KEY_ESCAPE,

    INPUT_MAX_KEYS
};

PL_EXTERN_C

void Input_Initialize(void);
void Input_ResetStates(void);

void Input_SetKeyboardFocusCallback(void(*Callback)(int key, bool is_pressed));
void Input_SetTextFocusCallback(void(*Callback)(const char* c));

struct PLVector2 Input_GetJoystickState(unsigned int controller, unsigned int joystick);
bool Input_GetKeyState(int key);
bool Input_GetButtonState(unsigned int controller, int button);
bool Input_GetActionState(unsigned int controller, int action);

void Input_SetAxisState(unsigned int controller, unsigned int axis, int status);
void Input_SetButtonState(unsigned int controller, int button, bool status);
void Input_SetKeyState(int key, bool status);
void Input_SetMouseState(int x, int y, int button, bool status);

void Input_AddTextCharacter(const char* c);

PL_EXTERN_C_END
