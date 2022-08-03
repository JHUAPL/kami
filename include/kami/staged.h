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
#ifndef KAMI_STAGED_H
#define KAMI_STAGED_H

#include <algorithm>
#include <vector>

#include <kami/agent.h>
#include <kami/scheduler.h>
#include <kami/sequential.h>

namespace kami {

    /**
     * @brief Will execute all agent steps in a sequential order.
     *
     * @detais A sequential scheduler will iterate over the agents assigned to the scheduler
     * and call their `step()` function in a sequential order. That order is
     * preserved between calls to `step()` but may be modified by `add_agent()` or
     * `delete_agent()`.
     */
    class LIBKAMI_EXPORT StagedScheduler : public SequentialScheduler {
    private:
        /**
         * @brief Advance a single time step.
         *
         * @details This method will step through the list of StagedAgent in the
         * scheduler's internal queue and then execute the `StagedAgent::step()`
         * method for every StagedAgent assigned to this scheduler in the order
         * assigned.
         *
         * @param model a reference copy of the model
         *
         * @params returns vector of agents successfully advanced
         */
        std::shared_ptr<std::vector<AgentID>> advance(std::shared_ptr<Model> model);

        /**
         * @brief Advance a single time step.
         *
         * @details This method will step through the list of StagedAgent
         * provided and then execute the `StagedAgent::advance()`
         * method for every StagedAgent assigned to this scheduler in the order
         * assigned.
         *
         * @param model a reference copy of the model
         * @param agent_list list of agents to execute the step
         *
         * @params returns vector of agents successfully advanced
         */
        std::shared_ptr<std::vector<AgentID>> advance(std::shared_ptr<Model> model, std::shared_ptr<std::vector<AgentID>> agent_list);

    public:
        /**
         * @brief Execute a single time step
         *
         * @details This method will step through the list of Agents in the scheduler's
         * internal queue and execute the `Agent::step()` method for  each `Agent`
         * in the same order.  Finally, it will execute the  `Agent::advance()`
         * method for each Agent in the same order.
         *
         * @param model a reference copy of the model
         * @param agent_list list of agents to execute the step
         *
         * @params returns vector of agents successfully stepped
         */
        std::shared_ptr<std::vector<AgentID>> step(std::shared_ptr<Model> model, std::shared_ptr<std::vector<AgentID>> agent_list) override;
    };

}  // namespace kami

#endif  // KAMI_STAGED_H
