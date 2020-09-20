#pragma once
#ifndef KAMI_RANDOM_HPP
#define KAMI_RANDOM_HPP

#include <algorithm>
#include <kami/kami.hpp>
#include <random>
#include <vector>

namespace kami {

///  \brief     Will execute all agent steps in a random order.
///  \details   A random scheduler will iterate over the agents assigned 
///  to the scheduler and call their `step()` function in a random order. 
///  That order should be different for each subsequent call to `step()`, 
///  but is not gauranteed not to repeat.
///  \pre       First create a Model for the scheduler to live in.
class RandomScheduler : public Scheduler {
   public:
    ///  \brief Constructor.  
    ///  \details   The Model parameter is used by the scheduler to get 
    ///  access to an Agent.  The Model is presumed to maintain a master
    ///  list of all Agents in the Model and the Model can be queried for
    ///  a reference to any particular Agent at `step()` time.
    RandomScheduler(Model *);

    ///  A deconstructor.
    virtual ~RandomScheduler();

    ///  \brief Add an agent to the scheduler.
    ///  \details   The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function adds a new Agent to the list.
    void addAgent(AgentID);

    ///  \brief Remove an agent from the scheduler.
    ///  \details The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function removes an Agent from the list.
    void deleteAgent(AgentID);

    ///  \brief Execute a single time step.
    ///  \details   This method will randomize the list of Agents in the 
    ///  scheduler's internal queue and then execute the `Agent::step()` 
    ///  method for every Agent assigned to this scheduler in the 
    ///  randomized order.
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
