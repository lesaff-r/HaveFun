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

#include "Engine\CameraController.h"
#include "Engine\Camera.h"
#include "Engine\Event.h"
#include "Engine\KeyCodes.h"

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cassert>
#include <iostream>
namespace engine {

    void
    CameraController::update(CameraData & camData)
    {
        // Get all camera Datas to be updated
        glm::vec3 & position = camData.position;
        glm::vec3 & target = camData.target;
        glm::vec3 & camUp = camData.camUp;
        glm::mat4 & viewMat = camData.viewMat;

        // Movement vector to update the camera
        glm::vec3 movement{ 0, 0, 0 };
        movement.y += m_up ? 1 : 0;
        movement.y += m_down ? -1 : 0;
        movement.x += m_left ? -1 : 0;
        movement.x += m_right ? 1 : 0;

        // Calc Camera direction and side vector
        glm::vec3 direction = glm::normalize(target - position);
        glm::vec3 side = glm::cross(direction, normalize(camUp));

        // TODO: need elapsed time!
        // Update new position
        float speed = 0.001f;
        position += movement.z * direction * speed;
        position += movement.y * camUp * speed;
        position += movement.x * side * speed;

        // Update new target with updated position and direction
        target = position + direction;

        // Update view matrix
        viewMat = glm::lookAt(position, target, camUp);
    }


    bool
    CameraController::onEvent(const SEvent & event)
    {
        if (event.EventType == SEvent::EEventType::EET_KEY_EVENT &&
            event.KeyEvent.Pressed != SEvent::SKeyEvent::State::Repeat)
            keyEvent(event);
        else if (event.EventType == SEvent::EEventType::EET_MOUSE_EVENT)
            mouseEvent(event);
        return true;
    }

    void
    CameraController::keyEvent(const SEvent & event)
    {
        // State should never be Repeat
        assert(event.KeyEvent.Pressed != SEvent::SKeyEvent::State::Repeat);

        bool press = static_cast<bool>(event.KeyEvent.Pressed);

        switch (event.KeyEvent.Key)
        {
        case EKeyCode::EKC_W:
            m_up = press;
            break;
        case EKeyCode::EKC_S:
            m_down = press;
            break;
        case EKeyCode::EKC_A:
            m_left = press;
            break;
        case EKeyCode::EKC_D:
            m_right = press;
            break;
        default:
            break;
        }
    }

    void
    CameraController::mouseEvent(const SEvent & event)
    {
        
    }
}