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

#include <memory>
#include <random>
#include <vector>

#include <kami/kami.h>
#include <kami/scheduler.h>
#include <kami/sequential.h>

namespace kami {

    /**
     * @brief Will execute all agent steps in a random order.
     *
     * @details A random scheduler will iterate over the agents assigned
     * to the scheduler and call their `step()` function in a random order.
     * That order should be different for each subsequent call to `step()`,
     * but is not guaranteed not to repeat.
     */
    class LIBKAMI_EXPORT RandomScheduler : public SequentialScheduler {
    private:
        std::shared_ptr<std::ranlux24> _rng = nullptr;

    public:
        /**
         * @brief Constructor.
         */
        RandomScheduler() = default;

        /**
         * @brief Constructor.
         *
         * @param rng [in] A uniform random number generator of type
         * `std::mt19937`, used as the source of randomness.
         */
        explicit RandomScheduler(std::shared_ptr<std::ranlux24> rng);

        /**
         * @brief Execute a single time step.
         *
         * @details This method will randomize the list of Agents provided
         * then execute the `Agent::step()` method for every Agent listed.
         *
         * @param model a reference copy of the model
         * @param agent_list list of agents to execute the step
         *
         * @params returns vector of agents successfully stepped
         */
        std::shared_ptr<std::vector<AgentID>> step(std::shared_ptr<Model> model, std::shared_ptr<std::vector<AgentID>> agent_list) override;

        /**
         * @brief Set the RNG
         *
         * @details Set the random number generator used to randomize the order of agent
         * stepping.
         *
         * @param rng [in] A uniform random number generator of type `std::mt19937`,
         * used as the source of randomness.
         */
        void set_rng(std::shared_ptr<std::ranlux24> rng);

        /**
         * @brief Get the RNG
         *
         * @details Get a reference to the random number generator used to randomize
         * the order of agent stepping.
         */
        std::shared_ptr<std::ranlux24> get_rng();
    };

}  // namespace kami

#endif  // KAMI_RANDOM_H
