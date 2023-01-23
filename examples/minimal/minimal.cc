/*-
 * Copyright (c) 2023 The Johns Hopkins University Applied Physics
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

#include <list>
#include <map>
#include <memory>

#include <kami/agent.h>
#include <kami/kami.h>
#include <kami/model.h>
#include <kami/population.h>
#include <kami/sequential.h>

class MinimalAgent
        : public kami::Agent {
public:
    kami::AgentID step(std::shared_ptr<kami::Model> model) override {
        return this->get_agent_id();
    }
};

class MinimalModel
        : public kami::Model {
public:
    MinimalModel() {
        auto sched = std::make_shared<kami::SequentialScheduler>();
        set_scheduler(sched);

        auto pop = std::make_shared<kami::Population>();
        set_population(pop);

        for (auto i = 0; i < 10; i++) {
            auto new_agent = std::make_shared<MinimalAgent>();
            pop->add_agent(new_agent);
        }
    }
};

int main() {
    auto model = std::make_shared<MinimalModel>();

    for (int i = 0; i < 10; i++)
        model->step();

    return 0;
}
