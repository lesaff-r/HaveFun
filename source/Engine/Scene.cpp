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
#include "Engine\Event.h"

#include <glm\gtx\transform.hpp>

namespace engine {

    Scene::Scene()
    {
        // TODO: Something better for shader loading
        // Load default shader
        const std::string vertexShaderSource =
            std::move(Shader::get(RESOURCES_PATH "default.vs.glsl"));
        const std::string fragmentShaderSource =
            std::move(Shader::get(RESOURCES_PATH "default.fs.glsl"));

        // Create new Shader Program
        m_shaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource,
														  fragmentShaderSource);
        // TODO: m_shaderProgram->attachShader()?

        // TODO: Objects & Scene loader ...

        // Attach controller to camera
        m_camera.attachController(std::make_unique<CameraController>());

        // New Test Object
        m_objects.emplace_back(std::make_shared<Object>());
    }


    void
    Scene::update()
    {
        m_camera.update();
    }

    void
    Scene::render()
    {
        // TODO: Should be in a renderer!


        // Clear Buffers
        glClearColor(0.2f, 0.2f, .2f, 0);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        const glm::mat4 & view = m_camera.getViewMatrix();
        const glm::mat4 & projection = m_camera.getProjectionMatrix();


        // Bind Shader Program
        m_shaderProgram->bind();

        // TODO: for now but should be in Model
        glm::mat4 model{ 1 };

        glm::mat4 mvp = projection * view * model;
        m_shaderProgram->setUniform("mvp", mvp);

        // TODO: Here for now
        m_shaderProgram->setUniform("light_color", m_light.intensity);

        for (auto & object : m_objects)
        {
            m_renderer.render(object);
        }

        // Unbind Shader Program
        m_shaderProgram->unbind();
    }


    bool
    Scene::onEvent(const SEvent & event)
    {
        return m_camera.onEvent(event);
    }
}
