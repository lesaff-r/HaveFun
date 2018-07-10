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

#include "Engine\Camera.h"
#include "Engine\Object.h"
#include "Engine\ShaderProgram.h"

#include <list>
#include <memory>

namespace engine {
    struct SEvent;
}

namespace engine {

    // TODO : Need sceneNodes and a SceneManager 
    class Scene
    {
    public:
        Scene();


    public:
        void update();
        void render();

        bool onEvent(const SEvent & event);


    private:
        // The active Camera used to view the scene
        Camera m_camera;

        // All the objects in the Scene
        std::list<Object::UniquePtr>  m_objects;

        // TODO: For now but will later be a material in the object
        std::unique_ptr<ShaderProgram>      m_shaderProgram;
    };
}
