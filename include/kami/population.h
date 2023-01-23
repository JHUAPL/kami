/*-
 * Copyright (c) 2022 The Johns Hopkins University Applied Physics
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
#ifndef KAMI_POPULATION_H
//! @cond SuppressGuard
#define KAMI_POPULATION_H
//! @endcond

#include <map>
#include <vector>

#include <kami/agent.h>
#include <kami/kami.h>

namespace kami {

    /**
     * @brief An abstract for generic models
     */
    class LIBKAMI_EXPORT Population {
    public:
        /**
         * @brief Get a reference to an `Agent` by `AgentID`
         *
         * @param[in] agent_id the `AgentID` to search for.
         *
         * @return a reference to the desired `Agent` or nothing is not found
         */
        [[nodiscard]] std::shared_ptr<Agent> get_agent_by_id(AgentID agent_id) const;

        /**
         * @brief Add an Agent to the Population.
         *
         * @param agent The Agent to add.
         *
         * @returns the ID of the agent added
         */
        AgentID add_agent(const std::shared_ptr<Agent>& agent) noexcept;

        /**
         * @brief Remove an Agent from the Population.
         *
         * @param agent_id The AgentID of the agent to remove.
         *
         * @returns a shared pointer to the Agent deleted
         */
        std::shared_ptr<Agent> delete_agent(AgentID agent_id);

        /**
         * @brief Returns the agent list.
         *
         * @returns a `std::vector` of all the `AgentID`'s in the `Population`
         */
        [[nodiscard]] std::unique_ptr<std::vector<AgentID>> get_agent_list() const;

    protected:
        /**
         * @brief A mapping of `AgentID` to `Agent` pointers
         *
         * @details This is the mapping of all `AgentID`s to
         * pointers to the corresponding `Agent` in this population.
         * This is left exposed as protected should any subclass
         * wish to manipulate this mapping directly.
         */
        std::map<kami::AgentID, std::shared_ptr<Agent>> _agent_map;
    };
}  // namespace kami

#endif  // KAMI_POPULATION_H
