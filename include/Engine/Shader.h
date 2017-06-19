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

#include <glad\glad.h>
#include <string>

namespace engine {

    class Shader
    {
    public:
        Shader(const std::string & data,
               const GLenum & type);
        ~Shader();

    public:
        inline unsigned int id() { return m_id; }


    private:
        // @brief Create a new shader of the given type
        unsigned int createShaderFromType(const GLenum & type);

        // @brief Try to compile the shader
        void compile();

        void getLogInfos();

    private:
        GLenum	m_type;
        GLuint	m_id;

        bool	m_isCompiled;
    };
}

