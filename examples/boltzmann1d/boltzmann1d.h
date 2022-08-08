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

#pragma once
#ifndef BOLTZMANN1D_H
//! @cond SuppressGuard
#define BOLTZMANN1D_H
//! @endcond

#include <iostream>
#include <map>
#include <memory>
#include <optional>

#include <kami/agent.h>
#include <kami/kami.h>
#include <kami/multigrid1d.h>
#include <kami/population.h>
#include <kami/random.h>


/**
 * A sample agent for a one-dimensional Boltzmann wealth model
 */
class MoneyAgent1D : public kami::Agent {

public:
    /**
     * Create the agent
     */
    MoneyAgent1D() : _step_counter(0), _agent_wealth(1) {}

    /**
     * Deconstruct the agent
     */
    ~MoneyAgent1D();

    /**
     * Execute a single time-step for the agent
     */
    kami::AgentID step(std::shared_ptr<kami::Model> model) override;

    /**
     * Move the agent to a random location on the world
     */
    kami::GridCoord1D move_agent(std::shared_ptr<kami::Model> model);

    /**
     * Give money to a random agent
     */
    std::optional<kami::AgentID> give_money(std::shared_ptr<kami::Model> model);

private:
    int _step_counter;
    int _agent_wealth;

};

/**
 * The one-dimensional Boltzmann wealth model
 */
class BoltzmannWealthModel1D : public kami::Model {

public:
    /**
     * Create an instance of the one-dimensional Boltzmann wealth model.
     *
     * @param[in] number_agents the number of agents to assign to the model.
     * @param[in] length_x the length of the one-dimensional world the agents
     * occupy.
     */
    explicit BoltzmannWealthModel1D(unsigned int number_agents = 10, unsigned int length_x = 10, unsigned int new_seed = 42);

    /**
     * Execute a single time-step for the model.
     */
    std::shared_ptr<kami::Model> step() override;

    /**
     * Execute a number of time-steps for the model.
     *
     * @param[in] n the number of steps to execute.
     */
    std::shared_ptr<kami::Model> run(unsigned int n) override;

private:
    unsigned int _step_count;

};

#endif  // BOLTZMANN1D_H
