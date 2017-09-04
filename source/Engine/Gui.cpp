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

#include "Engine/Gui.h"

#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw_gl3.h"

namespace engine {

    Gui::Gui(GLFWwindow * window, const Gui::WinResizeFn && winResizeFn) :
        m_resizeWindow{true},
        m_winResizeFn{ std::move(winResizeFn) }
    {
        ImGui_ImplGlfwGL3_Init(window, true);
    }

    Gui::~Gui()
    {
        ImGui_ImplGlfwGL3_Shutdown();
    }


	void
    Gui::update()
    {
        ImGui_ImplGlfwGL3_NewFrame();

        // New GUI Window for resizing
        if (m_resizeWindow)
        {
            ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
            ImGui::Begin("Test resize window", &m_resizeWindow, flags);
            if (ImGui::Button("1920x1080"))
                m_winResizeFn(1920, 1080);
            if (ImGui::Button("1080x720"))
                m_winResizeFn(1080, 720);
            if ((ImGui::Button("720x480")))
                m_winResizeFn(720, 480);
            ImGui::End();
        }
    }

    void
    Gui::render() const {
        ImGui::Render();
    }
}
