

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

#ifndef CARBONITE_EVENT_HPP
#define CARBONITE_EVENT_HPP

#include <functional>
#include <vector>

#include "SDL_events.h"

#include "Random.hpp"

namespace Carbonite {

    namespace Event {
        using AppQuit = SDL_QuitEvent;
        using WindowClose = SDL_WindowEvent;

        struct WindowResize {
            WindowResize(SDL_WindowEvent);
            std::int32_t w, h;
        };

        struct WindowMoved {
            WindowMoved(SDL_WindowEvent);
            std::int32_t x, y;
        };

        using KeyPressed = SDL_KeyboardEvent;
        using KeyReleased = SDL_KeyboardEvent;

        using MouseButtonDown = SDL_MouseButtonEvent;
        using MouseButtonUp = SDL_MouseButtonEvent;
        using MouseScrolledEvent = SDL_MouseWheelEvent;
        using MouseMovedEvent = SDL_MouseMotionEvent;
    }

    template<typename T>
    class Sub {

        friend void Pub(const T &data);

        using Callback = std::function<void(const T &)>;

    public:
        explicit Sub(Callback func) : Func(func) {
            m_id = GetRandomInt32();
            Sub<T>::Subscribers.push_back(*this);
        }

        ~Sub() {
            const auto &i = std::find_if(Sub<T>::Subscribers.begin(), Sub<T>::Subscribers.end(), [this](Sub<T> &sub) {
                return this->m_id = sub.m_id;
            });

            if (i != Sub<T>::Subscribers.end()) Sub<T>::Subscribers.erase(i);

            ReleaseRandomInt32(m_id);
        }

        static std::vector<std::reference_wrapper<Sub<T>>> Subscribers;
        Callback Func;

    private:
        std::int32_t m_id;
    };

    template<typename T> std::vector<std::reference_wrapper<Sub<T>>> Sub<T>::Subscribers{};

    template<class T>
    void Pub(const T &data) {
        for (Sub<T> &i: Sub<T>::Subscribers) {
            i.Func(data);
        }
    }

}

#endif //CARBONITE_EVENT_HPP
