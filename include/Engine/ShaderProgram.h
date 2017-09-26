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

#include "Engine\Shader.h"

#include <glad\glad.h>
#include <glm\mat4x4.hpp>
#include <string>
#include <memory>

namespace engine {    

    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string & vertexShader,
                      const std::string & fragmentShader);
        ~ShaderProgram();

    public:
        void bind();
        void unbind();

    public:
        void setUniform(const std::string & name, const glm::mat4 & mat) const;


    private:
        // @brief Create a new Shader object 
        Shader::UniquePtr createShader(const std::string & shader,
                                       const GLenum shaderType);

        // @brief Link all attached shader to the Shader Program
        void link();

        // Get debug infos
        void getLogInfos() const;

    private:
        GLuint  m_id;

        bool    m_isLinked;

    private:
        // For now
        Shader::UniquePtr m_vertexShader;
        Shader::UniquePtr m_fragmentShader;
    };
}
