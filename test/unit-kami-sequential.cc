/*-
 * Copyright (c) 2022 The Johns Hopkins University Applied Physics
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
#include <kami/population.h>
#include <kami/sequential.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace std;

class TestAgent : public Agent {
public:
    AgentID step(std::shared_ptr<Model> model) override {
        return get_agent_id();
    }
};

class TestModel : public Model {
public:
    std::optional<std::shared_ptr<std::vector<AgentID>>> step() {
        return _sched->step(shared_from_this());
    }
};

class SequentialSchedulerTest : public ::testing::Test {
protected:
    std::shared_ptr<TestModel> mod = nullptr;

    void SetUp() override {
        mod = std::make_shared<TestModel>();
        auto popul_foo = std::make_shared<Population>();
        auto sched_foo = std::make_shared<SequentialScheduler>();

        // Domain is not required for this test
        static_cast<void>(mod->set_population(popul_foo));
        static_cast<void>(mod->set_scheduler(sched_foo));

        for (auto i = 0; i < 10; i++) {
            auto agent_foo = std::make_shared<TestAgent>();
            static_cast<void>(popul_foo->add_agent(agent_foo));
        }
    }
};

TEST(SequentialScheduler, DefaultConstructor) {
    // There is really no way this can go wrong, but
    // we add this check anyway in case of future
    // changes.
    EXPECT_NO_THROW(
            const SequentialScheduler sched_foo;
    );
}

TEST_F(SequentialSchedulerTest, step) {
    auto tval = mod->get_population().value()->get_agent_list();
    auto rval = mod->step();

    EXPECT_TRUE(rval);
    EXPECT_EQ(rval.value()->size(), 10);
    EXPECT_EQ(*rval.value(), *tval);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

