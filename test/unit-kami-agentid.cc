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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;

class AgentIDTest
        : public ::testing::Test {
protected:
    AgentID agent_id_foo;
    AgentID agent_id_bar;
};

TEST_F(AgentIDTest, DefaultConstructor) {
    EXPECT_EQ(agent_id_foo, agent_id_foo);
    EXPECT_NE(agent_id_foo, agent_id_bar);
}

TEST_F(AgentIDTest, to_string) {
    EXPECT_THAT(agent_id_foo.to_string(), testing::MatchesRegex("[0-9]+"));
    EXPECT_THAT(agent_id_bar.to_string(), testing::MatchesRegex("[0-9]+"));
}

TEST_F(AgentIDTest, equality) {
    EXPECT_TRUE(agent_id_foo == agent_id_foo);
    EXPECT_TRUE(agent_id_bar == agent_id_bar);
    EXPECT_FALSE(agent_id_foo == agent_id_bar);
}

TEST_F(AgentIDTest, inequality) {
    EXPECT_TRUE(agent_id_foo != agent_id_bar);
    EXPECT_FALSE(agent_id_bar != agent_id_bar);
}

TEST_F(AgentIDTest, ordering) {
    EXPECT_TRUE(agent_id_foo < agent_id_bar);
    EXPECT_FALSE(agent_id_bar < agent_id_foo);
}

int main(
        int argc,
        char** argv
) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

