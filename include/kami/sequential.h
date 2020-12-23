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
#ifndef KAMI_SEQUENTIAL_H
#define KAMI_SEQUENTIAL_H

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/model.h>
#include <kami/scheduler.h>

#include <algorithm>
#include <vector>

namespace kami {

///  \brief     Will execute all agent steps in a sequential order.
///  \details   A sequential scheduler will iterate over the agents assigned
///  to the scheduler and call their `step()` function in a sequential order.
///  That order is preserved between calls to `step()` but may be modified by
///  `addAgent()` or `deleteAgent()`.
///  \pre       First create a Model for the scheduler to live in.
class LIBKAMI_EXPORT SequentialScheduler : public Scheduler {
   public:
    ///  \brief Constructor.
    ///  \details   The Model parameter is used by the scheduler to get
    ///  access to an Agent.  The Model is presumed to maintain a master
    ///  list of all Agents in the Model and the Model can be queried for
    ///  a reference to any particular Agent at `step()` time.
    SequentialScheduler(Model *model);

    ///  \brief Add an agent to the scheduler.
    ///  \details   The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function adds a new Agent to the list.
    void add_agent(AgentID agent_id);

    ///  \brief Remove an agent from the scheduler.
    ///  \details The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function removes an Agent from the list.
    void delete_agent(AgentID agent_id);

    ///  \brief Execute a single time step.
    ///  \details   This method will step through the list of Agents in the
    ///  scheduler's internal queue and then execute the `Agent::step()`
    ///  method for every Agent assigned to this scheduler in the order
    ///  assigned.
    void step();

   protected:
    ///  \brief A vector containing the `AgentID`s of all agents assgined to
    ///  this scheduler
    std::vector<AgentID> _agent_list;
    ///  \brief A pointer to the `Model` this scehduler belongs to.
    Model *_model;
    ///  \brief Counter to increment on each step.
    int _step_counter;
};

};  // namespace kami

#endif  // KAMI_SEQUENTIAL_H
