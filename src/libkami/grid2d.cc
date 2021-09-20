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
#include <kami/grid.h>
#include <kami/grid2d.h>
#include <kami/kami.h>
#include <map>
#include <vector>

namespace kami {

int GridCoord2D::get_x_location(void) const {
    return _x_coord;
}

int GridCoord2D::get_y_location(void) const {
    return _y_coord;
}

std::string GridCoord2D::to_string() const {
    return std::string("(" + std::to_string(_x_coord) + ", " +
                       std::to_string(_y_coord) + ")");
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

    _agent_grid = new std::vector<AgentID> *[_maximum_x];
    for (auto i = 0; i < _maximum_x; i++)
        _agent_grid[i] = new std::vector<AgentID>[_maximum_y];

    _agent_index = new std::map<AgentID, GridCoord2D>;
}

Grid2D::~Grid2D(void) {
    delete _agent_index;

    for (auto i = 0; i < _maximum_x; i++) delete[] _agent_grid[i];
    delete[] _agent_grid;
}

bool Grid2D::delete_agent(AgentID agent_id) {
    auto location = get_location_by_agent(agent_id);

    return delete_agent(agent_id, location);
}

bool Grid2D::delete_agent(AgentID agent_id, GridCoord2D location) {
    auto agent_list = _agent_grid[static_cast<int>(location.get_x_location())]
                                 [static_cast<int>(location.get_y_location())];
    for (auto test_agent_id = agent_list.begin();
         test_agent_id < agent_list.end(); test_agent_id++) {
        if (*test_agent_id == agent_id) {
            agent_list.erase(test_agent_id);
            _agent_index->erase(agent_id);
            return true;
        }
    }

    return false;
}

bool Grid2D::is_location_valid(GridCoord2D location) const {
    auto x = location.get_x_location();
    auto y = location.get_y_location();

    return (x >= 0 && x < static_cast<int>(_maximum_x) && y >= 0 &&
            y < static_cast<int>(_maximum_y));
}

GridCoord2D Grid2D::get_location_by_agent(AgentID agent_id) const {
    return _agent_index->at(agent_id);
}

bool Grid2D::move_agent(AgentID agent_id, GridCoord2D coord) {
    GridCoord2D current_location = get_location_by_agent(agent_id);

    if (delete_agent(agent_id, current_location) == true)
        return add_agent(agent_id, coord);
    return false;
}

bool Grid2D::get_wrap_x(void) const { return _wrap_x; }
bool Grid2D::get_wrap_y(void) const { return _wrap_y; }

std::vector<GridCoord2D> Grid2D::get_neighborhood(
    AgentID agent_id, GridNeighborhoodType neighborhood_type,
    bool includeCenter) const {
    GridCoord2D location = get_location_by_agent(agent_id);

    return get_neighborhood(location, neighborhood_type, includeCenter);
}

std::vector<GridCoord2D> Grid2D::get_neighborhood(
    GridCoord2D location, GridNeighborhoodType neighborhood_type,
    bool include_center) const {
    std::vector<GridCoord2D> neighborhood;
    auto x = location.get_x_location();
    auto y = location.get_y_location();

    // We assume our starting position is valid
    if (include_center) neighborhood.push_back(location);

    // N, E, S, W
    {
        auto new_location = coord_wrap(GridCoord2D(x, y - 1));
        if (is_location_valid(new_location))
            neighborhood.push_back(coord_wrap(new_location));
    }
    {
        auto new_location = coord_wrap(GridCoord2D(x, y + 1));
        if (is_location_valid(new_location))
            neighborhood.push_back(coord_wrap(new_location));
    }
    {
        auto new_location = coord_wrap(GridCoord2D(x + 1, y));
        if (is_location_valid(new_location))
            neighborhood.push_back(coord_wrap(new_location));
    }
    {
        auto new_location = coord_wrap(GridCoord2D(x - 1, y));
        if (is_location_valid(new_location))
            neighborhood.push_back(coord_wrap(new_location));
    }

    if (neighborhood_type == GridNeighborhoodType::Moore) {
        // NE, SE, SW, NW
        {
            auto new_location = coord_wrap(GridCoord2D(x + 1, y - 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x + 1, y + 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x - 1, y + 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord2D(x - 1, y - 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }
    }

    return neighborhood;
}

std::vector<AgentID> *Grid2D::get_location_contents(
    GridCoord2D location) const {
    if (is_location_valid(location) && !is_location_empty(location)) {
        return &_agent_grid[location.get_x_location()]
                           [location.get_y_location()];
    }

    return nullptr;
}

unsigned int Grid2D::get_maximum_x(void) const { return _maximum_x; }
unsigned int Grid2D::get_maximum_y(void) const { return _maximum_y; }

GridCoord2D Grid2D::coord_wrap(GridCoord2D location) const {
    auto x = location.get_x_location();
    auto y = location.get_y_location();

    if (_wrap_x)
        x = (x + static_cast<int>(_maximum_x)) % static_cast<int>(_maximum_x);
    if (_wrap_x)
        y = (y + static_cast<int>(_maximum_y)) % static_cast<int>(_maximum_y);
    return GridCoord2D(x, y);
}

bool Grid2D::is_location_empty(GridCoord2D location) const {
    auto x = location.get_x_location();
    auto y = location.get_y_location();

    return _agent_grid[x][y].size() == 0;
}

}  // namespace kami
