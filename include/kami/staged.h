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

#include <kami/agent.h>
#include <kami/model.h>
#include <kami/scheduler.h>

#include <algorithm>
#include <vector>

namespace kami {

/**
 * Will execute all agent steps in a sequential order.
 *
 * A sequential scheduler will iterate over the agents assigned to the scheduler
 * and call their `step()` function in a sequential order. That order is
 * preserved between calls to `step()` but may be modified by `add_agent()` or
 * `delete_agent()`.
 *
 * @note First create a Model for the scheduler to live in.
 */
    class LIBKAMI_EXPORT StagedScheduler : public Scheduler {
    public:
        /**
         * Constructor.
         * The Model parameter is used by the scheduler to get access to an Agent.
         * The Model is presumed to maintain a master list of all Agents in the
         * Model and the Model can be queried for  a reference to any particular
         * Agent at `step()` time.
         */
        explicit StagedScheduler(Model *);

        /**
         * A deconstructor.
         */
        ~StagedScheduler() = default;

        /**
         * Add an agent to the scheduler.
         *
         * The scheduler maintains a list of all AgentIDs currently assigned.  This
         * function adds a new Agent to the list.
         */
        void add_agent(AgentID agent_id) override;

        /**
         * Remove an agent from the scheduler.
         *
         * The scheduler maintains a list of all AgentIDs currently assigned.  This
         * function removes an Agent from the list.
         */
        void delete_agent(AgentID agent_id) override;

        /**
         * Execute a single time step.
         *
         * This method will step through the list of Agents in the scheduler's
         * internal queue and execute the `Agent::step()` method for  each `Agent`
         * in the same order.  Finally, it will execute the  `Agent::advance()`
         * method for each Agent in the same order.
         */
        void step() override;

    private:
        std::vector<AgentID> _agent_list;
        Model *_model;
        int _step_counter;
    };

}  // namespace kami

#endif  // KAMI_STAGED_H
