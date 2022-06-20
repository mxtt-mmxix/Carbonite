

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

#include <functional>
#include <unordered_map>

#include "SDL_events.h"
#include "SDL_mouse.h"

#include "spdlog/spdlog.h"

#include "Input.hpp"

namespace {
    using GetVec3 = std::function<Carbonite::Vec3()>;
    std::unordered_map<std::string, GetVec3> s_inputMap;
}

namespace Carbonite {

    Vec3 Get(const std::string& key) {
        if (s_inputMap.find(key) == s_inputMap.end()) {
            spdlog::error("Input \"{}\" not bound!", key);
            return {};
        }

        return s_inputMap.at(key)();
    }

    void UnBind(const std::string& key) {
        s_inputMap.erase(key);
    }

    namespace Bind {

        void PhysicalKey(SDL_Scancode scancode, const std::string& key) {
            s_inputMap[key] = [scancode]() -> Vec3 {
                return {static_cast<float>(SDL_GetKeyboardState(nullptr)[scancode]), 0, 0 };
            };
        }

        void UnicodeKey(SDL_Keycode keycode, const std::string& key) {
            s_inputMap[key] = [keycode]() -> Vec3 {
                return {static_cast<float>(SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(keycode)]), 0, 0 };
            };
        }

        void MouseButton(std::uint32_t buttonID, std::string key) {
            s_inputMap[key] = [buttonID]() -> Vec3 {
                return {(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(buttonID)) ? 1.f : 0.f, 0, 0 };
            };
        }

        void MouseMove(std::string key) {
            s_inputMap[key] = []() -> Vec3 {
                std::int32_t x, y;
                SDL_GetMouseState(&x, &y);
                return {static_cast<float>(x), static_cast<float>(y), 0 };
            };
        }
    }
}