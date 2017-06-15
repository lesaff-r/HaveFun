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

#include "Engine/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <functional>

namespace engine {

	Window::Window()
	{
		// GLFW Initialization
		if (!glfwInit())
			throw std::runtime_error("[ERROR] GLFW Initialization failed");

		// Support from OpenGL 4.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create GLFW Window
		m_window = glfwCreateWindow(720, 480, "Engine_v0", NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			throw std::runtime_error("[ERROR] GLFW Window creation failed");
		}

		// Makes current Window context
		glfwMakeContextCurrent(m_window);

		// Glad Initialization
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			glfwTerminate();
			throw std::runtime_error("[ERROR] GLAD Initialization failed");
		}

		// Initialize GUI
		auto winResizeFn = [this](int width, int heigh) {
			this->resize(width, heigh);
		};
		m_gui = std::make_unique<Gui>(m_window, winResizeFn);
	}

	Window::~Window() {
		glfwTerminate();
	}


	int
	Window::should_close() const {
		return glfwWindowShouldClose(m_window);
	}

	void
	Window::update() {
		// Manage events
		glfwPollEvents();
		processInputs();

		// Update GUI
		m_gui->update();
	}

	void
	Window::render() {
		// Display GUI
		m_gui->render();

		// Display window on Screen
		glfwSwapBuffers(m_window);
	}

	void
	Window::resize(int width, int heigh) const {
		glfwSetWindowSize(m_window, width, heigh);
	}


	void
	Window::processInputs() {
		// Use this or use 
		// glfwSetKeyCallback(window, key_callback);
		// for more a generic way to manage events
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);
	}
}
