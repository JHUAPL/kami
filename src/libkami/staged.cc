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

#include <kami/agent.h>
#include <kami/model.h>
#include <kami/scheduler.h>
#include <kami/sequential.h>
#include <kami/staged.h>

#include <random>
#include <string>

namespace kami {

StagedScheduler::StagedScheduler(Model *model) {
    _step_counter = 0;
    _model = model;
}

StagedScheduler::~StagedScheduler() {}

void StagedScheduler::add_agent(AgentID agent_id) {
    _agent_list.push_back(agent_id);
}

void StagedScheduler::delete_agent(AgentID agent_id) {
    for (auto agent_list_iter = _agent_list.begin();
         agent_list_iter < _agent_list.end(); agent_list_iter++) {
        if (*agent_list_iter == agent_id) {
            _agent_list.erase(agent_list_iter);
            return;
        }
    }
    // ERROR HERE
}

void StagedScheduler::step() {
    _step_counter++;

    for (auto agent_list_iter = _agent_list.begin();
         agent_list_iter < _agent_list.end(); agent_list_iter++) {
        StagedAgent *agent =
            dynamic_cast<StagedAgent *>(_model->getAgentByID(*agent_list_iter));
        if (agent != nullptr) agent->step();
        // ERROR HERE
    }

    for (auto agent_list_iter = _agent_list.begin();
         agent_list_iter < _agent_list.end(); agent_list_iter++) {
        StagedAgent *agent =
            dynamic_cast<StagedAgent *>(_model->getAgentByID(*agent_list_iter));
        if (agent != nullptr) agent->advance();
        // ERROR HERE
    }

    return;
}


}  // namespace kami
