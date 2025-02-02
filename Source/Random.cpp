

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

#include <random>
#include <unordered_set>

#include "Random.hpp"

namespace {

    std::unordered_set<std::uint32_t> s_usedInt32s;

}

namespace Carbonite {

    std::int32_t GetRandomInt32(std::int32_t min, std::int32_t max) {

        static std::random_device s_device;
        static std::mt19937 s_generator { s_device() };

        std::int32_t int32 = std::uniform_int_distribution { min, max } (s_generator);
        s_usedInt32s.insert(int32);
        return int32;
    }

    void ReleaseRandomInt32(std::int32_t int32) {
        s_usedInt32s.erase(int32);
    }

}