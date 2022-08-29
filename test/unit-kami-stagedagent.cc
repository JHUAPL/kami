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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace std;

class TestAgent : public StagedAgent {
public:
    AgentID advance(shared_ptr<Model> model) override {
        return get_agent_id();
    }

    AgentID step(shared_ptr<Model> model) override {
        return get_agent_id();
    }
};

class TestModel : public Model {
};

class StagedAgentTest : public ::testing::Test {
protected:
    TestAgent agent_foo;
    TestAgent agent_bar;
    shared_ptr<TestModel> model_world = nullptr;

    void SetUp() override {
        model_world = make_shared<TestModel>();
    }
};

TEST(StagedAgent, DefaultConstructor) {
    EXPECT_NO_THROW(
            const TestAgent agent_baz;
            const TestAgent agent_qux;
    );
}

TEST_F(StagedAgentTest, equivalance) {
    EXPECT_EQ(agent_foo, agent_foo);
    EXPECT_NE(agent_foo, agent_bar);
}

TEST_F(StagedAgentTest, get_agent_id) {
    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.get_agent_id());
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.get_agent_id());
}

TEST_F(StagedAgentTest, step) {
    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.step(model_world));
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.step(model_world));
}

TEST_F(StagedAgentTest, advance) {
    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.advance(model_world));
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.advance(model_world));
}

TEST_F(StagedAgentTest, equality) {
    EXPECT_TRUE(agent_foo == agent_foo);
    EXPECT_TRUE(agent_bar == agent_bar);
}

TEST_F(StagedAgentTest, inequality) {
    EXPECT_TRUE(agent_foo != agent_bar);
    EXPECT_FALSE(agent_bar != agent_bar);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

