/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_AGENT_HPP
#define KAMI_AGENT_HPP

#include <kami/KAMI_EXPORT.h>

#include <iostream>
#include <string>

namespace kami {

///  \brief A unique identifier for each agent.
///  \details A unqiue identifier is created for each Agent at
///  runtime.  The unique identifier is an unsigned integer that
///  increments monotonically with each new Agent instantiated.
///  AgentIDs are not guaranteed to be unique from session-to-session.
class KAMI_EXPORT AgentID {
   public:
    ///  \brief Constructs a new unique identifier.
    AgentID();

    ///  \brief Convert the identifier to a human readable string.
    std::string toString() const;

    ///  \brief Test if two AgentID instances are equal.
    friend bool operator==(const AgentID &, const AgentID &);

    ///  \brief Test if two AgentID instances are not equal.
    friend bool operator!=(const AgentID &, const AgentID &);

    ///  \brief Test if one AgentID is less than another.
    ///  \details Due to the way AgentID instance are used internally,
    ///  the AgentID must be ordered.  The `<` operator provides 
    ///  basic order sufficient for `std::map`.
    friend bool operator<(const AgentID &, const AgentID &);

    ///  \brief Output an AgentID to the specified output stream.
    friend std::ostream &operator<<(std::ostream &, const AgentID &);

   private:
    static uint64_t idGen;
    uint64_t id;
};

///  \brief A superclass for Agents
///
///  \details All agents should subclass the Agent class.
///  At a minimum, subclasses must implement the `step()`
///  function, to execute a single time step for each agent.
class KAMI_EXPORT Agent {
   public:
    ///  \brief Deconstructor
    virtual ~Agent() = default;

    /// \brief Get the agent's self identification number.
    AgentID getAgentID() const;

    /// \brief Execute a time-step for the agent
    ///
    /// \details This function should step the agent instance.  Any activities that the
    /// agent should perform as part of its time step should be in this function.
    virtual void step();

    friend bool operator==(const Agent &, const Agent &);
    friend bool operator!=(const Agent &, const Agent &);

   private:
    AgentID agentID;
};

///  \brief A class for agents with pre-`step()` and post-`step()` staging.
///
///  \details Staged agents use a two-phase or three-phase step to allow agents to take actions without
///  updating the state of the model before all agents have been allowed to
///  update.
class StagedAgent : public Agent {
   public:
    ///
    StagedAgent();
    virtual ~StagedAgent() = default;

    ///  \brief Initialize a staged time step for the agent
    ///
    ///  \details This method should initialize a time-step, but not actually execute
    ///  any changes.  It should be implemented if a model's schedule expectes
    ///  a staged stepping function wherein all agents step using the same
    ///  state.
    virtual void preStep() = 0;

    ///  \brief Post-step actions the agent
    ///
    ///  \details This method should be called after `step()`.  Any updates or cleanups
    ///  to the agent should occur here that must happen after the step is complete.
    virtual void postStep() = 0;
};

}  // namespace kami

#endif  // KAMI_AGENT_HPP
