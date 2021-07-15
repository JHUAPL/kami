/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <kami/agent.h>
#include <kami/model.h>
#include <kami/random.h>
#include <kami/scheduler.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>

namespace kami {

RandomScheduler::RandomScheduler(Model *model) : SequentialScheduler(model) {}

RandomScheduler::RandomScheduler(Model *model,
                                 std::shared_ptr<std::mt19937> rng)
    : SequentialScheduler(model) {
    this->set_rng(rng);
}

void RandomScheduler::step() {
    shuffle(_agent_list.begin(), _agent_list.end(), *_rng);
    this->SequentialScheduler::step();
}

void RandomScheduler::set_rng(std::shared_ptr<std::mt19937> rng) {
    this->_rng = rng;
}

std::shared_ptr<std::mt19937> RandomScheduler::get_rng() { return (_rng); }

}  // namespace kami
