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

#include "Engine/Program.h"

namespace engine {

    Program::Program(int argc, char * argv[]) :
        m_window{ m_eventManager },
        m_core{ m_eventManager }
    {}

    int
    Program::run(void)
    {
        while (!m_window.should_close())
        {
            m_window.update();

            m_core.update();
            m_core.render();

            m_window.render();
        }
        return EXIT_SUCCESS;
    }
}
