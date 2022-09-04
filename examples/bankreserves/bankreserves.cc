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

#include "bankreserves.h"

#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <random>

#include <CLI/CLI.hpp>

#include <nlohmann/json.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <kami/agent.h>
#include <kami/multigrid2d.h>
#include <kami/kami.h>
#include <kami/model.h>
#include <kami/population.h>
#include <kami/random.h>
#include <kami/reporter.h>

std::shared_ptr<spdlog::logger> console = nullptr;
std::shared_ptr<std::mt19937> rng = nullptr;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EmptyDeclOrStmt"

int main(int argc, char **argv) {
    std::string ident = "bankreserves";
    std::string log_level_option = "info";
    std::string output_file_name = ident + ".json";
    CLI::App app{ident};
    unsigned int
            initial_seed = kami::Constants::JENNYS_NUMBER,
            max_steps = 100,
            x_size = 20,
            y_size = 20,
            agent_count = x_size * y_size,
            max_initial_wealth = 10;

    // This exercise is really stupid.
    auto levels_list = std::make_unique<std::list<std::string>>();
    for (auto &level_name: SPDLOG_LEVEL_NAMES)
        levels_list->push_back(std::string(level_name.data(), level_name.size()));

    app.add_option("-c", agent_count, "Set the number of agents")->check(CLI::PositiveNumber);
    app.add_option("-f", output_file_name, "Set the JSON report file")->check(CLI::ExistingPath);
    app.add_option("-l", log_level_option, "Set the logging level")->check(
            CLI::IsMember(levels_list.get(), CLI::ignore_case));
    app.add_option("-n", max_steps, "Set the number of steps to run the model")->check(CLI::PositiveNumber);
    app.add_option("-s", initial_seed, "Set the initial seed")->check(CLI::Number);
    app.add_option("-x", x_size, "Set the number of columns")->check(CLI::PositiveNumber);
    app.add_option("-y", y_size, "Set the number of rows")->check(CLI::PositiveNumber);
    app.add_option("-w", max_initial_wealth, "Set the maximum initial agent wealth")->check(CLI::PositiveNumber);
    CLI11_PARSE(app, argc, argv);

    console = spdlog::stdout_color_st(ident);
    console->set_level(spdlog::level::from_str(log_level_option));
    console->info("Compiled with Kami/{}, log level {}", kami::version.to_string(), log_level_option);

    console->info("Starting Bank Reserves Model with {} agents for {} steps", agent_count, max_steps);
    auto model = std::make_shared<BankReservesModel>(agent_count, x_size, y_size, initial_seed, max_initial_wealth);
    spdlog::stopwatch sw;
    for (int i = 0; i < max_steps; i++)
        model->step();
    console->info("Bank Reserves Model simulation complete, requiring {} seconds", sw);

    auto rpt = model->report();
    std::ofstream output_file(output_file_name);
    output_file << *rpt;
    console->info("JSON data report written to {}", output_file_name);
    console->trace("Done.");
}

#pragma clang diagnostic pop
