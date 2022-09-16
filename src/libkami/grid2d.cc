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

#include <map>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/error.h>
#include <kami/grid2d.h>

namespace kami {

    int GridCoord2D::x() const {
        return _x_coord;
    }

    int GridCoord2D::y() const {
        return _y_coord;
    }

    std::string GridCoord2D::to_string() const {
        return std::string("(" + std::to_string(_x_coord) + ", " + std::to_string(_y_coord) + ")");
    }

    double GridCoord2D::distance(std::shared_ptr<Coord> &p) const {
        auto p2d = std::static_pointer_cast<GridCoord2D>(p);
        return distance(p2d);
    }

    double GridCoord2D::distance(std::shared_ptr<GridCoord2D> &p, GridDistanceType distance_type) const {
        switch (distance_type) {
            case GridDistanceType::Chebyshev:
                return distance_chebyshev(p);
            case GridDistanceType::Manhattan:
                return distance_manhattan(p);
            case GridDistanceType::Euclidean:
                return distance_euclidean(p);
            default:
                throw error::InvalidOption("Unknown distance type given");
        }
    }

    bool operator==(const GridCoord2D &lhs, const GridCoord2D &rhs) {
        return (lhs._x_coord == rhs._x_coord && lhs._y_coord == rhs._y_coord);
    }

    bool operator!=(const GridCoord2D &lhs, const GridCoord2D &rhs) {
        return !(lhs == rhs);
    }

    std::ostream &operator<<(std::ostream &lhs, const GridCoord2D &rhs) {
        return lhs << rhs.to_string();
    }

    GridCoord2D::GridCoord2D(int x_coord, int y_coord)
            : _x_coord(x_coord), _y_coord(y_coord) {}

    double GridCoord2D::distance_chebyshev(std::shared_ptr<GridCoord2D> &p) const {
        return static_cast<double>(fmax(abs(_x_coord - p->_x_coord), abs(_x_coord - p->_x_coord)));
    }

    double GridCoord2D::distance_euclidean(std::shared_ptr<GridCoord2D> &p) const {
        return sqrt(pow(_x_coord - p->_x_coord, 2) + pow(_x_coord - p->_x_coord, 2));
    }

    double GridCoord2D::distance_manhattan(std::shared_ptr<GridCoord2D> &p) const {
        return static_cast<double>(abs(_x_coord - p->_x_coord) + abs(_x_coord - p->_x_coord));
    }

    GridCoord2D operator+(const GridCoord2D &lhs, const GridCoord2D &rhs) {
        return {lhs._x_coord + rhs._x_coord, lhs._y_coord + rhs._y_coord};
    }

    GridCoord2D operator-(const GridCoord2D &lhs, const GridCoord2D &rhs) {
        return {lhs._x_coord - rhs._x_coord, lhs._y_coord - rhs._y_coord};
    }

    GridCoord2D operator*(const GridCoord2D &lhs, const double rhs) {
        return {static_cast<int>(lhs._x_coord * rhs), static_cast<int>(lhs._y_coord * rhs)};
    }

    GridCoord2D operator*(const double lhs, const GridCoord2D &rhs) {
        return {static_cast<int>(rhs._x_coord * lhs), static_cast<int>(rhs._y_coord * lhs)};
    }

    Grid2D::Grid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x,
                   bool wrap_y) {
        _maximum_x = maximum_x;
        _maximum_y = maximum_y;
        _wrap_x = wrap_x;
        _wrap_y = wrap_y;

        _agent_grid = std::make_unique<std::unordered_multimap<GridCoord2D, AgentID>>();
        _agent_index = std::make_unique<std::map<AgentID, GridCoord2D>>();
    }

    AgentID Grid2D::delete_agent(const AgentID agent_id) {
        return delete_agent(agent_id, get_location_by_agent(agent_id));
    }

    AgentID Grid2D::delete_agent(const AgentID agent_id, const GridCoord2D &coord) {
        for (auto test_agent_id = _agent_grid->find(coord); test_agent_id != _agent_grid->end(); test_agent_id++)
            if (test_agent_id->second == agent_id) {
                _agent_grid->erase(test_agent_id);
                _agent_index->erase(agent_id);
                return agent_id;
            }

        throw error::AgentNotFound("Agent not found on grid");
    }

    bool Grid2D::is_location_valid(const GridCoord2D &coord) const {
        auto x = coord.x();
        auto y = coord.y();

        return (x >= 0 && x < static_cast<int>(_maximum_x) &&
                y >= 0 && y < static_cast<int>(_maximum_y));
    }

    bool Grid2D::is_location_empty(const GridCoord2D &coord) const {
        auto grid_location = _agent_grid->equal_range(coord);
        return grid_location.first == grid_location.second;
    }

    AgentID Grid2D::move_agent(const AgentID agent_id, const GridCoord2D &coord) {
        return add_agent(delete_agent(agent_id, get_location_by_agent(agent_id)), coord);
    }

    std::shared_ptr<std::unordered_set<GridCoord2D>>
    Grid2D::get_neighborhood(const AgentID agent_id, const bool include_center,
                             const GridNeighborhoodType neighborhood_type) const {
        return std::move(get_neighborhood(get_location_by_agent(agent_id), include_center, neighborhood_type));
    }

    std::shared_ptr<std::unordered_set<GridCoord2D>>
    Grid2D::get_neighborhood(const GridCoord2D &coord, const bool include_center,
                             const GridNeighborhoodType neighborhood_type) const {
        auto neighborhood = std::make_unique<std::unordered_set<GridCoord2D>>();
        std::vector<GridCoord2D> directions;

        switch (neighborhood_type) {
            case GridNeighborhoodType::VonNeumann:
                directions = directions_vonneumann;
                break;
            case GridNeighborhoodType::Moore:
                directions = directions_moore;
                break;
            default:
                throw error::InvalidOption(
                        fmt::format("Invalid neighborhood type {} given", (unsigned int) neighborhood_type));
        }

        if (include_center and is_location_valid(coord))
            neighborhood->insert(coord);

        for (auto &direction: directions) {
            auto new_location = coord_wrap(coord + direction);

            if (is_location_valid(new_location))
                neighborhood->insert(new_location);
        }

        return std::move(neighborhood);
    }

    std::shared_ptr<std::set<AgentID>> Grid2D::get_location_contents(const GridCoord2D &coord) const {
        auto agent_ids = std::make_shared<std::set<AgentID>>();

        if (!is_location_valid(coord))
            throw error::LocationUnavailable(fmt::format("Coordinates {} are invalid", coord.to_string()));
        if (is_location_empty(coord))
            return agent_ids;

        auto agent_range = _agent_grid->equal_range(coord);
        if (agent_range.first == agent_range.second)
            return agent_ids;

        for (auto i = agent_range.first; i != agent_range.second; i++)
            agent_ids->insert(i->second);
        return agent_ids;
    }

    bool Grid2D::get_wrap_x() const { return _wrap_x; }

    bool Grid2D::get_wrap_y() const { return _wrap_y; }

    unsigned int Grid2D::get_maximum_x() const { return _maximum_x; }

    unsigned int Grid2D::get_maximum_y() const { return _maximum_y; }

    GridCoord2D Grid2D::get_location_by_agent(const AgentID &agent_id) const {
        auto coord = _agent_index->find(agent_id);
        if (coord == _agent_index->end())
            throw error::AgentNotFound(fmt::format("Agent {} not found on grid", agent_id.to_string()));
        return coord->second;
    }

    GridCoord2D Grid2D::coord_wrap(const GridCoord2D &coord) const {
        auto x = coord.x();
        auto y = coord.y();

        if (_wrap_x)
            x = (x + static_cast<int>(_maximum_x)) % static_cast<int>(_maximum_x);
        if (_wrap_x)
            y = (y + static_cast<int>(_maximum_y)) % static_cast<int>(_maximum_y);
        return {x, y};
    }

}  // namespace kami
