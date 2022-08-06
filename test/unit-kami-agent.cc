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

#include <gtest/gtest.h>

class TestAgent : public kami::Agent {
public:
    kami::AgentID step(std::shared_ptr<kami::Model> model) override {
        return get_agent_id();
    }
};

class TestModel : public kami::Model {
public:
    std::shared_ptr<kami::Model> step() override {
        return shared_from_this();
    }

    std::shared_ptr<kami::Model> run(unsigned int) override {
        return shared_from_this();
    }
};

TEST(Agent, DefaultConstructor) {
    const TestAgent agent_foo;
    const TestAgent agent_bar;

    EXPECT_EQ(agent_foo, agent_foo);
    EXPECT_NE(agent_foo, agent_bar);
}

TEST(Agent, get_agent_id) {
    const TestAgent agent_foo;
    const TestAgent agent_bar;

    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.get_agent_id());
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.get_agent_id());
}

TEST(Agent, step) {
    TestAgent agent_foo;
    TestAgent agent_bar;
    auto model_world = std::make_shared<TestModel>();

    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.step(model_world));
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.step(model_world));
}

TEST(Agent, Equality) {
    const TestAgent agent_foo;
    const TestAgent agent_bar;

    EXPECT_TRUE(agent_foo == agent_foo);
    EXPECT_TRUE(agent_bar == agent_bar);
}

TEST(Agent, Inequality) {
    const TestAgent agent_foo;
    const TestAgent agent_bar;

    EXPECT_TRUE(agent_foo != agent_bar);
    EXPECT_FALSE(agent_bar != agent_bar);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

