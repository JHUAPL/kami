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

#pragma once
#ifndef KAMI_RANDOM_H
#define KAMI_RANDOM_H

#include <kami/kami.h>
#include <kami/sequential.h>

#include <algorithm>
#include <random>
#include <vector>

namespace kami {

/**
 * Will execute all agent steps in a random order.
 * 
*  A random scheduler will iterate over the agents assigned
 *   to the scheduler and call their `step()` function in a random order.
 *   That order should be different for each subsequent call to `step()`,
 *   but is not gauranteed not to repeat.
* @note First create a Model for the scheduler to live in.
*/
class LIBKAMI_EXPORT RandomScheduler : public SequentialScheduler {
   public:
    /**
     * Constructor.
     *
     * The Model parameter is used by the scheduler to get
     * access to an Agent.  The Model is presumed to maintain a master
     * list of all Agents in the Model and the Model can be queried for
     * a reference to any particular Agent at `step()` time.
     */
    RandomScheduler(Model *model);

    /**
     * Constructor.
     * 
     * The Model parameter is used by the scheduler to get
     * access to an Agent.  The Model is presumed to maintain a master
     * list of all Agents in the Model and the Model can be queried for
     * a reference to any particular Agent at `step()` time.
     */
    RandomScheduler(Model *model, int seed);

    /**
     * Execute a single time step.
     *
     * This method will randomize the list of Agents in the scheduler's internal
     * queue and then execute the `Agent::step()` method for every Agent
     * assigned to this scheduler in the randomized order.
     */
    void step();

    /**
     * Get the seed used.
     *
     * Returns the seed used to initialize the random number
     * generator.
     */
    int get_seed(void) const;

    /**
     * Set the seed used to initialize the random number generator.
     * 
     * @param seed The random number seed
     */
    void set_seed(int seed);

   private:
    std::random_device _rd;
    std::mt19937 _rng{_rd()};
    int _original_seed;
};

};  // namespace kami

#endif  // KAMI_RANDOM_H
