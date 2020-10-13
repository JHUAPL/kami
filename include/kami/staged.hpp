#pragma once
#ifndef KAMI_STAGED_HPP
#define KAMI_STAGED_HPP

#include <algorithm>
#include <kami/KAMI_EXPORT.hpp>
#include <kami/agent.hpp>
#include <kami/model.hpp>
#include <kami/scheduler.hpp>
#include <vector>

namespace kami {

///  \brief     Will execute all agent steps in a sequential order.
///  \details   A sequential scheduler will iterate over the agents assigned 
///  to the scheduler and call their `step()` function in a sequential order. 
///  That order is preserved between calls to `step()` but may be modified by
///  `addAgent()` or `deleteAgent()`.
///  \pre       First create a Model for the scheduler to live in.
class KAMI_EXPORT StagedScheduler : public Scheduler {
   public:
    ///  \brief Constructor.  
    ///  \details   The Model parameter is used by the scheduler to get 
    ///  access to an Agent.  The Model is presumed to maintain a master
    ///  list of all Agents in the Model and the Model can be queried for
    ///  a reference to any particular Agent at `step()` time.
    StagedScheduler(Model *);

    ///  A deconstructor.
    virtual ~StagedScheduler();

    ///  \brief Add an agent to the scheduler.
    ///  \details   The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function adds a new Agent to the list.
    void addAgent(AgentID);

    ///  \brief Remove an agent from the scheduler.
    ///  \details The scheduler maintains a list of all AgentIDs currently
    ///  assigned.  This function removes an Agent from the list.
    void deleteAgent(AgentID);

    ///  \brief Execute a single time step.
    ///  \details   This method will step through the list of Agents in the
    ///  scheduler's internal queue and then execute the `Agent::preStep()`
    ///  method for every Agent assigned to this scheduler in the order
    ///  assigned.  Next, it will execute the `Agent::step()` method for
    ///  each Agent in the same order.  Finally, it will execute the
    ///  `Agent::postStep()` method for each Agent in the same order.
    void step();

   private:
    std::vector<AgentID> agentList;
    Model *model;
    int stepCounter;
};

};  // namespace kami

#endif  // KAMI_STAGED_HPP
