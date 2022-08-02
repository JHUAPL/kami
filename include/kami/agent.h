/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#ifndef KAMI_AGENT_H
#define KAMI_AGENT_H

#include <iostream>
#include <memory>
#include <string>

#include <kami/kami.h>
#include <kami/model.h>

namespace kami {

/**
 * @brief A unique identifier for each `Agent`.
 *
 * @details The unique identifier permits ordering to allow `AgentID`s to be used as keys
 * for `std::map`. The unique identifier is unique for the session, however,
 * `AgentID`s are not guaranteed to be unique from session-to-session.
 *
 * @see Agent
 */
    class LIBKAMI_EXPORT AgentID {
    private:
        inline static long long _id_next = 1;

        /**
         * @brief The unique identifier is a `long long`.
         *
         * @details The unique identifier is an unsigned integer that increments
         * monotonically with each new `AgentID` instantiated.  This is
         * substantially faster than other potential identifiers, such
         * as MD5 hashes or UUID objects.
         */
        long long _id;

    public:
        /**
         * @brief Constructs a new unique identifier.
         */
        AgentID() : _id(_id_next++){};

        /**
         * @brief Convert the identifier to a human-readable string.
         *
         * @return a human-readable form of the `AgentID` as `std::string`.
         */
        [[nodiscard]] std::string to_string() const { return std::to_string(_id); }

        /**
         * @brief Test if two `AgentID` instances are equal.
         *
         * @param lhs is the left-hand side of the equality test.
         * @param rhs is the right-hand side of the equality test.
         * @return true is they are equal and false if not.
         */
        friend bool operator==(const AgentID &lhs, const AgentID &rhs);

        /**
         * @brief Test if two `AgentID` instances are not equal.
         *
         * @param lhs is the left-hand side of the equality test.
         * @param rhs is the right-hand side of the equality test.
         * @return true is they are not equal and false if they are.
         */
        friend bool operator!=(const AgentID &lhs, const AgentID &rhs);

        /**
         * @brief Test if one AgentID is less than another.
         *
         * @details Due to the way AgentID instances are used internally,
         * the AgentID must be orderable.  The `<` operator provides a
         * basic ordering sufficient for `std::map`.
         *
         * @param lhs is the left-hand side of the ordering test.
         * @param rhs is the right-hand side of the ordering test.
         * @return true if `lhs` is "less than" `rhs` as determined by the
         * underlying implementation of the `AgentID`.
         */
        friend bool operator<(const AgentID &lhs, const AgentID &rhs);

        /**
         * @brief Output an AgentID to the specified output stream
         *
         * @details The form of the output will be the same as that produced by the
         * `to_string()` member function.
         *
         * @param lhs is the stream to output the `AgentID` to
         * @param rhs is the `AgentID` to output
         * @return the output stream for reuse
         */
        friend std::ostream &operator<<(std::ostream &lhs, const AgentID &rhs);
    };

/**
 * @brief A superclass for all agents.
 *
 * @details All agents should subclass the `Agent` class. At a minimum, subclasses must
 * implement the `step()` function, to execute a single time step for each
 * agent.
 *
 * @see `StagedAgent`
 */
    class LIBKAMI_EXPORT Agent {
    private:
        const AgentID _agent_id;

    public:
        /**
         * @brief Get the `Agent`'s `AgentID`.
         *
         * @return the `AgentID`
         */
        [[nodiscard]] AgentID get_agent_id() const;

        /**
         * @brief Execute a time-step for the agent
         *
         * @details This function should step the agent instance.  Any activities that the
         * agent should perform as part of its time step should be in this function.
         *
         * @param model a reference copy of the model
         */
        virtual AgentID step(std::shared_ptr<Model> model) = 0;

        /**
         * @brief Compare if two `Agent`s are the same `Agent`.
         *
         * @param lhs is the left-hand side of the equality test.
         * @param rhs is the right-hand side of the equality test.
         * @return true is they are equal and false if not.
         *
         * @note This does not compare that two Agent instances are
         * identical.  Accordingly, this can be used to compare two instances
         * of the same Agent at different points in its time stream.
         *
         * Subclasses of Agent may chose to extend this operator to tighten
         * the restrictions on the comparison.
         */
        friend bool operator==(const Agent &lhs, const Agent &rhs);

        /**
         * @brief Compare if two `Agent`s are not the same `Agent`.
         *
         * @param lhs is the left-hand side of the equality test.
         * @param rhs is the right-hand side of the equality test.
         * @return true is they are not equal and false if they are.
         *
         * @note This does not compare that two Agent instances are
         * identical.  Accordingly, this can be used to compare two instances
         * of the same `Agent` at different points in its time stream.
         *
         * Subclasses of `Agent` may chose to extend this operator to tighten
         * the restrictions on the comparison.
         */
        friend bool operator!=(const Agent &lhs, const Agent &rhs);
    };

/**
 * @brief A superclass for all staged agents.
 *
 * @details Staged agents use a two-phase step to allow agents to take actions without
 * updating the state of the model before all agents have been allowed to
 * update.  All work necessary to advance the `StagedAgent` state should take
 * place in the `step()` function.  However, the `StagedAgent` should not actually
 * update the state, and instead save the results for later use.  Finally,
 * during the `advance()` stage, the StagedAgent state should update.
 *
 * `StagedAgents` must implement both the `step()` and `advance()` functions.
 */
    class LIBKAMI_EXPORT StagedAgent : public Agent {
    public:
        /**
         * @brief Post-step advance the agent
         *
         * @details This method should be called after `step()`.  Any updates or cleanups to
         * the agent that must happen for the `StagedAgent` to complete its step must
         * happen here.
         *
         * @param model a reference copy of the model
         *
         */
        virtual AgentID advance(std::shared_ptr<Model> model) = 0;
    };

}  // namespace kami

#endif  // KAMI_AGENT_H
