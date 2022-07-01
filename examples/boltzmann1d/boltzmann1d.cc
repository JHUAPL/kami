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

#include "boltzmann1d.h"

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
#include <kami/multigrid1d.h>

kami::MultiGrid1D *MoneyAgent1D::_world = nullptr;
BoltzmannWealthModel1D *MoneyAgent1D::_model = nullptr;
std::shared_ptr<spdlog::logger> console = nullptr;
std::shared_ptr<std::mt19937> rng = nullptr;

template <>
struct fmt::formatter<kami::AgentID> : fmt::formatter<std::string> {
    [[maybe_unused]] static auto format(kami::AgentID agent_id, format_context &ctx) {
        return format_to(ctx.out(), "{}", agent_id.to_string());
    }
};

template <>
struct fmt::formatter<kami::GridCoord1D> : fmt::formatter<std::string> {
    [[maybe_unused]] static auto format(const kami::GridCoord1D& coord, format_context &ctx) {
        return format_to(ctx.out(), "{}", coord.to_string());
    }
};

void MoneyAgent1D::step() {
    _step_counter++;

    console->trace("Agent {} is moving", this->get_agent_id());
    move_agent();
    console->trace("Agent {} is giving money", this->get_agent_id());
    if (_agent_wealth > 0) give_money();
}

void MoneyAgent1D::set_world(kami::MultiGrid1D *world) { _world = world; }

void MoneyAgent1D::set_model(BoltzmannWealthModel1D *model) { _model = model; }

void MoneyAgent1D::move_agent() {
    console->trace("Entering move_agent");
    auto agent_id = get_agent_id();
    auto move_list = _world->get_neighborhood(agent_id, false);
    std::uniform_int_distribution<int> dist(0, (int)move_list.size() - 1);
    auto new_location = move_list[dist(*rng)];

    console->trace("Moving Agent {} to location {}", agent_id, new_location);
    _world->move_agent(agent_id, new_location);
    console->trace("Exiting move_agent");
}

void MoneyAgent1D::give_money() {
    kami::AgentID agent_id = get_agent_id();
    kami::GridCoord1D location = _world->get_location_by_agent(agent_id);
    std::vector<kami::AgentID> *cell_mates = _world->get_location_contents(location);

    if (cell_mates->size() > 1) {
        std::uniform_int_distribution<int> dist(0, (int)cell_mates->size() - 1);
        kami::AgentID other_agent_id = cell_mates->at(dist(*rng));
        auto other_agent = _model->get_agent_by_id(other_agent_id);

        console->trace("Agent {} giving unit of wealth to agent {}", agent_id, other_agent_id);
        other_agent->_agent_wealth += 1;
        _agent_wealth -= 1;
    }
}

BoltzmannWealthModel1D::BoltzmannWealthModel1D(unsigned int number_agents, unsigned int length_x) {
    _world = new kami::MultiGrid1D(length_x, true);
    _sched = new kami::RandomScheduler(this, rng);

    _step_count = 0;
    MoneyAgent1D::set_world(_world);
    MoneyAgent1D::set_model(this);

    std::uniform_int_distribution<int> dist(0, (int)length_x - 1);

    for (unsigned int i = 0; i < number_agents; i++) {
        auto *new_agent = new MoneyAgent1D();

        _agent_list.insert(std::pair<kami::AgentID, MoneyAgent1D *>(new_agent->get_agent_id(), new_agent));
        _sched->add_agent(new_agent->get_agent_id());
        _world->add_agent(new_agent->get_agent_id(), kami::GridCoord1D(dist(*rng)));
    }
}

BoltzmannWealthModel1D::~BoltzmannWealthModel1D() {
    for (auto & agent_pair : _agent_list)
        delete agent_pair.second;

    delete _sched;
    delete _world;
}

void BoltzmannWealthModel1D::step() {
    _step_count++;
    _sched->step();
}

void BoltzmannWealthModel1D::run(unsigned int steps) {
    for (auto i = 0; i < steps; i++) step();
}

MoneyAgent1D *BoltzmannWealthModel1D::get_agent_by_id(kami::AgentID _agent_id) const {
    MoneyAgent1D *_agent_pair = _agent_list.at(_agent_id);

    return _agent_pair;
}

int main(int argc, char **argv) {
    std::string ident = "boltzmann1d";
    std::string log_level_option = "info";
    CLI::App app{ident};
    unsigned int x_size = 16, agent_count = x_size, max_steps = 100, initial_seed = 42;

    app.add_option("-c", agent_count, "Set the number of agents")->check(CLI::PositiveNumber);
    app.add_option("-l", log_level_option, "Set the logging level")->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    app.add_option("-n", max_steps, "Set the number of steps to run the model")->check(CLI::PositiveNumber);
    app.add_option("-s", initial_seed, "Set the initial seed")->check(CLI::Number);
    app.add_option("-x", x_size, "Set the number of columns")->check(CLI::PositiveNumber);
    CLI11_PARSE(app, argc, argv);

    console = spdlog::stdout_color_st(ident);
    console->set_level(spdlog::level::from_str(log_level_option));
    console->info("Compiled with Kami/{}, log level {}", kami::version.to_string(), log_level_option);
    console->info("Starting Boltzmann Wealth Model with {} agents on a {}-unit grid for {} steps",agent_count, x_size, max_steps);

    rng = std::make_shared<std::mt19937>(initial_seed);
    BoltzmannWealthModel1D model(agent_count, x_size);

    spdlog::stopwatch sw;
    for (int i = 0; i < max_steps; i++) {
        console->trace("Initiating model step {}", i);
        model.step();
    }
    console->info("Boltzmann Wealth Model simulation complete, requiring {} seconds", sw);
}
