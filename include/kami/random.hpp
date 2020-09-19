#pragma once
#ifndef KAMI_RANDOM_HPP
#define KAMI_RANDOM_HPP

#include <algorithm>
#include <kami/agent.hpp>
#include <kami/model.hpp>
#include <kami/scheduler.hpp>
#include <random>
#include <vector>

namespace kami {

class RandomScheduler : public Scheduler {
   public:
    RandomScheduler(Model *);
    virtual ~RandomScheduler();

    void addAgent(AgentID);
    void deleteAgent(AgentID);
    void step();

   private:
    std::vector<AgentID> agentList;
    std::random_device rd;
    std::mt19937 rng{rd()};
    Model *model;
    int stepCounter;
};

};  // namespace kami

#endif  // KAMI_RANDOM_HPP
