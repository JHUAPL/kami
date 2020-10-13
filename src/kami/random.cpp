/*-
 * TODO FILE HEADER
 */

#include <kami/agent.hpp>
#include <kami/model.hpp>
#include <kami/random.hpp>
#include <kami/scheduler.hpp>
#include <random>
#include <string>

namespace kami {

RandomScheduler::RandomScheduler(Model *m) {
    stepCounter = 0;
    model = m;
}

RandomScheduler::RandomScheduler(Model *m, uint_fast32_t seed) {
    stepCounter = 0;
    model = m;
    rng.seed(seed);
}

RandomScheduler::~RandomScheduler() {}

void RandomScheduler::addAgent(AgentID newAgentID) {
    agentList.push_back(newAgentID);
}

void RandomScheduler::deleteAgent(AgentID oldAgentID) {
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        if (*agentID == oldAgentID) {
            agentList.erase(agentID);
            return;
        }
    }
    // ERROR HERE
}

void RandomScheduler::step() {
    stepCounter++;

    shuffle(agentList.begin(), agentList.end(), rng);
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        Agent *agent = model->getAgentByID(*agentID);
        if (agent != nullptr)
            agent->step();
        // ERROR HERE
    }
}

void TwoActionRandomScheduler::step() {
    stepCounter++;

    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        TwoActionAgent *agent = dynamic_cast<TwoActionAgent *>(model->getAgentByID(*agentID));
        if (agent != nullptr)
            agent->stepA();
        // ERROR HERE
    }
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        TwoActionAgent *agent = dynamic_cast<TwoActionAgent *>(model->getAgentByID(*agentID));
        if (agent != nullptr)
            agent->stepA();
        // ERROR HERE
    }
}

}  // namespace kami
