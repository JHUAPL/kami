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
#ifndef KAMI_GRID1D_H
#define KAMI_GRID1D_H

#include <iostream>
#include <map>
#include <vector>

#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/kami.h>

namespace kami {

/**
 * One-dimensional coordinates
 */
    class LIBKAMI_EXPORT GridCoord1D : public GridCoord {
    public:
        /**
         * Constructor for one-dimensional coordinates
         */
        explicit GridCoord1D(int x_coord) : _x_coord(x_coord){};

        /**
         * Return the `x` coordinate
         */
        [[nodiscard]] int get_x_location() const;

        /**
         * Convert the coordinate to a human-readable string.
         *
         * @return a human-readable form of the `Coord` as `std::string`.
         */
        [[nodiscard]] std::string to_string() const override;

        /**
         * Test if two coordinates are equal
         */
        friend bool operator==(const GridCoord1D &lhs, const GridCoord1D &rhs);

        /**
         * Test if two coordinates are not equal
         */
        friend bool operator!=(const GridCoord1D &lhs, const GridCoord1D &rhs);

        /**
         * Output a given coordinate to the specified stream
         */
        friend std::ostream &operator<<(std::ostream &lhs, const GridCoord1D &rhs);

    private:
        int _x_coord;
    };

/**
 * A one-dimensional grid where each cell may contain agents
 *
 * The grid is linear and may wrap around in its only dimension.
 *
 * @see `MultiGrid1D`
 * @see `SoloGrid1D`
 */
    class LIBKAMI_EXPORT Grid1D : public GridDomain {
    public:
        /**
         * Constructor
         *
         * @param[in] maximum_x the length of the grid.
         * @param[in] wrap_x should the grid wrap around on itself.
         */
        explicit Grid1D(unsigned int maximum_x, bool wrap_x = false);

        /**
         * Destructor
         */
        virtual ~Grid1D();

        /**
         * Place agent on the grid at the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to add.
         * @param[in] coord the coordinates of the agent.
         *
         * @returns false if the agent is not placed at the specified
         * location, otherwise, true.
         */
        virtual bool add_agent(AgentID agent_id, GridCoord1D coord) = 0;

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
        bool delete_agent(AgentID agent_id, const GridCoord1D &coord);

        /**
         * Move an agent to the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to move.
         * @param[in] coord the coordinates of the agent.
         */
        bool move_agent(AgentID agent_id, GridCoord1D coord);

        /**
         * Inquire if the specified location is empty.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return true if the location has no `Agent`s occupying it, false
         * otherwise.
         */
        [[nodiscard]] bool is_location_empty(const GridCoord1D& coord) const;

        /**
         * Inquire if the specified location is valid within the grid.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return true if the location specified is valid, false otherwise.
         */
        [[nodiscard]] bool is_location_valid(const GridCoord1D& coord) const;

        /**
         * Get the location of the specified agent.
         *
         * @param[in] agent_id the `AgentID` of the agent in question.
         *
         * @return the location of the specified `Agent`
         */
        [[nodiscard]] GridCoord1D get_location_by_agent(AgentID agent_id) const;

        /**
         * Get the contents of the specified location.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return a pointer to a `vector` of `AgentID`s.  The pointer is to the
         * internal copy of the agent list at the location, therefore, any changes
         * to that object will update the state of the gird.  Further, the pointer
         * should not be deleted when no longer used.
         */
        [[nodiscard]] std::vector<AgentID> *get_location_contents(const GridCoord1D& coord) const;

        /**
         * Inquire to whether the grid wraps in the `x` dimension.
         *
         * @return true if the grid wraps, and false otherwise
         */
        [[nodiscard]] bool get_wrap_x() const;

        /**
         * Return the neighborhood of the specified Agent
         *
         * @param[in] agent_id the `AgentID` of the agent in question
         * @param[in] include_center should the center-point, occupied by the agent,
         * be in the list.
         *
         * @return a vector of `GridCoord1D` that includes all of the coordinates
         * for all adjacent points.
         */
        [[nodiscard]] std::vector<GridCoord1D> get_neighborhood(AgentID agent_id, bool include_center) const;

        /**
         * Return the neighborhood of the specified location
         *
         * @param[in] coord the coordinates of the specified location.
         * @param[in] include_center should the center-point, occupied by the agent,
         * be in the list.
         *
         * @return a vector of `GridCoord1D` that includes all of the coordinates
         * for all adjacent points.
         */
        [[nodiscard]] std::vector<GridCoord1D> get_neighborhood(const GridCoord1D& coord, bool include_center) const;

        /**
         * Get the size of the grid in the `x` dimension.
         *
         * @return the length of the grid in the `x` dimension
         */
        [[nodiscard]] unsigned int get_maximum_x() const;

    protected:
        /**
         * A vector containing the `AgentID`s of all agents assigned to this
         * grid.
         */
        std::vector<AgentID> *_agent_grid;

        /**
         * A map containing the grid location of each agent.
         */
        std::map<AgentID, GridCoord1D> *_agent_index;

        /**
         * Automatically adjust a coordinate location for wrapping.
         *
         * @param[in] coord the coordinates of the specified location.
         *
         * @return the adjusted coordinate wrapped if appropriate.
         */
        [[nodiscard]] GridCoord1D coord_wrap(const GridCoord1D& coord) const;

    private:
        unsigned int _maximum_x;
        bool _wrap_x;
    };

}  // namespace kami

#endif  // KAMI_GRID1D_H
