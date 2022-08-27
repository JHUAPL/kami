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

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include <kami/population.h>
#include <kami/reporter.h>
#include <kami/scheduler.h>

namespace kami {

    ReporterModel::ReporterModel() {
        _step_count = 0;
        _rpt = std::make_shared<Reporter>();
    }

    std::shared_ptr<Model> ReporterModel::step() {
        _step_count++;

        auto ret = _sched->step(std::static_pointer_cast<ReporterModel>(shared_from_this()));
        auto rpt = _rpt->collect(std::static_pointer_cast<ReporterModel>(shared_from_this()));

        return shared_from_this();
    }

    std::unique_ptr<nlohmann::json> ReporterModel::report() {
        return std::move(_rpt->report(std::static_pointer_cast<ReporterModel>(shared_from_this())));
    }

    Reporter::Reporter() {
        _report_data = std::make_unique<std::vector<nlohmann::json>>();
    }

    std::shared_ptr<Reporter> Reporter::clear() {
        // I _can_ do this in one line, but I won't
        _report_data.reset();
        _report_data = std::make_unique<std::vector<nlohmann::json>>();
        return shared_from_this();
    }

    std::unique_ptr<nlohmann::json>
    Reporter::collect(const std::shared_ptr<ReporterModel> &model) {
        auto pop = model->get_population();
        return collect(model, pop.value());
    }

    std::unique_ptr<nlohmann::json>
    Reporter::collect(const std::shared_ptr<ReporterModel> &model, const std::shared_ptr<Population> &pop) {
        auto agent_list = pop->get_agent_list();
        return collect(model, agent_list);
    }

    std::unique_ptr<nlohmann::json>
    Reporter::collect(const std::shared_ptr<ReporterModel> &model,
                      const std::unique_ptr<std::vector<AgentID>> &agent_list) {
        auto collection_array = std::vector<nlohmann::json>();

        for (auto &agent_id: *agent_list) {
            auto agent_data = nlohmann::json();
            auto agent_opt = model->get_population().value()->get_agent_by_id(agent_id);

            agent_data["agent_id"] = agent_id.to_string();
            if (!agent_opt) {
                agent_data["data"] = {};                    // Record JSON null
            } else {
                auto agent = std::static_pointer_cast<ReporterAgent>(agent_opt.value());
                auto agent_collection = agent->collect();
                if (agent_collection)
                    agent_data["data"] = *agent_collection.value();
            }
            collection_array.push_back(agent_data);
        }
        auto model_data = model->collect();
        auto agent_collection = std::make_unique<nlohmann::json>(collection_array);
        auto collection = std::make_unique<nlohmann::json>();

        (*collection)["step_id"] = model->get_step_id();
        if (model_data)
            (*collection)["model_data"] = *model_data.value();
        (*collection)["agent_data"] = *agent_collection;

        _report_data->push_back(*collection);

        return std::move(collection);
    }

    std::unique_ptr<nlohmann::json> Reporter::report(const std::shared_ptr<ReporterModel> &model) {
        auto json_data = std::make_unique<nlohmann::json>(*_report_data);
        return std::move(json_data);
    }

}  // namespace kami
