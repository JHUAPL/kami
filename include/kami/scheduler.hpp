/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SCHEDULER_HPP
#define KAMI_SCHEDULER_HPP

#include <kami/agent.hpp>

namespace kami {

///  \brief     Create a Kami scheduler.
///  \details   Schedulers are responsible for executing each time step
///  in the model.  A scheduler will have a collection of agents assigned
///  to it and will execute the step function for each agent based on the
///  type of scheduling implemented.
class Scheduler {
   public:
    /// \brief  Return a new Kami scheduler
    ///
    /// \details    This function should return a new instance of a
    /// scheduler class that implements this trait.
    Scheduler() {}
    virtual ~Scheduler();

    /// Add an Agent to the Scheduler.
    ///
    /// @param agentID The AgentID of the agent to add.
    virtual void addAgent(AgentID agentID) = 0;

    /// Remove an Agent from the Scheduler.
    ///
    /// @param agentID The AgentID of the agent to remove.
    virtual void deleteAgent(AgentID agentID) = 0;

    /// Step the Scheduler.
    ///
    /// A generic step function that executes a single time step.
    virtual void step() = 0;
};

}  // namespace kami

#endif  // KAMI_SCHEDULER_HPP
