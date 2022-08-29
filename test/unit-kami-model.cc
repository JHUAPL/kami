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

#include <kami/agent.h>
#include <kami/model.h>
#include <kami/multigrid2d.h>
#include <kami/population.h>
#include <kami/sequential.h>

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
    shared_ptr<Model> step() final {
        return shared_from_this();
    }
};

TEST(Model, DefaultConstructor) {
    // There is really no way this can go wrong, but
    // we add this check anyway in case of future
    // changes.
    EXPECT_NO_THROW(
            const TestModel model_foo
    );
}

TEST(Model, set_population) {
    auto model_foo = make_shared<TestModel>();
    auto pop_foo = make_shared<Population>();

    auto pop_bar = model_foo->set_population(pop_foo);
    EXPECT_EQ(pop_foo, pop_bar);
}

TEST(Model, get_population) {
    auto model_foo = make_shared<TestModel>();
    auto pop_foo = make_shared<Population>();

    auto pop_nul = model_foo->get_population();

    auto pop_bar = model_foo->set_population(pop_foo);
    auto pop_baz = model_foo->get_population();

    EXPECT_TRUE(pop_baz);
    EXPECT_EQ(pop_foo, pop_baz);
    EXPECT_EQ(pop_bar, pop_baz);
}

TEST(Model, set_scheduler) {
    auto model_foo = make_shared<TestModel>();
    auto sched_foo = make_shared<SequentialScheduler>();

    auto sched_bar = model_foo->set_scheduler(sched_foo);
    EXPECT_EQ(sched_foo, sched_bar);
}

TEST(Model, get_scheduler) {
    auto model_foo = make_shared<TestModel>();
    auto sched_foo = make_shared<SequentialScheduler>();

    auto sched_nul = model_foo->get_scheduler();
    EXPECT_FALSE(sched_nul);

    auto sched_bar = model_foo->set_scheduler(sched_foo);
    auto sched_baz = model_foo->get_scheduler();

    EXPECT_TRUE(sched_baz);
    EXPECT_EQ(sched_foo, sched_baz);
    EXPECT_EQ(sched_bar, sched_baz);
}

TEST(Model, set_domain) {
    auto model_foo = make_shared<TestModel>();
    auto grid2_foo = make_shared<MultiGrid2D>(10, 10, true, true);

    auto grid2_bar = model_foo->set_domain(grid2_foo);
    EXPECT_EQ(grid2_foo, grid2_bar);
}

TEST(Model, get_domain) {
    auto model_foo = make_shared<TestModel>();
    auto grid2_foo = make_shared<MultiGrid2D>(10, 10, true, true);

    auto grid2_nul = model_foo->get_domain();
    EXPECT_FALSE(grid2_nul);

    auto grid2_bar = model_foo->set_domain(grid2_foo);
    auto grid2_baz = model_foo->get_domain();

    EXPECT_TRUE(grid2_baz);
    EXPECT_EQ(grid2_foo, grid2_baz);
    EXPECT_EQ(grid2_bar, grid2_baz);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

