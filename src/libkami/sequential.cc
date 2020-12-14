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
#include <kami/sequential.h>
#include <kami/scheduler.h>
#include <random>
#include <string>

namespace kami {

SequentialScheduler::SequentialScheduler(Model *newModel) {
    stepCounter = 0;
    model = newModel;
}

void SequentialScheduler::addAgent(AgentID newAgentID) {
    agentList.push_back(newAgentID);
}

void SequentialScheduler::deleteAgent(AgentID oldAgentID) {
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        if (*agentID == oldAgentID) {
            agentList.erase(agentID);
            return;
        }
    }
    // ERROR HERE
}

void SequentialScheduler::step() {
    stepCounter++;

    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        Agent *agent = model->getAgentByID(*agentID);
        if (agent != nullptr)
            agent->step();
        // ERROR HERE
    }
}

}  // namespace kami
