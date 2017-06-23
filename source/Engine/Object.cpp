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

#include "Engine\Object.h"

#include <glad\glad.h>

namespace engine {

    Object::Object()
    {
        // Define a simple triangle
        const float vertexPositions[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f,  0.5f, 0.0f  // top
        };

        // Create and bind VAO
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // Create a VBO for vertices then bind it
        glGenBuffers(1, &m_vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);

        // Create memory space and store data for current bound Vertex Buffer Object
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

        // Define the vertex buffer data interpretation for current bound Vertex Buffer Object
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        // Unbind VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void
    Object::render()
    {
        // Bind VAO
        glBindVertexArray(m_vao);

        // Draw object
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind VAO
        glBindVertexArray(0);
    }
}