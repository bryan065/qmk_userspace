/*
  Copyright (c) 2022 Bryan065

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

enum userspace_custom_keycodes {
    VRSN = QK_KB,       // Print QMK Version
    KC_MAKE,            // Build QMK for keyboard
    KC_CAPSOFF,         // Caps off keycode
    RGB_DEF,
    MON_OFF,
    WIN_VER,
    MAC_VER,
    WIN_CPY,
    MAG_UP,
    NEW_SAFE_RANGE
};

enum layer_names {
    _BASE,
    _FUNCTION,
    _RGB,
    _SYSTEM,
    _LAYER_SAFE_RANGE
};
