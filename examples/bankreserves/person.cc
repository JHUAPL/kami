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

kami::AgentID PersonAgent::step(std::shared_ptr<kami::ReporterModel> model) {
    console->trace("step() called for agent {}", get_agent_id());
    move_agent(model);
    do_business(model);
    balance_books(model);
    _bank->bank_balance();

    return get_agent_id();
}

std::optional<kami::GridCoord2D> PersonAgent::move_agent(std::shared_ptr<kami::ReporterModel> &model) {
    console->trace("move_agent() called for agent {}", get_agent_id());
    auto agent_id = get_agent_id();

    auto domain = model->get_domain();
    auto world = std::static_pointer_cast<kami::MultiGrid2D>(domain);

    auto move_list = world->get_neighborhood(agent_id, false, kami::GridNeighborhoodType::Moore);
    std::uniform_int_distribution<int> dist(0, (int) move_list->size() - 1);
    auto new_location = *std::next(move_list->begin(), dist(*rng));

    console->trace("Moving Agent {} to location {}", agent_id, new_location);
    world->move_agent(agent_id, new_location);

    return new_location;
}

std::optional<kami::AgentID> PersonAgent::do_business(std::shared_ptr<kami::ReporterModel> &model) {
    console->trace("do_business() called for agent {}", get_agent_id());
    auto agent_id = get_agent_id();

    if (!(_savings > 0 | _wallet > 0 | _bank->_available_to_loan > 0))
        return agent_id;

    auto world = std::static_pointer_cast<kami::MultiGrid2D>(model->get_domain());
    auto population = model->get_population();

    auto location = world->get_location_by_agent(agent_id);
    auto cell_mates_opt = world->get_location_contents(location);

    if (!cell_mates_opt)
        return std::nullopt;

    // Note, here we reverse the logic from that used in the Mesa
    // implementation.  We prefer the guard clause to the nested
    // if statements.  See Fowler.
    auto cell_mates = cell_mates_opt;
    if (cell_mates->size() < 2)
        return std::nullopt;

    auto customer_id = agent_id;
    std::uniform_int_distribution<int> dist(0, (int) cell_mates->size() - 1);
    do {            // There aren't enough do loops, ya know?
        customer_id = *std::next(cell_mates->begin(), dist(*rng));
    } while (customer_id == agent_id);

    std::bernoulli_distribution coin_flip(0.5);
    if (coin_flip(*rng))
        return std::nullopt;

    // If true, trade_amount = 5, if false, trade_amount = 2
    // Dropping the conditional should make this faster, but
    // really, this is just more elegant.
    auto trade_amount = (int) std::round(coin_flip(*rng)) * 3 + 2;

    auto customer = std::static_pointer_cast<PersonAgent>(population->get_agent_by_id(customer_id));
    console->debug("Agent {} trading amount {} with agent {}", agent_id, trade_amount, customer_id);
    customer->_wallet += trade_amount;
    _wallet -= trade_amount;

    return customer_id;
}

std::optional<int> PersonAgent::balance_books(std::shared_ptr<kami::ReporterModel> &model) {
    console->debug("balance_books() called for agent {} with wallet {}, savings {}, loans {}", get_agent_id(), _wallet,
                   _savings, _loans);

    if (_wallet < 0) {
        if (_savings >= -_wallet) {
            withdraw_from_savings(-_wallet);
        } else {
            if (_savings > 0) {
                withdraw_from_savings(_savings);
            }
            auto temp_loan = _bank->_available_to_loan;
            if (temp_loan >= -_wallet) {
                take_out_loan(-_wallet);
            } else {
                take_out_loan(temp_loan);
            }
        }
    } else {
        deposit_to_savings(_wallet);
    }

    if (_loans > 0 & _savings > 0) {
        if (_savings > _loans) {
            withdraw_from_savings(_loans);
            repay_a_loan(_loans);
        } else {
            withdraw_from_savings(_savings);
            repay_a_loan(_wallet);
        }
    }

    _wealth = _savings - _loans;
    console->debug("balance_books() exiting for agent {}, and wealth {}", get_agent_id(), _wealth);
    return _wealth;
}

kami::AgentID PersonAgent::deposit_to_savings(double amount) {
    console->debug("deposit_to_savings() called for agent {}, and amount {}", get_agent_id(), amount);
    _wallet -= amount;
    _savings += amount;
    _bank->_deposits += amount;
    return get_agent_id();
}

kami::AgentID PersonAgent::withdraw_from_savings(double amount) {
    console->debug("withdraw_from_savings() called for agent {}, and amount {}", get_agent_id(), amount);
    _wallet += amount;
    _savings -= amount;
    _bank->_deposits -= amount;
    return get_agent_id();
}

kami::AgentID PersonAgent::repay_a_loan(double amount) {
    console->debug("repay_a_loan() called for agent {}, and amount {}", get_agent_id(), amount);
    _loans -= amount;
    _wallet -= amount;
    _bank->_available_to_loan += amount;
    _bank->_bank_loans -= amount;
    return get_agent_id();
}

kami::AgentID PersonAgent::take_out_loan(double amount) {
    console->debug("take_out_loan() called for agent {}, and amount {}", get_agent_id(), amount);
    _loans += amount;
    _wallet += amount;
    _bank->_available_to_loan -= amount;
    _bank->_bank_loans += amount;
    return get_agent_id();
}
