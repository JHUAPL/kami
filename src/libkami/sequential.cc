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

#include <memory>
#include <vector>

#include <kami/agent.h>
#include <kami/reporter.h>
#include <kami/sequential.h>

namespace kami {

    std::unique_ptr<std::vector<AgentID>> SequentialScheduler::step(std::shared_ptr<Model> model) {
        auto population = model->get_population();
        return std::move(this->step(model, population->get_agent_list()));
    }

    std::unique_ptr<std::vector<AgentID>> SequentialScheduler::step(std::shared_ptr<ReporterModel> model) {
        auto population = model->get_population();
        return std::move(this->step(model, population->get_agent_list()));
    }

    std::unique_ptr<std::vector<AgentID>>
    SequentialScheduler::step(std::shared_ptr<Model> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        auto return_agent_list = std::make_unique<std::vector<AgentID>>();
        auto population = model->get_population();

        Scheduler::_step_counter++;
        for (auto &agent_id: *agent_list) {
            auto agent = population->get_agent_by_id(agent_id);

            agent->step(model);
            return_agent_list->push_back(agent_id);
        }

        return std::move(return_agent_list);
    }

    std::unique_ptr<std::vector<AgentID>>
    SequentialScheduler::step(std::shared_ptr<ReporterModel> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        auto return_agent_list = std::make_unique<std::vector<AgentID>>();
        auto population = model->get_population();

        Scheduler::_step_counter++;
        for (auto &agent_id: *agent_list) {
            auto agent = population->get_agent_by_id(agent_id);

            agent->step(model);
            return_agent_list->push_back(agent_id);
        }

        return std::move(return_agent_list);
    }

}  // namespace kami
