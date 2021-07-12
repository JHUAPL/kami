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
#ifndef KAMI_GRID2D_H
#define KAMI_GRID2D_H

#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/kami.h>

#include <iostream>
#include <map>
#include <vector>

namespace kami {

/**
 * Two-dimensional coordinates
 */
class LIBKAMI_EXPORT GridCoord2D : public GridCoord {
   public:
    /**
     * Constructor for two-dimensional coordinates
     */
    GridCoord2D(int x_coord, int y_coord)
        : _x_coord(x_coord), _y_coord(y_coord){};

    /**
     * Get the coordinate in the first dimension or `x`.
     */
    int get_x_location(void) const;

    /**
     * Get the coordinate in the second dimension or `y`.
     */
    int get_y_location(void) const;

    /**
     * Convert the coordinate to a human-readable string.
     *
     * @return a human-readable form of the `Coord` as `std::string`.
     */
    std::string to_string() const;

    /**
     * Test if two coordinates are equal
     */
    friend bool operator==(const GridCoord2D &, const GridCoord2D &);

    /**
     * Test if two coordinates are not equal
     */
    friend bool operator!=(const GridCoord2D &, const GridCoord2D &);

    /**
     * Output a given coordinate to the specified stream
     */
    friend std::ostream &operator<<(std::ostream &, const GridCoord2D &);

   private:
    int _x_coord, _y_coord;
};

/**
 * A two-dimensional grid where each cell may contain agents
 *
 * The grid is linear and may wrap around in its only dimension.
 *
 * @see `MultiGrid2D`
 * @see `SoloGrid2D`
 */
class LIBKAMI_EXPORT Grid2D : public GridDomain {
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
    Grid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x = false,
           bool wrap_y = false);

    /**
     * Deconstructor
     */
    virtual ~Grid2D();

    /**
     * Place agent on the grid at the specified location.
     *
     * @param[in] agent_id the `AgentID` of the agent to add.
     * @param[in] coord the coordinates of the agent.
     *
     * @returns false if the agent is not placed at the specified
     * location, otherwise, true.
     */
    virtual bool add_agent(AgentID agent_id, GridCoord2D coord) = 0;

    /**
     * Remove agent from the grid.
     *
     * @param[in] agent_id the `AgentID` of the agent to remove.
     *
     * @returns false if the agent is not removed, otherwise, true.
     */
    bool delete_agent(AgentID agent_id);

    /**
     * Remove agent from the grid at the specified location
     *
     * @param[in] agent_id the `AgentID` of the agent to remove.
     * @param[in] coord the coordinates of the agent.
     *
     * @returns false if the agent is not removed, otherwise, true.
     */
    virtual bool delete_agent(AgentID agent_id, GridCoord2D coord);

    /**
     * Move an agent to the specified location.
     *
     * @param[in] agent_id the `AgentID` of the agent to move.
     * @param[in] coord the coordinates of the agent.
     */
    bool move_agent(AgentID agent_id, GridCoord2D coord);

    /**
     * Inquire if the specified location is empty.
     *
     * @param[in] coord the coordinates of the query.
     *
     * @return true if the location has no `Agent`s occupying it, false
     * otherwise.
     */
    bool is_location_empty(GridCoord2D coord) const;

    /**
     * Inquire if the specified location is valid within the grid.
     *
     * @param[in] coord the coordinates of the query.
     *
     * @return true if the location specified is valid, false otherwise.
     */
    bool is_location_valid(GridCoord2D coord) const;

    /**
     * Get the location of the specified agent.
     *
     * @param[in] agent_id the `AgentID` of the agent in question.
     *
     * @return the location of the specified `Agent`
     */
    GridCoord2D get_location_by_agent(AgentID agent_id) const;

    /**
     * Get the contents of the specified location.
     */
    std::vector<AgentID> *get_location_contents(GridCoord2D coord) const;

    /**
     * Inquire to whether the grid wraps in the `x` dimension.
     */
    bool get_wrap_x(void) const;

    /**
     * Inquire to whether the grid wraps in the `y` dimension.
     */
    bool get_wrap_y(void) const;

    /**
     * Return the neighborhood of the specified Agent
     *
     * @param[in] agent_id the `AgentID` of the agent in question.
     * @param[in] neighborhood_type the neighborhood type.
     * @param[in] include_center should the center-point, occupied by the agent,
     * be in the list.
     *
     * @return a vector of `GridCoord1D` that includes all of the coordinates
     * for all adjacent points.
     * 
     * @see `NeighborhoodType`
     */
    std::vector<GridCoord2D> get_neighborhood(
        AgentID agent_id, GridNeighborhoodType neighborhood_type,
        bool include_center) const;

    /**
     * Return the neighborhood of the specified location
     *
     * @param[in] coord the coordinates of the specified location.
     * @param[in] neighborhood_type the neighborhood type.
     * @param[in] include_center should the center-point, occupied by the agent,
     * be in the list.
     *
     * @return a vector of `GridCoord1D` that includes all of the coordinates
     * for all adjacent points.
     * 
     * @see `NeighborhoodType`
     */
    std::vector<GridCoord2D> get_neighborhood(
        GridCoord2D coord, GridNeighborhoodType neighborhood_type,
        bool include_center) const;

    /**
     * Get the length of the grid in the `y` dimension.
     */
    unsigned int get_maximum_x(void) const;

    /**
     * Get the length of the grid in the `y` dimension.
     */
    unsigned int get_maximum_y(void) const;

   protected:
    std::vector<AgentID> **_agent_grid;
    std::map<AgentID, GridCoord2D> *_agent_index;

    GridCoord2D coord_wrap(GridCoord2D coord) const;

   private:
    unsigned int _maximum_x, _maximum_y;
    bool _wrap_x, _wrap_y;
};

}  // namespace kami

#endif  // KAMI_GRID2D_H
