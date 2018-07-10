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

#include "CameraController.h"

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

namespace engine {
    struct SEvent;
}

namespace engine {

    struct CameraData
    {
        // The camera position
        glm::vec3   position = glm::vec3{ 0.0f, 0.0f, 10.0f };

        // The position the camera is looking at
        glm::vec3   target = glm::vec3{ 0.0f, 0.0f, 0.0f };

        // Defines the Up vector from the world
        // @note Shoud be Y up
        glm::vec3   camUp = glm::vec3{ 0.0f, 1.0f, 0.0f };

        // The view matrix for the camera
        glm::mat4   viewMat = glm::mat4{ 1 };

        // The projection matrix for the camera
        glm::mat4   projectionMat = glm::mat4{ 1 };

        // Perspective data for projection matrix
        float fov = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
    };

    class Camera
    {
    public:
        Camera();

    public:
        void update();
        bool onEvent(const SEvent & event);

        void attachController(CameraController::UniquePtr controller);

    public:
        inline const glm::mat4 & getViewMatrix()       { return m_camData.viewMat; }
        inline const glm::mat4 & getProjectionMatrix() { return m_camData.projectionMat; }


    private:
        CameraData m_camData;

        CameraController::UniquePtr p_camController;
    };
}