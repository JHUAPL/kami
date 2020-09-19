/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MODEL_HPP
#define KAMI_MODEL_HPP

#include <kami/agent.hpp>

namespace kami {

/// An abstract for generic models
class Model {
   public:
    virtual ~Model();

    /// Get a reference to an Agent by AgentID
    virtual Agent *getAgentByID(AgentID) const = 0;

    /// Run the model for a fixed number of steps.
    void run(unsigned int) { return; }

    /// Execute a time-step for the model.
    ///
    /// This function should step the model instance.  Any activities that the
    /// model should perform as part of its time step should be in this function.
    void step() { return; }
};

}  // namespace kami

#endif  // KAMI_MODEL_HPP
