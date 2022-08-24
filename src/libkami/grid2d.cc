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

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid2d.h>

#include <map>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace kami {

    int GridCoord2D::get_x_location() const {
        return _x_coord;
    }

    int GridCoord2D::get_y_location() const {
        return _y_coord;
    }

    std::string GridCoord2D::to_string() const {
        return std::string("(" + std::to_string(_x_coord) + ", " + std::to_string(_y_coord) + ")");
    }

    std::optional<double> GridCoord2D::distance(std::shared_ptr<Coord> &p, GridDistanceType distance_type) const {
        auto p2d = std::static_pointer_cast<GridCoord2D>(p);

        switch (distance_type) {
            case GridDistanceType::Chebyshev:
                return distance_chebyshev(p2d);
            case GridDistanceType::Manhattan:
                return distance_manhattan(p2d);
            case GridDistanceType::Euclidean:
                return distance_euclidean(p2d);
        }
        return std::nullopt;
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

    Grid2D::Grid2D(unsigned int maximum_x, unsigned int maximum_y, bool wrap_x,
                   bool wrap_y) {
        _maximum_x = maximum_x;
        _maximum_y = maximum_y;
        _wrap_x = wrap_x;
        _wrap_y = wrap_y;

        _agent_grid = std::make_unique<std::unordered_multimap<GridCoord2D, AgentID>>();
        _agent_index = std::make_unique<std::map<AgentID, GridCoord2D>>();
    }

    std::optional<AgentID> Grid2D::delete_agent(AgentID agent_id) {
        auto coord = get_location_by_agent(agent_id);
        if (!coord)
            return std::nullopt;

        return delete_agent(agent_id, coord.value());
    }

    std::optional<AgentID> Grid2D::delete_agent(AgentID agent_id, const GridCoord2D &coord) {
        auto agent_location = _agent_grid->find(coord);
        if (agent_location == _agent_grid->end())
            return std::nullopt;

        for (auto test_agent_id = agent_location; test_agent_id != _agent_grid->end(); test_agent_id++)
            if (test_agent_id->second == agent_id) {
                _agent_grid->erase(test_agent_id);
                _agent_index->erase(agent_id);
                return agent_id;
            }

        return std::nullopt;
    }

    bool Grid2D::is_location_valid(const GridCoord2D &coord) const {
        auto x = coord.get_x_location();
        auto y = coord.get_y_location();

        return (x >= 0 && x < static_cast<int>(_maximum_x) &&
                y >= 0 && y < static_cast<int>(_maximum_y));
    }

    bool Grid2D::is_location_empty(const GridCoord2D &coord) const {
        auto grid_location = _agent_grid->equal_range(coord);
        return grid_location.first == grid_location.second;
    }

    std::optional<AgentID> Grid2D::move_agent(const AgentID agent_id, const GridCoord2D &coord) {
        auto coord_current = get_location_by_agent(agent_id);

        if (!coord_current)
            return std::nullopt;
        if (!delete_agent(agent_id, coord_current.value()))
            return std::nullopt;

        return add_agent(agent_id, coord);
    }

    std::optional<std::shared_ptr<std::unordered_set<GridCoord2D>>>
    Grid2D::get_neighborhood(const AgentID agent_id, const bool include_center,
                             const GridNeighborhoodType neighborhood_type) const {
        auto coord = get_location_by_agent(agent_id);
        if (!coord)
            return std::nullopt;

        return std::move(get_neighborhood(coord.value(), include_center, neighborhood_type));
    }

    std::optional<std::shared_ptr<std::unordered_set<GridCoord2D>>>
    Grid2D::get_neighborhood(const GridCoord2D &coord, const bool include_center,
                             const GridNeighborhoodType neighborhood_type) const {
        auto neighborhood = std::make_unique<std::unordered_set<GridCoord2D>>();
        auto x = coord.get_x_location();
        auto y = coord.get_y_location();

        // We assume our starting position is valid
        if (include_center)
            neighborhood->insert(coord);

        // N, E, S, W
        {
            auto new_location = coord_wrap(GridCoord2D(x, y - 1));
            if (is_location_valid(new_location))
                neighborhood->insert(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x, y + 1));
            if (is_location_valid(new_location))
                neighborhood->insert(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x + 1, y));
            if (is_location_valid(new_location))
                neighborhood->insert(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x - 1, y));
            if (is_location_valid(new_location))
                neighborhood->insert(coord_wrap(new_location));
        }

        if (neighborhood_type == GridNeighborhoodType::Moore) {
            // NE, SE, SW, NW
            {
                auto new_location = coord_wrap(GridCoord2D(x + 1, y - 1));
                if (is_location_valid(new_location))
                    neighborhood->insert(coord_wrap(new_location));
            }
            {
                auto new_location = coord_wrap(GridCoord2D(x + 1, y + 1));
                if (is_location_valid(new_location))
                    neighborhood->insert(coord_wrap(new_location));
            }
            {
                auto new_location = coord_wrap(GridCoord2D(x - 1, y + 1));
                if (is_location_valid(new_location))
                    neighborhood->insert(coord_wrap(new_location));
            }
            {
                auto new_location = coord_wrap(GridCoord2D(x - 1, y - 1));
                if (is_location_valid(new_location))
                    neighborhood->insert(coord_wrap(new_location));
            }
        }

        return std::move(neighborhood);
    }

    std::optional<std::shared_ptr<std::set<AgentID>>> Grid2D::get_location_contents(const GridCoord2D &coord) const {
        auto agent_ids = std::make_shared<std::set<AgentID>>();

        if (!is_location_valid(coord))
            return std::nullopt;
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

    std::optional<GridCoord2D> Grid2D::get_location_by_agent(const AgentID &agent_id) const {
        auto coord = _agent_index->find(agent_id);
        if (coord == _agent_index->end())
            return std::nullopt;
        return coord->second;
    }

    GridCoord2D Grid2D::coord_wrap(const GridCoord2D &coord) const {
        auto x = coord.get_x_location();
        auto y = coord.get_y_location();

        if (_wrap_x)
            x = (x + static_cast<int>(_maximum_x)) % static_cast<int>(_maximum_x);
        if (_wrap_x)
            y = (y + static_cast<int>(_maximum_y)) % static_cast<int>(_maximum_y);
        return {x, y};
    }

}  // namespace kami
