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

#include "Engine\Timer.h"

#include <memory>
#include <glm/vec2.hpp>

namespace engine {
    struct SEvent;
    struct CameraData;
}

namespace engine {

    class CameraController
    {
    public:
        using UniquePtr = std::unique_ptr<CameraController>;

    public:
        void update(CameraData & camData);
        bool onEvent(const SEvent & event);


    private:
        void onKeyEvent(const SEvent & event);
        void onMouseEvent(const SEvent & event);

        void move(CameraData & camData);
        void rotate(CameraData & camData);
        void zoom(CameraData & camData);

    private:
        Timer mTimer;

        // Variables for camera movement
        union
        {
            struct
            {
                bool up : 1;
                bool down : 1;
                bool left : 1;
                bool right : 1;
            };
            bool move = false;
        } m_movement;

        bool m_rotate = false;
        bool m_zoom = false;

        bool m_mouseLeftDown = false;
        bool m_mouseRightDown = false;
        bool m_mouseMidddleDown = false;

        glm::vec2 m_mousePos;
        glm::vec2 m_mousePosDelta;
        glm::vec2 m_wheelOffset;
    };
}