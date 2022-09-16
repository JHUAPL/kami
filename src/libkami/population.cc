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

#include <algorithm>
#include <utility>
#include <vector>

#include <kami/agent.h>
#include <kami/error.h>
#include <kami/population.h>

namespace kami {

    AgentID Population::add_agent(const std::shared_ptr<Agent> &agent) noexcept {
        auto agent_id = agent->get_agent_id();
        _agent_map.insert(std::pair<AgentID, std::shared_ptr<Agent>>(agent_id, agent));
        return agent->get_agent_id();
    }

    std::shared_ptr<Agent> Population::delete_agent(const AgentID agent_id) {
        auto agent_it = _agent_map.find(agent_id);

        if (agent_it == _agent_map.end())
            throw error::ResourceNotAvailable("Agent not found in population");

        auto agent = agent_it->second;
        _agent_map.erase(agent_it);
        return std::move(agent);
    }

    std::shared_ptr<Agent> Population::get_agent_by_id(const AgentID agent_id) const {
        auto agent_it = _agent_map.find(agent_id);

        if (agent_it == _agent_map.end())
            throw error::AgentNotFound("Agent not found in population");

        return agent_it->second;
    }

    std::unique_ptr<std::vector<AgentID>> Population::get_agent_list() const {
        auto key_selector = [](auto pair) { return pair.first; };
        auto agent_ids = std::make_unique<std::vector<AgentID>>(_agent_map.size());

        transform(_agent_map.begin(), _agent_map.end(), agent_ids->begin(), key_selector);
        return std::move(agent_ids);
    }

}  // namespace kami
