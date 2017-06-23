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

#include "config.h"
#include "Engine\Scene.h"
#include "Engine\ShaderProgram.h"

namespace engine {

    Scene::Scene()
    {
        // Load default shader
        const std::string vertexShaderSource =
            std::move(Shader::get(RESOURCES_PATH "default.vs.glsl"));
        const std::string fragmentShaderSource =
            std::move(Shader::get(RESOURCES_PATH "default.fs.glsl"));

        // Create new Shader Program
        m_shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource,
														  fragmentShaderSource);
        // TODO: m_shaderProgram->attachShader()?

        // New Test Object
        m_objects.emplace_back(std::make_unique<Object>());
    }


    void
    Scene::render()
    {
        // TODO: Should be in a renderer
        // Clear Buffers
        glClearColor(0.2f, 0.2f, .2f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        // For later
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glEnable(GL_DEPTH_TEST);

        // Bind Shader Program
        m_shaderProgram->bind();

        for (auto & object : m_objects)
        {
            object->render();
        }

        // Unbind Shader Program
        m_shaderProgram->unbind();
    }
}
