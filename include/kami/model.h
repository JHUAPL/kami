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
#ifndef KAMI_MODEL_H
#define KAMI_MODEL_H

#include <kami/agent.h>
#include <kami/kami.h>

namespace kami {

/**
 * An abstract for generic models
 */
class LIBKAMI_EXPORT Model {
   public:
    /**
     * Get a reference to an `Agent` by `AgentID`
     *
     * @param[in] agent_id the `AgentID` to search for.
     *
     * @return a reference to the desired `Agent` or `nullptr` if not found.
     */
    virtual Agent *get_agent_by_id(AgentID agent_id) const = 0;

    /**
     * Execute a fixed number of time-steps for the model.
     *
     * This function should execute a fixed number of time-steps for the model.
     *
     * @param[in] n the number of time steps to execute.
     */
    virtual void run(unsigned int n) = 0;

    /**
     * Execute a single time-step for the model.
     *
     * This function should step the model instance.  Any activities that the
     * model should perform as part of its time step should be in this function.
     */
    virtual void step() = 0;
};

}  // namespace kami

#endif  // KAMI_MODEL_H
