/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SCHEDULER_HPP
#define KAMI_SCHEDULER_HPP

#include <kami/agent.hpp>

namespace kami {

/// An abstract class for a Scheduler
class Scheduler {
   public:

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
