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

#include "Engine\Shader.h"

#include <glad/glad.h>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

namespace engine {

    Shader::Shader(const std::string & data,
                   const GLenum & type) :
        m_type{ type },
        m_id{ createShaderFromType(type) },
        m_isCompiled{ false }

    {
        // Attach source code to the given shader
        const char * raw_data = data.c_str();
        glShaderSource(m_id, 1, &raw_data, nullptr);

        // Load from file
        //	 TODO: Not available for now

        compile();
    }

    Shader::~Shader()
    {
        glDeleteShader(m_id);
    }


    unsigned int
    Shader::createShaderFromType(const GLenum & type) {

        GLuint id;

        switch (type)
        {
        case (GL_VERTEX_SHADER):
            id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case (GL_FRAGMENT_SHADER):
            id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            id = 0;
        }

        // Shader creation should never fail
        assert (id != 0);

        return id;
    }

    void
    Shader::compile() {

        // Compile the shader
        glCompileShader(m_id);

        // Get compile status
        GLint compileStatus;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);

        // And check if shader compilation failed
        m_isCompiled = (compileStatus == GL_TRUE);
        if (!m_isCompiled)
            getLogInfos();
    }

    void
    Shader::getLogInfos() {

        // Getting Log length
        GLint infoLogLength;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Create log container
        GLchar * infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(m_id, infoLogLength, nullptr, infoLog);

        // Display log
        std::cout << infoLog << std::endl;

        // Then delete log container
        delete[] infoLog;
    }


    const std::string
    Shader::get(const std::string & path) {
        // Try to open shader file
        std::ifstream file(path.c_str());

        // Check if file's opening failed
        if (!file.good())
            std::cout << "[ERROR] Failed to open shader: " << path << std::endl;

        // Create a stringstream and dump the shader content into it
        std::stringstream stream;
        stream << file.rdbuf();

        // Close shader file
        file.close();

        // Return shader file content as string
        return stream.str();
    }
}
