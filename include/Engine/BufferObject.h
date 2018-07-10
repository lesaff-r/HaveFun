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
        BufferObject(const GLenum type, const GLenum usage);

    public:
        // @brief Create memory space and store data for current bound Vertex Buffer Object
        void init(const GLsizeiptr size, const GLvoid * data) const;

        // @brief Define the vertex buffer data interpretation for current bound Vertex Buffer Object
        void attribute(const GLuint index, const GLint size,
                       const GLsizei stride, const GLvoid * pointer) const;


        inline void bind() const {
            glBindBuffer(m_type, m_vbo);
        }
        inline void unbind() const {
            glBindBuffer(m_type, 0);
        }


    private:
        // @brief Vertex Buffer Object Id
        GLuint m_vbo;

        const GLenum m_type;
        const GLenum m_usage;
    };
}
