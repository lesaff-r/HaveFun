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

#include <unordered_map>
#include <functional>

namespace engine {
    struct SEvent;
    enum class EEventType;
}

namespace engine {

    class EventManager final
    {
    // @brief Callbacks to process Events
    using EventCallbackFn = std::function<bool(const SEvent &)>;

    public:
        EventManager();


    public:
        void registerCallback(/*const EEventType & eventType,*/
                              const EventCallbackFn && callback);

        // Notify the EventManager that an Event has occured
        void notify(const SEvent & event);

    private:
        // Callback for the Engine to manage Events
        EventCallbackFn m_callback;

        //std::unordered_map<EEventType, std::list<EventCallbackFn>> m_callbacks;
    };
}
