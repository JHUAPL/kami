/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_AGENT_HPP
#define KAMI_AGENT_HPP

#include <iostream>
#include <string>

namespace kami {

/**
 * A unique identifier for each agent
 */
class AgentID {
   public:
    /**
     * Create a new unique identifier
     */
    AgentID();

    /**
     * Convert the identifier to a human readable string
     */
    std::string toString() const;

    friend bool operator==(const AgentID &, const AgentID &);
    friend bool operator!=(const AgentID &, const AgentID &);
    friend bool operator<(const AgentID &, const AgentID &);
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
