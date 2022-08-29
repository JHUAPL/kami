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

#include <memory>
#include <utility>
#include <vector>

#include <kami/agent.h>
#include <kami/population.h>
#include <kami/sequential.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace std;

class TestAgent : public Agent {
public:
    AgentID step(shared_ptr<Model> model) override {
        return get_agent_id();
    }
};

class TestModel : public Model {
public:
    shared_ptr<vector<AgentID>> retval;

    shared_ptr<Model> step() override {
        retval = _sched->step(shared_from_this()).value();
        return shared_from_this();
    }

    shared_ptr<Model> step(unique_ptr<vector<AgentID>> agent_list) {
        retval = _sched->step(shared_from_this(), std::move(agent_list)).value();
        return shared_from_this();
    }
};

class SequentialSchedulerTest : public ::testing::Test {
protected:
    shared_ptr<TestModel> mod = nullptr;

    void SetUp() override {
        mod = make_shared<TestModel>();
        auto pop_foo = make_shared<Population>();
        auto sched_foo = make_shared<SequentialScheduler>();

        // Domain is not required for this test
        static_cast<void>(mod->set_population(pop_foo));
        static_cast<void>(mod->set_scheduler(sched_foo));

        for (auto i = 0; i < 10; i++) {
            auto agent_foo = make_shared<TestAgent>();
            static_cast<void>(pop_foo->add_agent(agent_foo));
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

TEST_F(SequentialSchedulerTest, step_interface1) {
    auto tval = mod->get_population().value()->get_agent_list();
    auto aval = mod->get_population().value()->get_agent_list();
    mod->step(std::move(aval));

    auto rval = mod->retval;

    EXPECT_TRUE(rval);
    EXPECT_EQ(rval->size(), 10);
    EXPECT_EQ(*rval, *tval);
}

TEST_F(SequentialSchedulerTest, step_interface2) {
    auto tval = mod->get_population().value()->get_agent_list();
    auto aval = mod->get_population().value()->get_agent_list();
    mod->step(std::move(aval));

    auto rval = mod->retval;

    EXPECT_TRUE(rval);
    EXPECT_EQ(rval->size(), 10);
    EXPECT_EQ(*rval, *tval);
}

TEST_F(SequentialSchedulerTest, step_10000) {
    // Do it a lot...
    for (auto i = 0; i < 10000; i++) {
        auto tval = mod->get_population().value()->get_agent_list();
        auto aval = mod->get_population().value()->get_agent_list();
        mod->step(std::move(aval));

        auto rval = mod->retval;

        EXPECT_TRUE(rval);
        EXPECT_EQ(rval->size(), 10);
        EXPECT_EQ(*rval, *tval);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

