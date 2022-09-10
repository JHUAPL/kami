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
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <fmt/format.h>

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/exception.h>
#include <kami/grid1d.h>

namespace kami {

    GridCoord1D::GridCoord1D(int x_coord) : _x_coord(x_coord) {}

    int GridCoord1D::x() const {
        return _x_coord;
    }

    std::string GridCoord1D::to_string() const {
        return std::string("(" + std::to_string(_x_coord) + ")");
    }

    double GridCoord1D::distance(std::shared_ptr<Coord> &p) const {
        auto p1d = std::static_pointer_cast<GridCoord1D>(p);
        return static_cast<double>(abs(_x_coord - p1d->_x_coord));
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

    GridCoord1D operator+(const GridCoord1D &lhs, const GridCoord1D &rhs) {
        return GridCoord1D(lhs._x_coord + rhs._x_coord);
    }

    GridCoord1D operator-(const GridCoord1D &lhs, const GridCoord1D &rhs) {
        return GridCoord1D(lhs._x_coord - rhs._x_coord);
    }

    GridCoord1D operator*(const GridCoord1D &lhs, const double rhs) {
        return GridCoord1D(static_cast<int>(lhs._x_coord * rhs));
    }

    GridCoord1D operator*(const double lhs, const GridCoord1D &rhs) {
        return GridCoord1D(static_cast<int>(rhs._x_coord * lhs));
    }


    Grid1D::Grid1D(unsigned int maximum_x, bool wrap_x) {
        _maximum_x = maximum_x;
        _wrap_x = wrap_x;

        _agent_grid = std::make_unique<std::unordered_multimap<GridCoord1D, AgentID>>();
        _agent_index = std::make_unique<std::map<AgentID, GridCoord1D>>();
    }

    AgentID Grid1D::delete_agent(AgentID agent_id) {
        return delete_agent(agent_id, get_location_by_agent(agent_id));
    }

    AgentID Grid1D::delete_agent(AgentID agent_id, const GridCoord1D &coord) {
        for (auto test_agent_id = _agent_grid->find(coord); test_agent_id != _agent_grid->end(); test_agent_id++)
            if (test_agent_id->second == agent_id) {
                _agent_grid->erase(test_agent_id);
                _agent_index->erase(agent_id);
                return agent_id;
            }

        throw exception::AgentNotFound("");
    }

    bool Grid1D::is_location_valid(const GridCoord1D &coord) const {
        auto x = coord.x();

        return (x >= 0 && x < static_cast<int>(_maximum_x));
    }

    bool Grid1D::is_location_empty(const GridCoord1D &coord) const {
        auto grid_location = _agent_grid->equal_range(coord);
        return grid_location.first == grid_location.second;
    }

    AgentID Grid1D::move_agent(const AgentID agent_id, const GridCoord1D &coord) {
        return add_agent(delete_agent(agent_id, get_location_by_agent(agent_id)), coord);
    }

    std::shared_ptr<std::unordered_set<GridCoord1D>>
    Grid1D::get_neighborhood(const AgentID agent_id, const bool include_center) const {
        return std::move(get_neighborhood(get_location_by_agent(agent_id), include_center));
    }

    std::shared_ptr<std::unordered_set<GridCoord1D>>
    Grid1D::get_neighborhood(const GridCoord1D &coord, const bool include_center) const {
        auto neighborhood = std::make_shared<std::unordered_set<GridCoord1D>>();

        // We assume our starting position is valid
        if (include_center)
            neighborhood->insert(coord);

        for (auto &direction: directions) {
            auto new_location = coord_wrap(coord + direction);

            if (is_location_valid(new_location))
                neighborhood->insert(new_location);
        }

        return std::move(neighborhood);
    }

    std::shared_ptr<std::set<AgentID>> Grid1D::get_location_contents(const GridCoord1D &coord) const {
        auto agent_ids = std::make_shared<std::set<AgentID>>();

        if (!is_location_valid(coord))
            throw exception::LocationUnavailable(fmt::format("Coordinates {} are invalid", coord.to_string()));
        if (is_location_empty(coord))
            return agent_ids;

        auto agent_range = _agent_grid->equal_range(coord);
        if (agent_range.first == agent_range.second)
            return agent_ids;

        for (auto i = agent_range.first; i != agent_range.second; i++)
            agent_ids->insert(i->second);
        return agent_ids;
    }

    bool Grid1D::get_wrap_x() const { return _wrap_x; }

    unsigned int Grid1D::get_maximum_x() const { return _maximum_x; }

    GridCoord1D Grid1D::get_location_by_agent(const AgentID &agent_id) const {
        auto coord = _agent_index->find(agent_id);
        if (coord == _agent_index->end())
            throw exception::AgentNotFound(fmt::format("Agent {} not found on grid", agent_id.to_string()));
        return coord->second;
    }

    GridCoord1D Grid1D::coord_wrap(const GridCoord1D &coord) const {
        auto x = coord.x();

        if (_wrap_x)
            x = (x + static_cast<int>(_maximum_x)) % static_cast<int>(_maximum_x);
        return GridCoord1D(x);
    }

}  // namespace kami
