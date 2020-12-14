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
#include <random>
#include <string>
#include <iostream>

namespace kami {

RandomScheduler::RandomScheduler(Model *newModel) : SequentialScheduler(newModel) {
    auto timeNow = std::chrono::system_clock::now();
    auto timeSeconds = std::chrono::time_point_cast<std::chrono::seconds>(timeNow);
    auto newSeed = timeSeconds.time_since_epoch().count();

    setSeed(newSeed);
}

RandomScheduler::RandomScheduler(Model *newModel, int newSeed) : SequentialScheduler(newModel) {
    setSeed(newSeed);
}

void RandomScheduler::step() {
    shuffle(agentList.begin(), agentList.end(), rng);
    SequentialScheduler::step();
}

void RandomScheduler::setSeed(int newSeed) {
    originalSeed = newSeed;
    rng.seed(originalSeed);
}

int RandomScheduler::getSeed(void) const {
    return(originalSeed);
}

}  // namespace kami
