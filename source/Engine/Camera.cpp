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

#include <glm\gtc\matrix_transform.hpp>
#include <glad\glad.h>
#include <iostream>
namespace engine {

    Camera::Camera() :
        m_position{0.0f, 0.0f, 10.0f},
        m_target{0.0f, 0.0f, 0.0f},
        m_camUp{0.0f, 1.0f, 0.0f},
        m_view{ glm::mat4{1} },
        m_projection{ glm::mat4{1} }
    {
        m_view = glm::lookAt(m_position, m_target, m_camUp);
        m_projection = glm::perspective(m_fov, m_aspectRatio, m_nearZ, m_farZ);
        //glViewport(0, 0, 1024, 768);
    }


    void
    Camera::update()
    {
        glm::vec3 movement(0, 0, 0);
        movement.y += up ? 1 : 0;
        movement.y += down ? -1 : 0;
        movement.x += left ? -1 : 0;
        movement.x += right ? 1 : 0;

        glm::vec3 direction = glm::normalize(m_target - m_position);
        glm::vec3 side = glm::cross(direction, normalize(m_camUp));

        // TODO: need elapsed time!
        // Update position
        float speed = 0.001f;
        m_position += movement.z * direction * speed;
        m_position += movement.y * m_camUp * speed;
        m_position += movement.x * side * speed;

        // Update target with new position and direction
        m_target = m_position + direction;

        // Update view matrix
        m_view = glm::lookAt(m_position, m_target, m_camUp);
    }


    bool
    Camera::onEvent(const SEvent & event)
    {
        if (event.EventType == EEventType::EET_KEY_EVENT &&
            event.KeyEvent.Pressed != EEventState::EES_REPEAT)
            move(event);
        else if (event.EventType == EEventType::EET_RESIZE)
            glViewport(0, 0, event.ResizeEvent.width, event.ResizeEvent.heigh);
        return true;
    }

    void
    Camera::move(const SEvent & event)
    {
        // State should never be Repeat
        assert (event.KeyEvent.Pressed != EEventState::EES_REPEAT);

        bool press = static_cast<bool>(event.KeyEvent.Pressed);

        switch (event.KeyEvent.Key)
        {
        case EKeyCode::EKC_W:
            up = press;
            break;
        case EKeyCode::EKC_S:
            down = press;
            break;
        case EKeyCode::EKC_A:
            left = press;
            break;
        case EKeyCode::EKC_D:
            right = press;
            break;
        default:
            break;
        }
    }
}