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
#include <string>

namespace kami {

uint64_t AgentID::idGen = 1;

AgentID::AgentID() {
    id = idGen++;
}

std::string AgentID::toString() const {
    return std::to_string(id);
}

bool operator==(const AgentID &lhs, const AgentID &rhs) {
    return lhs.id == rhs.id;
}

bool operator!=(const AgentID &lhs, const AgentID &rhs) {
    return !(lhs == rhs);
}

bool operator<(const AgentID &lhs, const AgentID &rhs) {
    return lhs.id < rhs.id;
}

std::ostream &operator<<(std::ostream &lhs, const AgentID &rhs) {
    return lhs << rhs.toString();
}

AgentID Agent::getAgentID() const {
    return agentID;
}


bool operator==(const Agent &lhs, const Agent &rhs) {
    return lhs.agentID == rhs.agentID;
}

bool operator!=(const Agent &lhs, const Agent &rhs) {
    return !(lhs == rhs);
}

void TwoActionAgent::step() {
    stepA();
    stepB();
}

}  // namespace kami
