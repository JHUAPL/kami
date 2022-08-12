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
#include <kami/multigrid1d.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(MultiGrid1D, DefaultConstructor) {
    // There is really no way this can go wrong, but
    // we add this check anyway in case of future
    // changes.
    EXPECT_NO_THROW(
            kami::MultiGrid1D multigrid1d_foo(10, true);
    );
}

TEST(MultiGrid1D, add_agent) {
    kami::MultiGrid1D multigrid1d_foo(10, true);
    const kami::AgentID agent_id_foo, agent_id_bar;
    const kami::GridCoord1D coord2(2), coord3(3);

    {
        auto agent_id_baz = multigrid1d_foo.add_agent(agent_id_foo, coord2);
        EXPECT_TRUE(agent_id_baz);
        EXPECT_EQ(agent_id_baz.value(), agent_id_foo);
    }
    {
        auto agent_id_baz = multigrid1d_foo.add_agent(agent_id_bar, coord2);
        EXPECT_TRUE(agent_id_baz);
        EXPECT_EQ(agent_id_baz.value(), agent_id_bar);
    }
    {
        auto agent_id_baz = multigrid1d_foo.add_agent(agent_id_bar, coord3);
        EXPECT_TRUE(agent_id_baz);
        EXPECT_EQ(agent_id_baz.value(), agent_id_bar);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

