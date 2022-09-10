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
#ifndef BANKRESERVES_H
//! @cond SuppressGuard
#define BANKRESERVES_H
//! @endcond

#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <kami/agent.h>
#include <kami/multigrid2d.h>
#include <kami/kami.h>
#include <kami/random.h>
#include <kami/reporter.h>

extern std::shared_ptr<spdlog::logger> console;
extern std::shared_ptr<std::mt19937> rng;

template<>
struct fmt::formatter<kami::AgentID> : fmt::formatter<std::string> {
    static auto format(kami::AgentID agent_id, format_context &ctx) {
        return format_to(ctx.out(), "{}", agent_id.to_string());
    }
};

template<>
struct fmt::formatter<kami::GridCoord2D> : fmt::formatter<std::string> {
    static auto format(const kami::GridCoord2D &coord, format_context &ctx) {
        return format_to(ctx.out(), "{}", coord.to_string());
    }
};

/**
 * A starter agent for a starter model
 */
class BankAgent : public kami::ReporterAgent {
public:
    /**
     * Constructor
     */
    explicit BankAgent(int reserve_percent) : _reserve_percent(reserve_percent) {};

    inline std::unique_ptr<nlohmann::json> collect() override {
        auto ret = std::make_unique<nlohmann::json>();

        (*ret)["reserves"] = _reserves;
        (*ret)["available"] = _available_to_loan;

        return std::move(ret);
    }

    inline kami::AgentID step(std::shared_ptr<kami::ReporterModel> model) override {
        return get_agent_id();
    };

    int bank_balance() {
        _reserves = (_reserve_percent / 100) * _deposits;
        return _available_to_loan = _deposits - (_reserves + _bank_loans);
    }

private:
    double _bank_loans = 0;
    double _reserve_percent = 0;
    double _deposits = 0;
    double _reserves = (_reserve_percent / 100) * _deposits;
    double _available_to_loan = 0;

    friend class PersonAgent;
};

class PersonAgent : public kami::ReporterAgent {
public:
    /**
     * Constructor
     */
    explicit PersonAgent(int wallet, std::shared_ptr<BankAgent> &bank) :
            _wallet(wallet), _bank(bank) {};

    inline std::unique_ptr<nlohmann::json> collect() override {
        auto ret = std::make_unique<nlohmann::json>();

        (*ret)["savings"] = _savings;
        (*ret)["loans"] = _loans;
        (*ret)["wallet"] = _wallet;
        (*ret)["wealth"] = _wealth;

        return std::move(ret);
    }

    /**
     * Execute a single time-step for the agent
     */
    kami::AgentID step(std::shared_ptr<kami::ReporterModel> model) override;

private:
    int _step_counter = 0;
    double _savings = 0;
    double _loans = 0;
    double _wallet = 0;
    double _wealth = 0;
    std::shared_ptr<BankAgent> _bank;

    /**
     * Move the agent to a random location on the world
     */
    std::optional<kami::GridCoord2D> move_agent(std::shared_ptr<kami::ReporterModel> &model);

    std::optional<kami::AgentID> do_business(std::shared_ptr<kami::ReporterModel> &model);

    std::optional<int> balance_books(std::shared_ptr<kami::ReporterModel> &model);

    kami::AgentID deposit_to_savings(double amount);

    kami::AgentID withdraw_from_savings(double amount);

    kami::AgentID repay_a_loan(double amount);

    kami::AgentID take_out_loan(double amount);
};

/**
 * The one-dimensional Boltzmann wealth model
 */
class BankReservesModel : public kami::ReporterModel {
public:
    /**
     * Create an instance of the one-dimensional Boltzmann wealth model.
     *
     * @param[in] number_agents the number of agents to assign to the model.
     * @param[in] length_x the length of the one-dimensional world the agents
     * occupy.
     */
    explicit BankReservesModel(unsigned int agent_count, unsigned int x_size, unsigned int y_size,
                               unsigned int initial_seed, unsigned int max_initial_wealth);

    inline std::unique_ptr<nlohmann::json> collect() override {
        return nullptr;
    }
};

#endif  // BANKRESERVES_H
