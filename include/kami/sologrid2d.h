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
#ifndef KAMI_SOLOGRID2D_H
//! @cond SuppressGuard
#define KAMI_SOLOGRID2D_H
//! @endcond

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/grid2d.h>
#include <kami/kami.h>

namespace kami {

    /**
     * @brief A two-dimensional grid where each cell may contain multiple agents
     *
     * @details The grid is linear and may wrap around in either dimension.
     *
     * @see `Grid2D`
     * @see `MultiGrid2D`
     */
    class LIBKAMI_EXPORT SoloGrid2D : public Grid2D {
    public:
        /**
         * @details Constructor
         *
         * @param[in] maximum_x the length of the grid in the first dimension
         * @param[in] maximum_y the length of the grid in the second dimension
         * @param[in] wrap_x should the grid wrap around on itself in the first dimension
         * @param[in] wrap_y should the grid wrap around on itself in the second dimension
         */
        SoloGrid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x, bool wrap_y);;

        /**
         * @details Place agent on the grid at the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to add.
         * @param[in] coord the coordinates of the agent.
         *
         * @returns false if the agent is not placed at the specified
         * location, otherwise, true
         */
        std::optional<AgentID> add_agent(AgentID agent_id, const GridCoord2D &coord) override;

    };

}  // namespace kami

#endif  // KAMI_SOLOGRID2D_H
