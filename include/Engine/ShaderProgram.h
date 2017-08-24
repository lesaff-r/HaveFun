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


    private:
        // @brief Create a new Shader object 
        std::unique_ptr<Shader> createShader(const std::string & shader,
                                             const GLenum shaderType);

        // @brief Link all attached shader to the Shader Program
        void link();

        void getLogInfos() const;

    private:
        GLuint  m_id;

        bool    m_isLinked;

    private:
        // For now
        std::unique_ptr<Shader> m_vertexShader;
        std::unique_ptr<Shader> m_fragmentShader;
    };
}