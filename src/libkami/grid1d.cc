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
#include <kami/grid1d.h>

#include <map>
#include <utility>
#include <vector>

namespace kami {

    int GridCoord1D::get_x_location() const { return _x_coord; }

    std::string GridCoord1D::to_string() const {
        return std::string("(" + std::to_string(_x_coord) + ")");
    }

    bool operator==(const GridCoord1D &lhs, const GridCoord1D &rhs) {
        return (lhs._x_coord == rhs._x_coord);
    }

    bool operator!=(const GridCoord1D &lhs, const GridCoord1D &rhs) {
        return !(lhs == rhs);
    }

    std::ostream &operator<<(std::ostream &lhs, const GridCoord1D &rhs) {
        return lhs << rhs.to_string();
    }

    Grid1D::Grid1D(unsigned int maximum_x, bool wrap_x) {
        _agent_grid = new std::vector<AgentID>[maximum_x];
        _agent_index = new std::map<AgentID, GridCoord1D>;

        _maximum_x = maximum_x;
        _wrap_x = wrap_x;
    }

    Grid1D::~Grid1D() {
        delete _agent_index;
        delete[] _agent_grid;
    }

    bool Grid1D::delete_agent(AgentID agent_id) {
        GridCoord1D coord = get_location_by_agent(agent_id);

        return delete_agent(agent_id, coord);
    }

    bool Grid1D::is_location_valid(const GridCoord1D& coord) const {
        auto x = coord.get_x_location();
        return (x >= 0 && x < static_cast<int>(_maximum_x));
    }

    bool Grid1D::is_location_empty(const GridCoord1D &coord) const {
        auto x = coord.get_x_location();

        return _agent_grid[x].empty();
    }

    bool Grid1D::delete_agent(AgentID agent_id, const GridCoord1D &coord) {
        auto agent_list = _agent_grid[static_cast<int>(coord.get_x_location())];

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

    bool Grid1D::move_agent(AgentID agent_id, GridCoord1D coord) {
        GridCoord1D coord_current = get_location_by_agent(agent_id);

        if (delete_agent(agent_id, coord_current))
            return add_agent(agent_id, std::move(coord));
        return false;
    }

    std::vector<GridCoord1D> Grid1D::get_neighborhood(AgentID agent_id, bool include_center) const {
        GridCoord1D coord = get_location_by_agent(agent_id);

        return get_neighborhood(coord, include_center);
    }

    std::vector<GridCoord1D> Grid1D::get_neighborhood(const GridCoord1D& coord, bool include_center) const {
        std::vector<GridCoord1D> neighborhood;
        auto x = coord.get_x_location();

        // We assume our starting position is valid
        if (include_center) neighborhood.push_back(coord);

        // E, W
        {
            auto new_location = coord_wrap(GridCoord1D(x + 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }
        {
            auto new_location = coord_wrap(GridCoord1D(x - 1));
            if (is_location_valid(new_location))
                neighborhood.push_back(coord_wrap(new_location));
        }

        return neighborhood;
    }

    std::vector<AgentID> *Grid1D::get_location_contents(const GridCoord1D& coord) const {
        if (is_location_valid(coord)) return &_agent_grid[coord.get_x_location()];
        return nullptr;
    }

    bool Grid1D::get_wrap_x() const { return _wrap_x; }

    unsigned int Grid1D::get_maximum_x() const { return _maximum_x; }

    GridCoord1D Grid1D::get_location_by_agent(AgentID agent_id) const {
        return _agent_index->at(agent_id);
    }

    GridCoord1D Grid1D::coord_wrap(const GridCoord1D& coord) const {
        auto x = coord.get_x_location();

        if(_wrap_x)
            x = (x + static_cast<int>(_maximum_x)) % static_cast<int>(_maximum_x);
        return GridCoord1D(x);
    }

}  // namespace kami
