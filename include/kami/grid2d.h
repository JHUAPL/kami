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
//! @cond SuppressGuard
#define KAMI_GRID2D_H
//! @endcond

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/kami.h>

namespace kami {

    /**
     * @brief Two-dimensional coordinates
     */
    class LIBKAMI_EXPORT GridCoord2D : public GridCoord {
    protected:
        inline double distance_chebyshev(std::shared_ptr<GridCoord2D> &p) const {
            return static_cast<double>(fmax(abs(_x_coord - p->_x_coord), abs(_x_coord - p->_x_coord)));
        };

        inline double distance_euclidean(std::shared_ptr<GridCoord2D> &p) const {
            return sqrt(pow(_x_coord - p->_x_coord, 2) + pow(_x_coord - p->_x_coord, 2));
        };

        inline double distance_manhattan(std::shared_ptr<GridCoord2D> &p) const {
            return static_cast<double>(abs(_x_coord - p->_x_coord) + abs(_x_coord - p->_x_coord));
        };

    public:
        /**
         * @brief Constructor for two-dimensional coordinates
         */
        GridCoord2D(int x_coord, int y_coord)
                : _x_coord(x_coord), _y_coord(y_coord) {};

        /**
         * @brief Get the coordinate in the first dimension or `x`.
         */
        [[nodiscard]] int get_x_location() const;

        /**
         * @brief Get the coordinate in the second dimension or `y`.
         */
        [[nodiscard]] int get_y_location() const;

        /**
         * @brief Convert the coordinate to a human-readable string.
         *
         * @return a human-readable form of the `Coord` as `std::string`.
         */
        [[nodiscard]] std::string to_string() const override;

        /**
         * @brief Find the distance between two points
         *
         * @details Find the distance between two points using the
         * specified metric.  There are three options provided by
         * the `GridDistanceType` class.
         *
         * However, the coordinate class is not aware of the
         * properties of the `Grid2D` it is operating on.  Accordingly,
         * if the direct path is measured, without accounting for
         * and toroidal wrapping of the underlying `Grid2D`.
         *
         * @param p the point to measure the distance to
         * @param distance_type specify the distance type
         *
         * @returns the distance as a `double`
         */
        std::optional<double> distance(std::shared_ptr<Coord> &p, GridDistanceType distance_type) const override;

        /**
         * @brief Test if two coordinates are equal
         */
        friend bool operator==(const GridCoord2D &, const GridCoord2D &);

        /**
         * @brief Test if two coordinates are not equal
         */
        friend bool operator!=(const GridCoord2D &, const GridCoord2D &);

        /**
         * @brief Output a given coordinate to the specified stream
         */
        friend std::ostream &operator<<(std::ostream &, const GridCoord2D &);

    private:
        int _x_coord, _y_coord;
    };

    /**
     * @brief A two-dimensional grid where each cell may contain agents
     *
     * @details The grid is linear and may wrap around in its only dimension.
     *
     * @see `MultiGrid2D`
     * @see `SoloGrid2D`
     */
    class LIBKAMI_EXPORT Grid2D : public GridDomain {
    public:
        /**
         * @brief Constructor
         *
         * @param[in] maximum_x the length of the grid in the first dimension
         * @param[in] maximum_y the length of the grid in the second dimension
         * @param[in] wrap_x should the grid wrap around on itself in the first
         * dimension
         * @param[in] wrap_y should the grid wrap around on itself in the second
         * dimension
         */
        explicit Grid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x = false, bool wrap_y = false);

        /**
         * @brief Place agent on the grid at the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to add.
         * @param[in] coord the coordinates of the agent.
         *
         * @returns false if the agent is not placed at the specified
         * location, otherwise, true.
         */
        virtual std::optional<AgentID> add_agent(AgentID agent_id, const GridCoord2D &coord) = 0;

        /**
         * @brief Remove agent from the grid.
         *
         * @param[in] agent_id the `AgentID` of the agent to remove.
         *
         * @returns false if the agent is not removed, otherwise, true.
         */
        std::optional<AgentID> delete_agent(AgentID agent_id);

        /**
         * @brief Remove agent from the grid at the specified location
         *
         * @param[in] agent_id the `AgentID` of the agent to remove.
         * @param[in] coord the coordinates of the agent.
         *
         * @returns false if the agent is not removed, otherwise, true.
         */
        std::optional<AgentID> delete_agent(AgentID agent_id, const GridCoord2D &coord);

        /**
         * @brief Move an agent to the specified location.
         *
         * @param[in] agent_id the `AgentID` of the agent to move.
         * @param[in] coord the coordinates of the agent.
         */
        std::optional<AgentID> move_agent(AgentID agent_id, const GridCoord2D &coord);

        /**
         * @brief Inquire if the specified location is empty.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return true if the location has no `Agent`s occupying it, false
         * otherwise.
         */
        [[nodiscard]] bool is_location_empty(const GridCoord2D& coord) const;

        /**
         * @brief Inquire if the specified location is valid within the grid.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return true if the location specified is valid, false otherwise.
         */
        [[nodiscard]] bool is_location_valid(const GridCoord2D& coord) const;

        /**
         * @brief Get the location of the specified agent.
         *
         * @param[in] agent_id the `AgentID` of the agent in question.
         *
         * @return the location of the specified `Agent`
         */
        [[nodiscard]] std::optional<GridCoord2D> get_location_by_agent(const AgentID &agent_id) const;

        /**
         * @brief Get the contents of the specified location.
         *
         * @param[in] coord the coordinates of the query.
         *
         * @return a pointer to a `set` of `AgentID`s.  The pointer is to the
         * internal copy of the agent list at the location, therefore, any changes
         * to that object will update the state of the gird.  Further, the pointer
         * should not be deleted when no longer used.
         */
        [[nodiscard]] std::optional<std::shared_ptr<std::set<AgentID>>>
        get_location_contents(const GridCoord2D &coord) const;

        /**
         * @brief Inquire to whether the grid wraps in the `x` dimension.
         *
         * @return true if the grid wraps, and false otherwise
         */
          [[nodiscard]] bool get_wrap_x() const;

        /**
         * @brief Inquire to whether the grid wraps in the `y` dimension.
         *
         * @return true if the grid wraps, and false otherwise
         */
        [[nodiscard]] bool get_wrap_y() const;

        /**
         * @brief Return the neighborhood of the specified Agent
         *
         * @param[in] agent_id the `AgentID` of the agent in question.
         * @param[in] neighborhood_type the neighborhood type.
         * @param[in] include_center should the center-point, occupied by the agent,
         * be in the list.
         *
         * @return a set of `GridCoord1D` that includes all of the coordinates
         * for all adjacent points.
         *
         * @see `NeighborhoodType`
         */
        [[nodiscard]] std::optional<std::shared_ptr<std::unordered_set<GridCoord2D>>>
        get_neighborhood(AgentID agent_id, bool include_center, GridNeighborhoodType neighborhood_type) const;

        /**
         * @brief Return the neighborhood of the specified location
         *
         * @param[in] coord the coordinates of the specified location.
         * @param[in] neighborhood_type the neighborhood type.
         * @param[in] include_center should the center-point, occupied by the agent,
         * be in the list.
         *
         * @return a set of `GridCoord2D` that includes all of the coordinates
         * for all adjacent points.
         *
         * @see `NeighborhoodType`
         */
        [[nodiscard]] std::optional<std::shared_ptr<std::unordered_set<GridCoord2D>>>
        get_neighborhood(const GridCoord2D &coord, bool include_center, GridNeighborhoodType neighborhood_type) const;

        /**
         * @brief Get the size of the grid in the `x` dimension.
         *
         * @return the length of the grid in the `x` dimension
         */
        [[nodiscard]] unsigned int get_maximum_x() const;

        /**
         * @brief Get the size of the grid in the `y` dimension.
         *
         * @return the length of the grid in the `xy dimension
         */
        [[nodiscard]] unsigned int get_maximum_y() const;

    protected:
        /**
         * @brief  A map containing the `AgentID`s of all agents assigned to this
         * grid.
         */
        std::unique_ptr<std::unordered_multimap<GridCoord2D, AgentID>> _agent_grid;

        /**
         * @brief A map containing the grid location of each agent.
         */
        std::unique_ptr<std::map<AgentID, GridCoord2D>> _agent_index;

        /**
         * @brief Automatically adjust a coordinate location for wrapping.
         *
         * @param[in] coord the coordinates of the specified location.
         *
         * @return the adjusted coordinate wrapped if appropriate.
         */
        [[nodiscard]] GridCoord2D coord_wrap(const GridCoord2D &coord) const;

    private:
        unsigned int _maximum_x, _maximum_y;
        bool _wrap_x, _wrap_y;
    };

}  // namespace kami

//! @cond SuppressHashMethod
namespace std {
    template<>
    struct hash<kami::GridCoord2D> {
        size_t operator()(const kami::GridCoord2D &key) const {
            return ((hash<int>()(key.get_x_location()) ^ (hash<int>()(key.get_y_location()) << 1)) >> 1);
        }
    };
}  // namespace std
//! @endcond

#endif  // KAMI_GRID2D_H
