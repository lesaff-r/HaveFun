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

#include "Engine\BufferObject.h"

namespace engine {

    BufferObject::BufferObject(const GLenum type, const GLenum usage) :
        m_vbo{0},
        m_type{type},
        m_usage{usage}
    {
        glGenBuffers(1, &m_vbo);
    }


    void
    BufferObject::init(const GLsizeiptr size, const GLvoid * data) const {
        glBufferData(m_type, size, data, m_usage);
    }

    void
    BufferObject::attribute(const GLuint index, const GLint size,
                            const GLsizei stride, const GLvoid * pointer) const
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size,
                              GL_FLOAT, GL_FALSE,
                              stride, pointer);
    }
}
