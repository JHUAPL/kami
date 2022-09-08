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

        /**
         * @brief Execute a time-step for the agent
         *
         * @details This function should step the agent instance.  Any activities that the
         * agent should perform as part of its time step should be in this function.
         *
         * @param model a reference copy of the model
         *
         * @returns a copy of the AgentID
         */
        virtual AgentID step(std::shared_ptr<ReporterModel> model) = 0;

    private:
        // This should be uncallable, but knocks out the inherited method.
        AgentID step(std::shared_ptr<Model> model) override;;

        int _step_counter = 0;
    };

    class LIBKAMI_EXPORT ReporterModel : public Model {
    public:
        /**
         * @brief Constructor
         */
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
        virtual unsigned int get_step_id();

        /**
         * @brief Execute a single time step of the model
         *
         * @details This method will collect all the `Agent`s in the `Population` associated
         * with the model and pass them to the associated `Scheduler` for stepping.  After scheduling,
         * this method will run the collect() for the `Reporter` associated with this model.
         *
         * @returns a shared pointer to the model instance
         */
        virtual std::shared_ptr<Model> step() override;

        /**
         * @brief Get the current report
         *
         * @details This method will return an object containg the data collected to that
         * point in the simulation.
         *
         * @returns a unique pointer to a `nlohmann::json` object representing the current report
         */
        std::unique_ptr<nlohmann::json> report();

    protected:

        /**
         * @brief The current report
         */
        std::shared_ptr<Reporter> _rpt;

        /**
         * @brief The model's current step count
         */
        unsigned int _step_count{};
    };

    class LIBKAMI_EXPORT Reporter : public std::enable_shared_from_this<Reporter> {
    public:
        /**
         * @brief Constructor
         */
        Reporter();

        /**
         * @brief Empty the report
         *
         * @details Clear all entries from the report; new collection
         * operations begin with a blank slate.
         *
         * @returns a reference copy of the `Reporter`
         */
        std::shared_ptr<Reporter> clear();

        /**
         * @brief Collect the current state of the model
         *
         * @details This will collect the current state of
         * each agent associated with the population returned
         * by the `Model`'s `get_population()`.
         *
         * @param model reference copy of the model
         *
         * @returns a copy of the current report
         */
        std::unique_ptr<nlohmann::json> collect(const std::shared_ptr<ReporterModel> &model);

        /**
         * @brief Collect the current state of the model
         *
         * @details This will collect the current state of
         * each agent associated with the `Population`.
         *
         * @param model reference copy of the model
         * @param pop Population to collect on
         *
         * @returns a copy of the current report
         */
        std::unique_ptr<nlohmann::json>
        collect(const std::shared_ptr<ReporterModel> &model, const std::shared_ptr<Population> &pop);

        /**
         * @brief Collect the current state of the model
         *
         * @details This will collect the current state of
         * each agent given
         *
         * @param model reference copy of the model
         * @param agent_list a vector agents to report on
         *
         * @returns a copy of the current report
         */
        std::unique_ptr<nlohmann::json>
        collect(const std::shared_ptr<ReporterModel> &model, const std::unique_ptr<std::vector<AgentID>> &agent_list);

        /**
         * @brief Collect the report
         *
         * @details This will return the aggregate report
         * of all the data collected by this `Reporter`.
         *
         * @param model reference copy of the model
         *
         * @returns a copy of the current report
         */
        std::unique_ptr<nlohmann::json> report(const std::shared_ptr<ReporterModel> &model);

    protected:
        /**
         * @brief A vector of the the report collected so far
         */
        std::unique_ptr<std::vector<nlohmann::json>> _report_data = nullptr;
    };

}

#endif //KAMI_REPORTER_H
