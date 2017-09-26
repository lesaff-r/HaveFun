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

#include <memory>

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
        void keyEvent(const SEvent & event);
        void mouseEvent(const SEvent & event);

    private:
        // Variables for camera movement
        bool m_up = false;
        bool m_down = false;
        bool m_left = false;
        bool m_right = false;
    };
}