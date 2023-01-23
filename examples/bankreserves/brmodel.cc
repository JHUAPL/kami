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

#include <nlohmann/json.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <kami/agent.h>
#include <kami/multigrid2d.h>
#include <kami/kami.h>
#include <kami/random.h>
#include <kami/reporter.h>

BankReservesModel::BankReservesModel(
        unsigned int agent_count,
        unsigned int x_size,
        unsigned int y_size,
        unsigned int initial_seed,
        unsigned int max_initial_wealth
) {
    rng = std::make_shared<std::mt19937>();
    rng->seed(initial_seed);

    auto domain = std::make_shared<kami::MultiGrid2D>(x_size, y_size, true, true);
    auto sched = std::make_shared<kami::RandomScheduler>(rng);
    auto pop = std::make_shared<kami::Population>();

    std::static_pointer_cast<void>(set_scheduler(sched));
    std::static_pointer_cast<void>(set_domain(domain));
    std::static_pointer_cast<void>(set_population(pop));

    console->debug("Scheduler initiated with seed {}", initial_seed);
    auto bank_agent = std::make_shared<BankAgent>(10);
    pop->add_agent(bank_agent);

    _step_count = 0;

    std::uniform_int_distribution<int> dist_x(0, (int) x_size - 1);
    std::uniform_int_distribution<int> dist_y(0, (int) y_size - 1);
    std::uniform_int_distribution<unsigned int> dist(1, max_initial_wealth);

    for (auto i = 0; i < agent_count; i++) {
        auto wallet = dist(*rng);
        auto new_agent = std::make_shared<PersonAgent>(10, bank_agent);

        pop->add_agent(new_agent);
        domain->add_agent(new_agent->get_agent_id(), kami::GridCoord2D(dist_x(*rng), dist_x(*rng)));
        console->trace("Initialized agent with AgentID {} with wallet {}", new_agent->get_agent_id(), wallet);
    }
}