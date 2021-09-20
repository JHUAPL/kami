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

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>

namespace kami {

/**
 * Create a Kami scheduler.
 *
 * Schedulers are responsible for executing each time step in the model.  A
 * scheduler will have a collection of agents assigned to it and will execute
 * the step function for each agent based on the type of scheduling implemented.
 */
class LIBKAMI_EXPORT Scheduler {
   public:
    /** 
     * Add an Agent to the Scheduler.
     * 
     * @param agent_id The AgentID of the agent to add.
     */
    virtual void add_agent(AgentID agent_id) = 0;

    /**
     * Remove an Agent from the Scheduler.
     * 
     * @param agent_id The AgentID of the agent to remove.
     */
    virtual void delete_agent(AgentID agent_id) = 0;

    /**
     * Step the Scheduler.
     * 
     * A generic step function that executes a single time step.
     */
    virtual void step() = 0;
};

}  // namespace kami

#endif  // KAMI_SCHEDULER_H
