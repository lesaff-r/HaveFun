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

namespace engine {

    // @brief Encapsulation of a Vertex Buffer Object for the OpenGL API
    class BufferObject final
    {
    public:
        BufferObject(GLenum type, GLenum usage);

    public:
        // @brief Create memory space and store data for current bound Vertex Buffer Object
        void init(GLsizeiptr size, const GLvoid * data);

        void bind();
        void unbind();


    private:
        // @brief Vertex Buffer Object Id
        GLuint m_vbo;

        GLenum m_type;
        GLenum m_usage;
    };
}
