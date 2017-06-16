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

#include "Engine\Scene.h"
#include "Engine\Shader.h"

namespace engine {

	Scene::Scene()
	{
		// Ugly stuff until I support file loading :'(
		const std::string vertexShaderSource{ "#version 430 \n"
			"void main()\n"
			"{\n"
			"}\0" };

		// Load Shader
		Shader * vertexShaderId = new Shader(vertexShaderSource);
		// Shader fragmentShaderId = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		// New Object
		m_objects.emplace_back(new Object);
	}


	void
	Scene::render()
	{
		for (auto & object : m_objects)
		{
			object->render();
		}
	}
}