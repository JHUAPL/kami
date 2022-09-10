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
#include <optional>
#include <vector>

#include <kami/agent.h>
#include <kami/model.h>
#include <kami/reporter.h>
#include <kami/sequential.h>
#include <kami/staged.h>

namespace kami {

    std::unique_ptr<std::vector<AgentID>>
    StagedScheduler::step(std::shared_ptr<Model> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        auto stepped_agent_list = this->SequentialScheduler::step(model, std::move(agent_list));
        return std::move(this->advance(model, std::move(stepped_agent_list)));
    }

    std::unique_ptr<std::vector<AgentID>>
    StagedScheduler::step(std::shared_ptr<ReporterModel> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        auto stepped_agent_list = this->SequentialScheduler::step(model, std::move(agent_list));
        return std::move(this->advance(model, std::move(stepped_agent_list)));
    }

    std::unique_ptr<std::vector<AgentID>> StagedScheduler::advance(std::shared_ptr<Model> model) {
        auto population = model->get_population();
        return std::move(this->advance(model, population->get_agent_list()));
    }

    std::unique_ptr<std::vector<AgentID>> StagedScheduler::advance(std::shared_ptr<ReporterModel> model) {
        auto population = model->get_population();
        return std::move(this->advance(model, population->get_agent_list()));
    }

    std::unique_ptr<std::vector<AgentID>>
    StagedScheduler::advance(std::shared_ptr<Model> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        auto return_agent_list = std::make_unique<std::vector<AgentID>>();
        auto population = model->get_population();

        for (auto &agent_id: *agent_list) {
            auto agent = std::static_pointer_cast<StagedAgent>(population->get_agent_by_id(agent_id));

            agent->advance(model);
            return_agent_list->push_back(agent_id);
        }

        return std::move(return_agent_list);
    }

}  // namespace kami
