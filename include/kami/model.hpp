/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MODEL_HPP
#define KAMI_MODEL_HPP

#include <kami/agent.hpp>

namespace kami {

/// An abstract for generic models
class KAMI_EXPORT Model {
   public:
    /// Destructor.
    virtual ~Model();

    /// Get a reference to an Agent by AgentID
    virtual Agent *getAgentByID(AgentID) const = 0;

    /// Run the model for a fixed number of steps.
    virtual void run(unsigned int) = 0;

    /// Execute a time-step for the model.
    ///
    /// This function should step the model instance.  Any activities that the
    /// model should perform as part of its time step should be in this function.
    virtual void step() = 0;
};

}  // namespace kami

#endif  // KAMI_MODEL_HPP
