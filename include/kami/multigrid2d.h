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
#ifndef KAMI_MULTIGRID2D_H
#define KAMI_MULTIGRID2D_H

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid2d.h>
#include <kami/kami.h>

namespace kami {

class LIBKAMI_EXPORT MultiGrid2D : public Grid2D {
   public:
    /**
     * Constructor
     *
     * @param[in] maximum_x the length of the grid in the first dimension
     * @param[in] maximum_y the length of the grid in the second dimension
     * @param[in] wrap_x should the grid wrap around on itself in the first
     * dimension
     * @param[in] wrap_y should the grid wrap around on itself in the second
     * dimension
     */
    MultiGrid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x,
                bool wrap_y);

    /**
     * Place agent on the grid at the specified location.
     *
     * @param[in] agent_id the `AgentID` of the agent to add.
     * @param[in] coord the coordinates of the agent.
     *
     * @returns false if the agent is not placed at the specified
     * location, otherwise, true
     */
    bool add_agent(AgentID agent_id, GridCoord2D coord);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID2D_H
