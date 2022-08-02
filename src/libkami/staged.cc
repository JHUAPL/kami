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

#include <memory>
#include <vector>

#include <kami/agent.h>
#include <kami/sequential.h>
#include <kami/staged.h>

namespace kami {

    void StagedScheduler::step() {
        auto agent_list = Scheduler::get_model()->get_population()->get_agent_list();
        this->SequentialScheduler::step(agent_list);
        this->advance(agent_list);
    }

    [[maybe_unused]] void StagedScheduler::advance() {
        this->advance(Scheduler::get_model()->get_population()->get_agent_list());
    }

    void StagedScheduler::advance(const std::shared_ptr<std::vector<AgentID>>& agent_list) {
        for(auto agent_id = agent_list->begin(); agent_id < agent_list->end(); agent_id++) {
            auto agent = std::dynamic_pointer_cast<StagedAgent>(this->Scheduler::get_model()->get_population()->get_agent_by_id(*agent_id));
            if(agent != nullptr) agent->advance(_model);
        }
    }

}  // namespace kami
