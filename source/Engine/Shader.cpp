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
#include <iostream>

namespace engine {

	// TODO: Will later be in deferent methods to abstract calls
	Shader::Shader(const std::string & data) :
		m_id{ createShaderFromType() }
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
	Shader::createShaderFromType() {
		// TODO: Only support GL_VERTEX_SHADER for now, but will later take a type as parameter
		GLint id = glCreateShader(GL_VERTEX_SHADER);

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
}
