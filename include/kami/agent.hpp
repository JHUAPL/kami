/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_AGENT_HPP
#define KAMI_AGENT_HPP

#include <iostream>
#include <string>

namespace kami {

///  \brief A unique identifier for each agent.
///  \details A unqiue identifier is created for each Agent at
///  runtime.  The unique identifier is an unsigned integer that
///  increments monotonically with each new Agent instantiated.
///  AgentIDs are not guaranteed to be unique from session-to-session.
class AgentID {
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

class Agent {
   public:
    virtual ~Agent() = default;

    AgentID getAgentID() const;
    virtual void step();

    friend bool operator==(const Agent &, const Agent &);
    friend bool operator!=(const Agent &, const Agent &);

   private:
    AgentID agentID;
};

///  A class for agents with pre-`step()` and post-`step()` staging.
class StagedAgent : public Agent {
   public:
    ///
    StagedAgent();
    virtual ~StagedAgent() = default;

    virtual void preStep() = 0;
    virtual void postStep() = 0;
};

}  // namespace kami

#endif  // KAMI_AGENT_HPP
