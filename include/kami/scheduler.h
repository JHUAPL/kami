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
#ifndef KAMI_SCHEDULER_H
#define KAMI_SCHEDULER_H

#include <kami/model.h>

namespace kami {
/**
 * Create a Kami scheduler.
 *
 * Schedulers are responsible for executing each time step in the model.  A
 * scheduler will have a collection of agents assigned to it and will execute
 * the step function for each agent based on the type of scheduling implemented.
 */
    class LIBKAMI_EXPORT Scheduler {
    protected:
        /**
         * Counter to increment on each step
         */
        int _step_counter = 0;

    public:
        /**
         * @brief Execute a single time step.
         *
         * @details This method will step through the list of Agents in the
         * `Population` associated with `model` and then execute the `Agent::step()`
         * method for every Agent assigned to this scheduler in the order
         * assigned.
         *
         * @param model a reference copy of the model
         */
        virtual void step(std::shared_ptr<Model> model) = 0;

        /**
         * @brief Execute a single time step.
         *
         * @details This method will step through the list of Agents
         * provided and then execute the `Agent::step()`
         * method for every Agent assigned to this scheduler in the order
         * assigned.
         *
         * @param model a reference copy of the model
         * @param agent_list list of agents to execute the step
         */
        virtual void step(std::shared_ptr<Model> model, std::shared_ptr<std::vector<AgentID>> agent_list) = 0;
    };

}  // namespace kami

#endif  // KAMI_SCHEDULER_H
