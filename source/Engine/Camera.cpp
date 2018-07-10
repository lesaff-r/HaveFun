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

#include "Engine\Camera.h"
#include "Engine\Event.h"
#include "Engine\KeyCodes.h"

#include <glad\glad.h>
#include <glm\gtc\matrix_transform.hpp>

namespace engine {

    Camera::Camera()
    {
        m_camData.viewMat = glm::lookAt(m_camData.position, m_camData.target, m_camData.camUp);
        m_camData.projectionMat = glm::perspective(m_camData.fov, m_camData.aspectRatio,
                                                   m_camData.nearPlane, m_camData.farPlane);
        //glViewport(0, 0, 1024, 768);
    }


    void
    Camera::update()
    {
        if (p_camController)
            p_camController->update(m_camData);
    }


    bool
    Camera::onEvent(const SEvent & event)
    {
        if (event.EventType == SEvent::EEventType::EET_RESIZE)
            glViewport(0, 0, event.ResizeEvent.width, event.ResizeEvent.heigh);
        else if (p_camController)
            p_camController->onEvent(event);
        return true;
    }

    void
    Camera::attachController(CameraController::UniquePtr pController)
    {
        p_camController = std::move(pController);
    }
}