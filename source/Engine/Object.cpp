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

namespace engine {

    Object::Object() :
        m_vboVertices{GL_ARRAY_BUFFER, GL_STATIC_DRAW},
        m_material{} // TODO: Unused for now
    {
        // Define a simple triangle
        // TODO: In the end should be
        // Position / Normals / Colors / UVs (Encapsulated in an object?)
        const float vertices[] = {
            // Position             Color 
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   // left
            0.5f,  -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   // right
            0.0f,   0.5f, 0.0f,     1.0f, 0.0f, 0.0f    // top
        };

        // Bind VAO
        m_vao.bind();

        // Bind VBO for vertices Positions
        m_vboVertices.bind();

        // Init VBO with vertices data
        m_vboVertices.init(sizeof(vertices), vertices);

        // TODO: Do something with this
        constexpr GLint positionSize = 3;
        constexpr GLsizei positionStride = sizeof(float) * 6;
        constexpr GLvoid * positionPointer = nullptr;
        // Define the vertex buffer data interpretation for current bound Vertex Buffer Object
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, positionSize,
                              GL_FLOAT, GL_FALSE,
                              positionStride, positionPointer);


        constexpr GLint colorSize = 3;
        constexpr GLsizei colorStride = sizeof(float) * 6;
        const GLvoid * colorPointer = reinterpret_cast<GLvoid*>(sizeof(float) * 3);
        // Define the vertex buffer data interpretation for current bound Vertex Buffer Object
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, colorSize,
            GL_FLOAT, GL_FALSE,
            colorStride, colorPointer);


        // Unbind VBO and VAO
        m_vboVertices.unbind();
        m_vao.unbind();
    }

    void
    Object::render()
    {
        // Bind VAO
        m_vao.bind();

        // Draw object
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind VAO
        m_vao.unbind();
    }
}