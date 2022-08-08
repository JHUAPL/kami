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

#include "starter.h"

#include <map>
#include <memory>
#include <random>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <kami/agent.h>
#include <kami/kami.h>
#include <kami/model.h>
#include <kami/population.h>
#include <kami/random.h>

std::shared_ptr<spdlog::logger> console = nullptr;
std::shared_ptr<std::ranlux24> rng = nullptr;

template <>
struct fmt::formatter<kami::AgentID> : fmt::formatter<std::string> {
    static auto format(kami::AgentID agent_id, format_context &ctx) {
        return format_to(ctx.out(), "{}", agent_id.to_string());
    }
};

StarterAgent::StarterAgent() {
    console->debug("StarterAgent with ID {} constructed", this->get_agent_id());
}

StarterAgent::~StarterAgent() {
    console->debug("StarterAgent with ID {} deconstructed", this->get_agent_id());
}

kami::AgentID StarterAgent::step(std::shared_ptr<kami::Model> model) {
    this->_step_counter++;
    return this->get_agent_id();
}

StarterModel::StarterModel(unsigned int number_agents, unsigned int new_seed) {
    rng = std::make_shared<std::ranlux24>();
    rng->seed(new_seed);

    auto sched = std::make_shared<kami::RandomScheduler>(rng);
    auto pop = std::make_shared<kami::Population>();

    _sched = sched;
    _pop = pop;

    console->debug("Scheduler initiated with seed {}", new_seed);

    _step_count = 0;

    for (unsigned int i = 0; i < number_agents; i++) {
        auto new_agent = std::make_shared<StarterAgent>();

        console->trace("Initializing agent with AgentID {}", new_agent->get_agent_id());
        _pop->add_agent(new_agent);
    }
}

std::shared_ptr<kami::Model> StarterModel::run(unsigned int steps) {
    for (auto i = 0; i < steps; i++) step();
    return shared_from_this();
}

std::shared_ptr<kami::Model> StarterModel::step() {
    console->trace("Executing model step {}", ++_step_count);
    _sched->step(shared_from_this());
    return shared_from_this();
}

int main(int argc, char **argv) {
    std::string ident = "starter";
    std::string log_level_option = "info";
    CLI::App app{ident};
    unsigned int agent_count = 100, max_steps = 100, initial_seed = 8675309;

    app.add_option("-c", agent_count, "Set the number of agents")->check(CLI::PositiveNumber);
    app.add_option("-l", log_level_option, "Set the logging level")->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    app.add_option("-n", max_steps, "Set the number of steps to run the model")->check(CLI::PositiveNumber);
    app.add_option("-s", initial_seed, "Set the initial seed")->check(CLI::Number);
    CLI11_PARSE(app, argc, argv);

    console = spdlog::stdout_color_st(ident);
    console->set_level(spdlog::level::from_str(log_level_option));
    console->info("Compiled with Kami/{}, log level {}", kami::version.to_string(), log_level_option);
    console->info("Starting Starter Model with {} agents for {} steps", agent_count, max_steps);

    auto model = std::make_shared<StarterModel>(agent_count, initial_seed);

    spdlog::stopwatch sw;
    for (int i = 0; i < max_steps; i++)
        model->step();

    console->info("Starter Model simulation complete, requiring {} seconds", sw);
}
