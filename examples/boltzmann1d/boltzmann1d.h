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
#define BOLTZMANN1D_H

#include <iostream>
#include <map>

#include <kami/agent.h>
#include <kami/kami.h>
#include <kami/multigrid1d.h>
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
     * Execute a single time-step for the agent
     */
    void step() override;

    /**
     * Give the agent a reference copy of the domain it is expected to work in
     */
    static void set_world(kami::MultiGrid1D *world);

    /**
     * Give the agent a reference copy of the model it is expected to work in
     */
    static void set_model(class BoltzmannWealthModel1D *model);

    /**
     * Move the agent to a random location on the world
     */
    void move_agent();

    /**
     * Give money to a random agent
     */
    void give_money();

private:
    static kami::MultiGrid1D *_world;
    static BoltzmannWealthModel1D *_model;
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
    explicit BoltzmannWealthModel1D(unsigned int number_agents = 10, unsigned int length_x = 10);

    /**
     * Destroy the instance
     */
    ~BoltzmannWealthModel1D();

    /**
     * Execute a single time-step for the model.
     */
    void step() override;

    /**
     * Execute a number of time-steps for the model.
     *
     * @param[in] n the number of steps to execute.
     */
    void run(unsigned int n) override;

    /**
     * Get the MoneyAgent instance associated with the given `AgentID`
     *
     * @returns an pointer to the `MoneyAgent` that was requested.
     */
    [[nodiscard]] MoneyAgent1D *get_agent_by_id(kami::AgentID agent_id) const override;

private:
    std::map<kami::AgentID, MoneyAgent1D *> _agent_list;
    kami::RandomScheduler *_sched;
    kami::MultiGrid1D *_world;
    unsigned int _step_count;
};

#endif  // BOLTZMANN1D_H
