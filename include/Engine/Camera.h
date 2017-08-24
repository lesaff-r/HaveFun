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

#include <glm\glm.hpp>

namespace engine {
    struct SEvent;
}

namespace engine {

    class Camera
    {
    public:
        Camera();


    public:
        bool onEvent(const SEvent & event);


    private:
        void move();

    private:
        // The camera position
        glm::vec3   m_position;

        // The position the camera is looking at
        glm::vec3   m_target;

        // Defines the UP vector for the world
        // @note Shoud be Y up
        glm::vec3   m_worldUp;

        // The view matrix for the camera
        glm::mat4   m_view;

        // Vectors to be used later for camera movements
        glm::vec3   m_front;
        glm::vec3   m_right;
        glm::vec3   m_up;
    };
}