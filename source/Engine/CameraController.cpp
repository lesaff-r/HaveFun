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
#include <glm\gtc\quaternion.hpp>
#include <cassert>

namespace engine {

    void
    CameraController::update(CameraData & camData)
    {
        mTimer.update();

        if (m_movement.move)
            move(camData);
        if (m_rotate)
            rotate(camData);
        if (m_zoom)
            zoom(camData);
    }

    void
    CameraController::move(CameraData & camData)
    {
        // Get all camera Datas to be updated
        glm::vec3 & position = camData.position;
        glm::vec3 & target = camData.target;
        glm::vec3 & camUp = camData.camUp;
        glm::mat4 & viewMat = camData.viewMat;

        // Movement vector to update the camera
        glm::vec3 movement{ 0, 0, 0 };
        movement.y += m_movement.up ? 1 : 0;
        movement.y += m_movement.down ? -1 : 0;
        movement.x += m_movement.left ? -1 : 0;
        movement.x += m_movement.right ? 1 : 0;

        // Calc Camera direction and side vector
        glm::vec3 direction = glm::normalize(target - position);
        glm::vec3 side = glm::cross(direction, normalize(camUp));

        // Update new position
        float speed = 2.0f * mTimer.getElapsedTime();
        position += movement.z * direction * speed;
        position += movement.y * camUp * speed;
        position += movement.x * side * speed;

        // Update new target with updated position and direction
        target = position + direction;

        // Update view matrix
        viewMat = glm::lookAt(position, target, camUp);
    }

    void
    CameraController::rotate(CameraData & camData)
    {
        // Get all camera Datas to be updated
        glm::vec3 & position = camData.position;
        glm::vec3 & target = camData.target;
        glm::vec3 & camUp = camData.camUp;
        glm::mat4 & viewMat = camData.viewMat;

        // Calc Camera direction and side vector
        glm::vec3 direction = glm::normalize(target - position);
        glm::vec3 side = glm::cross(direction, normalize(camUp));

        // Rotation Speed
        float speed = 0.001f;

        if (m_mouseLeftDown)
        {
            // Rotate around x-axis
            glm::quat qy = glm::angleAxis(m_mousePosDelta.y * speed, side);
            glm::mat3 rotY(qy);
            direction = direction * rotY;
            camUp = camUp * rotY;

            // Rotate around y-axis
            glm::quat qx = glm::angleAxis(m_mousePosDelta.x * speed, camUp);
            glm::mat3 rotX(qx);
            direction = direction * rotX;

            // Update target with new direction
            target = position + direction;
        }
        else if (m_mouseRightDown)
        {
            // Nothing for now
        }

        // Update view matrix
        viewMat = glm::lookAt(position, target, camUp);

        // Rotation done
        m_rotate = false;
    }

    void
    CameraController::zoom(CameraData & camData)
    {
        // Get all camera Datas to be updated
        glm::vec3 & position = camData.position;
        glm::vec3 & target = camData.target;
        glm::vec3 & camUp = camData.camUp;
        glm::mat4 & viewMat = camData.viewMat;

        // Calc Camera direction and side vector
        glm::vec3 direction = glm::normalize(target - position);

        float speed = 0.2f;
        glm::vec3 movement;
        movement = direction * m_wheelOffset.y * speed;

        // Update position and target
        position += movement;
        target += movement;

        // Update view matrix
        viewMat = glm::lookAt(position, target, camUp);

        m_zoom = false;
    }


    bool
    CameraController::onEvent(const SEvent & event)
    {
        if (event.EventType == SEvent::EEventType::EET_KEY_EVENT &&
            event.KeyEvent.Pressed != SEvent::SKeyEvent::State::Repeat)
            onKeyEvent(event);
        else if (event.EventType == SEvent::EEventType::EET_MOUSE_EVENT)
            onMouseEvent(event);
        return true;
    }

    void
    CameraController::onKeyEvent(const SEvent & event)
    {
        // State should never be Repeat
        assert(event.KeyEvent.Pressed != SEvent::SKeyEvent::State::Repeat);

        bool press = static_cast<bool>(event.KeyEvent.Pressed);

        switch (event.KeyEvent.Key)
        {
        case EKeyCode::EKC_W:
            m_movement.up = press;
            break;
        case EKeyCode::EKC_S:
            m_movement.down = press;
            break;
        case EKeyCode::EKC_A:
            m_movement.left = press;
            break;
        case EKeyCode::EKC_D:
            m_movement.right = press;
            break;
        default:
            break;
        }
    }

    void
    CameraController::onMouseEvent(const SEvent & event)
    {
        switch (event.MouseEvent.type)
        {
        case SEvent::SMouseEvent::Type::LButtonDown:
            m_mousePos = event.MouseEvent.pos;
            m_mouseLeftDown = true;
            break;
        case SEvent::SMouseEvent::Type::LButtonUp:
            m_mousePos = event.MouseEvent.pos;
            m_mouseLeftDown = false;
            break;
        case SEvent::SMouseEvent::Type::RButtonDown:
            m_mousePos = event.MouseEvent.pos;
            m_mouseRightDown = true;
            break;
        case SEvent::SMouseEvent::Type::RButtonUp:
            m_mousePos = event.MouseEvent.pos;
            m_mouseRightDown = false;
            break;
        case SEvent::SMouseEvent::Type::Move:
            if (m_mouseLeftDown || m_mouseRightDown)
            {
                m_mousePosDelta = event.MouseEvent.pos - m_mousePos;
                m_mousePos = event.MouseEvent.pos;
                m_rotate = true;
            }
            break;
        case SEvent::SMouseEvent::Type::Wheel:
            m_wheelOffset = event.MouseEvent.wheelOffset;
            m_zoom = true;
            break;
        default:
            break;
        }
    }
}