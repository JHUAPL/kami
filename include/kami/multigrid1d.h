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
#ifndef KAMI_MULTIGRID1D_H
#define KAMI_MULTIGRID1D_H

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid1d.h>
#include <kami/kami.h>

namespace kami {

    /**
     * @brief A one-dimensional grid where each cell may contain multiple agents
     *
     * @details The grid is linear and may wrap around in its only dimension.
     *
     * @see `Grid1D`
     * @see `SoloGrid1D`
     */
    class LIBKAMI_EXPORT MultiGrid1D : public Grid1D {
    public:
        /**
         * @brief Constructor
         *
         * @param[in] maximum_x the length of the grid.
         * @param[in] wrap_x should the grid wrap around on itself.
         */
        MultiGrid1D(unsigned int maximum_x, bool wrap_x)
                : Grid1D(maximum_x, wrap_x) {}

        /**
         * @brief Place agent on the grid at the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to add.
         * @param[in] coord the coordinates of the agent.
         *
         * @returns false if the agent is not placed at the specified
         * location, otherwise, true
         */
        bool add_agent(AgentID agent_id, GridCoord1D coord) override;
    };

}  // namespace kami

#endif  // KAMI_MULTIGRID1D_H
