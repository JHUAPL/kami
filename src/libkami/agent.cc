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

#include <kami/agent.h>

#include <iostream>
#include <string>

namespace kami {

    bool operator==(const AgentID &lhs, const AgentID &rhs) {
        return lhs._id == rhs._id;
    }

    bool operator!=(const AgentID &lhs, const AgentID &rhs) {
        return !(lhs == rhs);
    }

    bool operator<(const AgentID &lhs, const AgentID &rhs) {
        return lhs._id < rhs._id;
    }

    std::ostream &operator<<(std::ostream &lhs, const AgentID &rhs) {
        return lhs << rhs.to_string();
    }

    AgentID Agent::get_agent_id() const { return this->_agent_id; }

    bool operator==(const Agent &lhs, const Agent &rhs) {
        return lhs._agent_id == rhs._agent_id;
    }

    bool operator!=(const Agent &lhs, const Agent &rhs) { return !(lhs == rhs); }

    [[maybe_unused]] std::shared_ptr<Model> Agent::get_model() {
        return(_model);
    }

    [[maybe_unused]] void Agent::set_model(std::shared_ptr<Model> model) {
        _model = std::move(model);
    }

}  // namespace kami
