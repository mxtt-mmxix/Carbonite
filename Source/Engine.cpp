/*
 * MIT License
 *
 * Copyright (c) 2022 TheChernoCommunity
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <cstdint>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "spdlog/spdlog.h"

#include "Engine.hpp"

namespace {
    constexpr std::uint32_t SUBSYSTEM_MASK = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
}

namespace Carbonite::Engine {

    bool Initialize() {
        if (SDL_WasInit(SUBSYSTEM_MASK) == SUBSYSTEM_MASK) {
            spdlog::warn("Engine already initialized!");
            return true;
        }

        SDL_SetMainReady();

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            spdlog::critical("Failed to initialize SDL: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    void DeInitialize() {
        SDL_Quit();
    }
}
