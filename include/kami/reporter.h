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
#ifndef KAMI_REPORTER_H
//! @cond SuppressGuard
#define KAMI_REPORTER_H
//! @endcond

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <kami/agent.h>
#include <kami/model.h>

namespace kami {

    class Reporter;

    class ReporterAgent;

    class ReporterModel;

    class LIBKAMI_EXPORT ReporterAgent : public Agent {
    public:
        /**
         * @brief Collect the current state of the agent
         *
         * @details This function should collect the agent's
         * current state.  The agent, notably, does not need
         * to collect historical state, as the historical state
         * is retained by the `Reporter` instance until such
         * time as `Reporter::report()` is called.  However,
         * the implementation of the collect() function is
         * up to the end user who can, ultimately, return whatever
         * they want.
         *
         * The only restriction on collect is that it must return
         * its data as a [nlohmann::json](https://json.nlohmann.me/)
         * JSON object.  See `Reporter` for additional details.
         */
        virtual std::optional<std::unique_ptr<nlohmann::json>> collect() = 0;

        virtual AgentID step(std::shared_ptr<ReporterModel> model) = 0;

    private:
        AgentID step(std::shared_ptr<Model> model) override {
            return get_agent_id();
        };

        int _step_counter = 0;
    };

    class LIBKAMI_EXPORT ReporterModel : public Model {
    public:
        ReporterModel();

        /**
         * @brief Collect the current state of the model
         *
         * @details This function should collect the model's
         * current state.  The model, notably, does not need
         * to collect historical state, as the historical state
         * is retained by the `Reporter` instance until such
         * time as `Reporter::report()` is called.  However,
         * the implementation of the collect() function is
         * up to the end user who can, ultimately, return whatever
         * they want.
         *
         * This is not expected to return agent data collection,
         * as the agents' information is collected separately.
         */
        virtual std::optional<std::unique_ptr<nlohmann::json>> collect() = 0;

        /**
         * @brief Get the step id of the model
         *
         * @details The step_id should probably be a monotonically
         * incrementing integer.
         */
        inline virtual unsigned int get_step_id() {
            return _step_count;
        };

        /**
         *
         */
        std::shared_ptr<Model> step() override;

        std::unique_ptr<nlohmann::json> report();

    protected:
        std::shared_ptr<Reporter> _rpt;
        unsigned int _step_count{};
    };

    class LIBKAMI_EXPORT Reporter : public std::enable_shared_from_this<Reporter> {
    public:
        Reporter();

        std::shared_ptr<Reporter> clear();

        std::unique_ptr<nlohmann::json> collect(const std::shared_ptr<ReporterModel> &model);

        std::unique_ptr<nlohmann::json>
        collect(const std::shared_ptr<ReporterModel> &model, const std::shared_ptr<Population> &pop);

        std::unique_ptr<nlohmann::json>
        collect(const std::shared_ptr<ReporterModel> &model, const std::unique_ptr<std::vector<AgentID>> &agent_list);

        std::unique_ptr<nlohmann::json> report(const std::shared_ptr<ReporterModel> &model);

    protected:
        std::unique_ptr<std::vector<nlohmann::json>> _report_data = nullptr;
    };

}

#endif //KAMI_REPORTER_H
