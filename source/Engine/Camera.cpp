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

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace engine {

    Camera::Camera() :
        m_position{0.0f, 0.0f, 3.0f},
        m_target{0.0f, 0.0f, 0.0f},
        m_worldUp{0.0f, 1.0f, 0.0f},
        m_view{0}
    {
        m_view = glm::lookAt(m_position,
                           m_target,
                           m_worldUp);
    }

    bool
    Camera::onEvent(const SEvent & event)
    {
        if (event.EventType == EEventType::EET_KEY_EVENT)
            move();
        return true;
    }

    void
    Camera::move()
    {
        std::cout << "I'm moving!" << std::endl;
    }
}