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
#include <iostream>

namespace engine {

	// TODO: Will later be in deferent methods to abstract calls
	// TODO: Also need a shader Program
	Shader::Shader(const std::string & data)
	{
		// Create a new shader
		// TODO: Only support GL_VERTEX_SHADER for now, but will later take a type as parameter
		m_id = glCreateShader(GL_VERTEX_SHADER); // failed if given id is 0

		// Attach source code to the given shader
		const char * raw_data = data.c_str();
		glShaderSource(m_id, 1, &raw_data, nullptr);

		// Load from file
		//	 TODO: Not available for now

		// Compile
		glCompileShader(m_id);
		// Checking if compile failed
		GLint compileStatus; // TODO: Should later be stored in Object

		glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus = GL_FALSE)
		{
			// Getting Log length
			GLint infoLogLength;
			glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			// Create log container
			GLchar * infoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(m_id, infoLogLength, nullptr, infoLog);

			// Display log Info
			std::cout << infoLog << std::endl;

			// Then delete it
			delete[] infoLog;
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(m_id);
	}

}
