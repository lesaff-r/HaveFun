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
        inline const glm::mat4 & getViewMatrix()        { return m_view; }
        inline const glm::mat4 & getProjectionMatrix()  { return m_projection; }

    public:
        void update();
        bool onEvent(const SEvent & event);


    private:
        void move(const SEvent & event);

    private:
        // TODO: Need CamData structure
        // The camera position
        glm::vec3   m_position;

        // The position the camera is looking at
        glm::vec3   m_target;

        // Defines the Up vector from the world
        // @note Shoud be Y up
        glm::vec3   m_camUp;

        // The view matrix for the camera
        glm::mat4   m_view;

        // The projection matrix for the camera
        glm::mat4   m_projection;

        // Perspective data for porjection matrix
        float m_fov = 45.0f;
        float m_aspectRatio = 4.0f/3.0f;
        float m_nearZ = 0.1f;
        float m_farZ = 1000.0f;

        // TODO: Need Camera controller
        // Variables for camera movement
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    };
}