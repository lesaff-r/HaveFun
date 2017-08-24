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

#include "Engine\EventManager.h"
#include "Engine/Window.h"
#include "Engine/Core.h"

namespace engine {

    // @note Can throw std::runtime_error on construction
    // @see Program(int ac, char * av[]);
    class Program final
    {
    public:
        // @brief Throw std::runtime_error if Window creation failed
        // @see Window::Window();
        Program(int ac, char * av[]);

    public:
        int		run(void);


    private:
        EventManager m_eventManager;
        Window       m_window;
        Core         m_core;
    };
}
