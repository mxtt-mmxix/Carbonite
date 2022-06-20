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

#include <cstdlib>

#include "SDL.h"
#include "spdlog/spdlog.h"

#include "Event.hpp"
#include "Init.hpp"
#include "Input.hpp"

int main(int argc, char **argv) {
    if (!Carbonite::Initialize()) {
        spdlog::critical("Failed to initialize engine!");
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Carbonite", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    if (window == nullptr) {
        spdlog::critical("Failed to create window: {}", SDL_GetError());
        return EXIT_FAILURE;
    }

    bool exit = false;

    Carbonite::Sub<Carbonite::Event::WindowClose> windowCloseSub {
        [&exit, &window](const Carbonite::Event::WindowClose &e) {
            if (e.windowID == SDL_GetWindowID(window)) exit = true;
        }
    };

    Carbonite::Sub<Carbonite::Event::AppQuit> appQuitSub {[&exit](const auto &) {
        exit = true;
    } };

    Carbonite::Bind::PhysicalKey(SDL_SCANCODE_ESCAPE, "Exit");

    while (!exit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Carbonite::Pub<Carbonite::Event::AppQuit>(event.quit);
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                            Carbonite::Pub<Carbonite::Event::WindowClose>(event.window);
                            break;
                    }
                    break;
            }
        }

        if (Carbonite::Get("Exit")) {
            exit = true;
        }
    }

    return EXIT_SUCCESS;
}