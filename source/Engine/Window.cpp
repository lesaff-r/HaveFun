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

#include "Engine\Window.h"
#include "Engine\Event.h"
#include "Engine\KeyCodes.h"

#include <stdexcept>
#include <functional>
#include <iostream>
namespace engine {

    Window::Window(EventManager & eventManager) :
        m_eventManager{ eventManager }
    {
        // GLFW Initialization
        if (!glfwInit())
            throw std::runtime_error{ "[ERROR] GLFW Initialization failed" };

        // Support from OpenGL 4.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW Window
        GLFWmonitor * monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode * mode = glfwGetVideoMode(monitor);

        m_window = glfwCreateWindow(mode->width, mode->height, "Engine_v0", monitor, NULL);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error{ "[ERROR] GLFW Window creation failed" };
        }

        // Makes current Window context
        glfwMakeContextCurrent(m_window);

        // Set glfw User Pointer to this object
        // Used to get member data from glfw callbacks
        glfwSetWindowUserPointer(m_window, this);


        // Glad Initialization
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error{ "[ERROR] GLAD Initialization failed" };
        }


        // GUI Initialization
        auto winResizeFn = [this](int width, int heigh) {
            this->resize(width, heigh);
        };
        m_gui = std::make_unique<Gui>(m_window, winResizeFn);

        // Callback Initialization
        glfwSetKeyCallback(m_window, &key_callback);
        glfwSetCursorPosCallback(m_window, &cursor_position_callback);
        glfwSetMouseButtonCallback(m_window, &mouse_button_callback);
        glfwSetScrollCallback(m_window, &scroll_callback);
    }

    Window::~Window()
    {
        glfwTerminate();
    }


    void
    Window::update()
    {
        // Manage events
        glfwPollEvents();

        // Update GUI
        m_gui->update();
    }

    void
    Window::render()
    {
        // Display GUI
        m_gui->render();

        // Display window on Screen
        glfwSwapBuffers(m_window);
    }


    void
    Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
    {
        // Get User pointer from Glfw to call Window method
        auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        // Create and fill Event container
        SEvent event;
        event.EventType = SEvent::EEventType::EET_KEY_EVENT;
        event.KeyEvent.Pressed = static_cast<SEvent::SKeyEvent::State>(action);
        event.KeyEvent.Key = static_cast<EKeyCode>(key);

        // If the key was pressed, process the input
        if (event.KeyEvent.Pressed == SEvent::SKeyEvent::State::Press)
            w->onKeyEvent(event);

        // Notify the EventManager
        w->m_eventManager.notify(event);
    }

    void
    Window::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
    {
        // Get User pointer from Glfw to call Window method
        auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        // Create and fill Event container
        SEvent event;
        event.EventType = SEvent::EEventType::EET_MOUSE_EVENT;
        event.MouseEvent.type = SEvent::SMouseEvent::Type::Move;

        // Get mouse position
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        event.MouseEvent.pos = glm::vec2{ float(x), float(y) };

        // Notify the EventManager
        w->m_eventManager.notify(event);
    }

    void
    Window::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
    {
        // Get User pointer from Glfw to call Window method
        auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        // Create and fill Event container
        SEvent event;
        event.EventType = SEvent::EEventType::EET_MOUSE_EVENT;
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            event.MouseEvent.type = (action == GLFW_PRESS) ?
                SEvent::SMouseEvent::Type::LButtonDown : SEvent::SMouseEvent::Type::LButtonUp;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            event.MouseEvent.type = (action == GLFW_PRESS) ?
                SEvent::SMouseEvent::Type::RButtonDown : SEvent::SMouseEvent::Type::RButtonUp;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            event.MouseEvent.type = (action == GLFW_PRESS) ?
                SEvent::SMouseEvent::Type::MidButtonDown : SEvent::SMouseEvent::Type::MidButtonUp;
            break;
        default:
            // Should not be something else
            break;
        }

        // Get and Set mouse position
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        event.MouseEvent.pos = glm::vec2{ float(x), float(y) };

        // Notify the EventManager
        w->m_eventManager.notify(event);
    }

    void
    Window::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
    {
        // Get User pointer from Glfw to call Window method
        auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        // Create and fill Event container
        SEvent event;
        event.EventType = SEvent::EEventType::EET_MOUSE_EVENT;
        event.MouseEvent.type = SEvent::SMouseEvent::Type::Wheel;
        event.MouseEvent.wheelOffset = glm::vec2{(float)xoffset, (float)yoffset};

        // Notify the EventManager
        w->m_eventManager.notify(event);
    }

    bool
    Window::onKeyEvent(const SEvent & event)
    {
        bool handled = false;

        switch (event.KeyEvent.Key)
        {
        case EKeyCode::EKC_ESC:
            close();
            handled = true;
            break;
        default:
            break;
        }

        return handled;
    }


    void
    Window::close() const
    {
        glfwSetWindowShouldClose(m_window, true);
    }


    void
    Window::resize(int width, int heigh) const {
        SEvent event;

        event.EventType = SEvent::EEventType::EET_RESIZE;
        event.ResizeEvent.width = width;
        event.ResizeEvent.heigh = heigh;
        m_eventManager.notify(event);

        glfwSetWindowSize(m_window, width, heigh);
    }
}
