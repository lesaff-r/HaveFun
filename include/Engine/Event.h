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

#include <glm/vec2.hpp>

namespace engine {
    enum class EKeyCode;
}

namespace engine {

    struct SEvent {

        // Defines the type of the Input
        enum class EEventType
        {
            EET_KEY_EVENT,
            EET_MOUSE_EVENT,
            EET_RESIZE
        };

        EEventType EventType;   // Type of the current Event


        // Container for Resize Event
        struct SResizeEvent
        {
            int width;          // The width of the Window after resize
            int heigh;          // The heigh of the Window after resize
        };

        // Container for Keyboard Events
        struct SKeyEvent
        {
            enum class State
            {
                Release,
                Press,
                Repeat
            };

            State Pressed;      // Status to know if the Key is Pressed or Released
            EKeyCode Key;       // The Key code

            // TODO: Add modifiers (shift, alt, ctrl) ?
        };

        // Container for Mouse Events
        struct SMouseEvent
        {
            enum class Type
            {
                LButtonDown,
                LButtonUp,
                RButtonDown,
                RButtonUp,
                MidButtonDown,
                MidButtonUp,
                Move,
                Wheel
            };

            Type type;          // Status to know which Key is Pressed or Released
            glm::vec2 pos;      // The mouse position
            float wheel = .0f;        // The mouse wheel offset if Event Type is SMouseEvent::Type::Wheel, otherwise zero 
        };

        SEvent() {}
        // A union to get the informations about the current Input Event
        union
        {
            struct SResizeEvent ResizeEvent;
            struct SKeyEvent    KeyEvent;
            struct SMouseEvent  MouseEvent;
        };
    };
}