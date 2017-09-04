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

#include "Engine\EventManager.h"
#include "Engine\Gui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

struct GLFWwindow;

namespace engine {

    // @brief Encapsulate a Window context
    // For now support only GLFW
    class Window final
    {
    public:
        // @brief Create a new GLFW window
        // @note Throw std::runtime_error if GLFW or GLAD Initialization failed
        Window(EventManager & eventManager);
        ~Window();

        // Delete copy operations
        Window(const Window &) = delete;
        Window & operator=(const Window &) = delete;

        // Define default moving operations
        Window(Window &&) = default;
        Window & operator=(Window &&) = default;


    public:
        inline int should_close() const     { return glfwWindowShouldClose(m_window); }

    public:
        void update();
        void render();


    private:
        // Called when the window detect a keyboard input
        // Also used to notify EventManager that a keyboard event has occured
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // Handle Keyboard Events
        bool onKeyEvent(const SEvent & event);

    private:
        // Close the window
        void close() const;

        // Resize the window
        // TODO: Or changed resolution if full screen
        void resize(int width, int heigh) const;

    private:
        EventManager & m_eventManager;

    private:
        GLFWwindow * m_window;

        std::unique_ptr<Gui> m_gui;
    };
}
