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

#include "Engine\ShaderProgram.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>

namespace engine {

    ShaderProgram::ShaderProgram(const std::string & vertexShader,
        const std::string & fragmentShader) :
        m_id{ glCreateProgram() },
        m_isLinked{ false }
    {
        m_vertexShader = createShader(vertexShader, GL_VERTEX_SHADER);
        m_fragmentShader = createShader(fragmentShader, GL_FRAGMENT_SHADER);

        link();
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_id);
    }


    void
    ShaderProgram::bind() {
        glUseProgram(m_id);
    }

    void
    ShaderProgram::unbind() {
        glUseProgram(0);
    }


    void
    ShaderProgram::setUniform(const std::string & name, const glm::mat4 & mat) const
    {
        int location = glGetUniformLocation(this->m_id, name.c_str());

        // Location should always be found
        assert(location != -1);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void
    ShaderProgram::setUniform(const std::string & name, const glm::vec3 & vec) const
    {
        int location = glGetUniformLocation(this->m_id, name.c_str());

        // Location should always be found
        assert(location != -1);
        glUniform3fv(location, 1, glm::value_ptr(vec));
    }

    Shader::UniquePtr
    ShaderProgram::createShader(const std::string & shaderData,
                                const GLenum shaderType)
    {
        // Create new shader
        Shader::UniquePtr shader = std::make_unique<Shader>(shaderData, shaderType);

        // Attach the shader to the current Shader Program
        glAttachShader(m_id, shader->id());

        return shader;
    }

    void
    ShaderProgram::link()
    {
        // Link shaders
        glLinkProgram(m_id);

        // Get link status
        GLint linkStatus;
        glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);

        // And check if shader linking failed
        m_isLinked = (linkStatus == GL_TRUE);
        if (!m_isLinked)
            getLogInfos();

    }

    void
    ShaderProgram::getLogInfos() const
    {
        // Getting Log length
        GLint infoLogLength;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Create log container
        GLchar * infoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog);

        // Display log
        std::cout << infoLog << std::endl;

        // Then delete log container
        delete[] infoLog;
    }
}
