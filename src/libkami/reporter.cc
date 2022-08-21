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

#include <memory>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include <kami/population.h>
#include <kami/reporter.h>

namespace kami {

    Reporter::Reporter() {
        _report_data = std::make_shared<std::unordered_map<std::shared_ptr<ReporterModel>, std::shared_ptr<std::vector<nlohmann::json>>>>();
    }

    std::shared_ptr<Reporter> Reporter::clear() {
        for (const auto &i: *_report_data)
            static_cast<void>(clear(i.first));
        return shared_from_this();
    }

    std::shared_ptr<Reporter> Reporter::clear(const std::shared_ptr<ReporterModel> &model) {
        auto _model_data = _report_data->at(model);
        _model_data->clear();
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
                agent_data["data"] = *agent_collection;
            }
            collection_array.push_back(agent_data);
        }
        auto model_data = model->collect();
        auto agent_collection = std::make_unique<nlohmann::json>(collection_array);
        auto collection = std::make_unique<nlohmann::json>();

        (*collection)["step_id"] = model->get_stepid();
        (*collection)["model_data"] = *model_data;
        (*collection)["agent_data"] = *agent_collection;

        auto jsonvec = _report_data->at(model);
        if (!jsonvec)
            jsonvec = std::make_shared<std::vector<nlohmann::json>>();
        jsonvec->push_back(*collection);

        return std::move(collection);
    }

    std::unique_ptr<nlohmann::json> Reporter::report(const std::shared_ptr<ReporterModel> &model) {
        auto jsonvec = _report_data->at(model);

        if (!jsonvec)
            jsonvec = std::make_shared<std::vector<nlohmann::json>>();
        auto jsonrpt = std::make_unique<nlohmann::json>(*jsonvec);

        return std::move(jsonrpt);
    }

}  // namespace kami
