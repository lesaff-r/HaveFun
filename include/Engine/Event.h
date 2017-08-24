//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2017 Lesaffre Remi (remi.lesaffre@gmail.com)
//

#pragma once

namespace engine {
    enum class EKeyCode;
}

namespace engine {

    // Defines the type of the Input
    enum class EEventType
    {
        EET_KEY_EVENT,
        EET_MOUSE_EVENT,
        EET_RESIZE
    };

    struct SEvent {

        // Type of the current Event
        EEventType EventType;

        // Container for Resize Event
        struct SResizeEvent
        {
            // The width of the Window after resize
            int width;

            // The heigh of the Window after resize
            int heigh;
        };

        // Container for Keyboard Events
        struct SKeyEvent
        {
            // The Key code
            EKeyCode Key;

            // Status to know if the Key is Pressed or Released
            bool Pressed;

            // TODO: Add modifiers (shift, alt, ctrl) ?
        };

        // Container for Mouse Events
        struct SMouseEvent
        {

        };

        // A union to get the informations about the current Input Event
        union
        {
            struct SResizeEvent ResizeEvent;
            struct SKeyEvent    KeyEvent;
            struct SMouseEvent  MouseEvent;
        };
    };
}