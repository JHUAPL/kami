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
#define KAMI_POPULATION_H

#include <map>
#include <vector>

#include <kami/agent.h>
#include <kami/kami.h>

namespace kami {
    /**
     * An abstract for generic models
     */
    class LIBKAMI_EXPORT Population {
    protected:
        std::map<kami::AgentID, std::shared_ptr<Agent>> _agent_map;
        std::shared_ptr<Model> _model = nullptr;

    public:

        Population();

        explicit Population(std::shared_ptr<Model> model);

        /**
         * @brief Get the `Model` associated with this scheduler
         */
        std::shared_ptr<Model> get_model();

        /**
         * @brief Add a `Model` to this scheduler
         *
         * @details This method will associate a model with the
         * scheduler.
         */
        [[maybe_unused]] void set_model(std::shared_ptr<Model> model);

        /**
         * Get a reference to an `Agent` by `AgentID`
         *
         * @param[in] agent_id the `AgentID` to search for.
         *
         * @return a reference to the desired `Agent` or `nullptr` if not found.
         */
        [[nodiscard]] std::shared_ptr<Agent> get_agent_by_id(AgentID agent_id) const;

        /**
         * Add an Agent to the Population.
         *
         * @param agent The Agent to add.
         */
        void add_agent(const std::shared_ptr<Agent> &agent);

        /**
         * Remove an Agent from the Population.
         *
         * @param agent_id The AgentID of the agent to remove.
         */
        [[maybe_unused]] void delete_agent(AgentID agent_id);

        /*
         * Returns the agent list.
         */
        std::shared_ptr<std::vector<AgentID>> get_agent_list();
    };
}  // namespace kami

#endif  // KAMI_POPULATION_H
