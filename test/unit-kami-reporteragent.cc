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
#include <kami/reporter.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace std;

class TestAgent : public ReporterAgent {
public:
    AgentID step(shared_ptr<ReporterModel> model) override {
        return get_agent_id();
    }

    std::optional<std::unique_ptr<nlohmann::json>> collect() override {
        auto json_ret_val = std::make_unique<nlohmann::json>();

        (*json_ret_val)["fname"] = "Gus";
        (*json_ret_val)["lname"] = "Fring";

        return json_ret_val;
    }
};

class TestModel : public ReporterModel {
public:
    std::optional<std::unique_ptr<nlohmann::json>> collect() override {
        return std::make_unique<nlohmann::json>();
    }
};

class ReporterAgentTest : public ::testing::Test {
protected:
    TestAgent agent_foo;
    TestAgent agent_bar;
    shared_ptr<TestModel> model_world = nullptr;

    void SetUp() override {
        model_world = make_shared<TestModel>();
    }
};

TEST(ReporterAgent, DefaultConstructor) {
    EXPECT_NO_THROW(
            const TestAgent agent_baz;
            const TestAgent agent_qux;
    );
}

TEST_F(ReporterAgentTest, equivalance) {
    EXPECT_EQ(agent_foo, agent_foo);
    EXPECT_NE(agent_foo, agent_bar);
}

TEST_F(ReporterAgentTest, get_agent_id) {
    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.get_agent_id());
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.get_agent_id());
}

TEST_F(ReporterAgentTest, step) {
    EXPECT_EQ(agent_foo.get_agent_id(), agent_foo.step(model_world));
    EXPECT_NE(agent_bar.get_agent_id(), agent_foo.step(model_world));
}

TEST_F(ReporterAgentTest, collect) {
    EXPECT_EQ(agent_foo.collect().value()->dump(), "{\"fname\":\"Gus\",\"lname\":\"Fring\"}");
    EXPECT_NE(agent_bar.collect().value()->dump(), "{\"fname\":\"Hank\",\"lname\":\"Schrader\"}");
}

TEST_F(ReporterAgentTest, equality) {
    EXPECT_TRUE(agent_foo == agent_foo);
    EXPECT_TRUE(agent_bar == agent_bar);
}

TEST_F(ReporterAgentTest, inequality) {
    EXPECT_TRUE(agent_foo != agent_bar);
    EXPECT_FALSE(agent_bar != agent_bar);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

