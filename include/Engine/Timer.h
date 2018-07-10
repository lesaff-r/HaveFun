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

#include <chrono>

namespace engine {

    class Timer
    {
    public:
        using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

        static TimePoint getCurrentTimePoint()
        {
            return std::chrono::high_resolution_clock::now();
        }

        void update()
        {
            auto now = getCurrentTimePoint();
            mElapsedTime = now - mCurrentTime;
            mCurrentTime = now;
        }

        inline float getElapsedTime() { return static_cast<float>(mElapsedTime.count()); }


    private:
        TimePoint mCurrentTime;
        std::chrono::duration<double> mElapsedTime;
    };
}