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

#include <algorithm>
#include <iterator>
#include <set>
#include <unordered_set>

#include <kami/agent.h>
#include <kami/error.h>
#include <kami/sologrid1d.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace kami::error;
using namespace std;

TEST(SoloGrid1D, DefaultConstructor) {
    // There is really no way this can go wrong, but
    // we add this check anyway in case of future
    // changes.
    EXPECT_NO_THROW(
            SoloGrid1D sologrid1d_foo(10, true);
    );
}

TEST(SoloGrid1D, add_agent) {
    SoloGrid1D sologrid1d_foo(10, true);
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord2(2), coord3(3);

    {
        auto agent_id_baz = sologrid1d_foo.add_agent(agent_id_foo, coord2);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.add_agent(agent_id_bar, coord2), LocationUnavailable);
    }
    {
        auto agent_id_baz = sologrid1d_foo.add_agent(agent_id_bar, coord3);
        EXPECT_EQ(agent_id_baz, agent_id_bar);
    }
}

TEST(SoloGrid1D, delete_agent) {
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord2(2), coord3(3);

    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_bar), AgentNotFound);
    }

    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo, coord2);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo, coord2);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_bar, coord2), AgentNotFound);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo, coord3), AgentNotFound);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_foo, coord3), AgentNotFound);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.delete_agent(agent_id_bar, coord3), AgentNotFound);
    }
}

TEST(SoloGrid1D, is_location_valid) {
    SoloGrid1D sologrid1d_foo(10, true);
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coordm1(-1), coord0(0), coord2(2), coord3(3), coord10(10), coord100(100);

    {
        EXPECT_TRUE(sologrid1d_foo.is_location_valid(coord0));
        EXPECT_TRUE(sologrid1d_foo.is_location_valid(coord2));
        EXPECT_TRUE(sologrid1d_foo.is_location_valid(coord2));

        EXPECT_FALSE(sologrid1d_foo.is_location_valid(coordm1));
        EXPECT_FALSE(sologrid1d_foo.is_location_valid(coord10));
        EXPECT_FALSE(sologrid1d_foo.is_location_valid(coord100));
    }
}

TEST(SoloGrid1D, is_location_empty) {
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord2(2), coord3(3);

    {
        SoloGrid1D sologrid1d_foo(10, true);

        EXPECT_TRUE(sologrid1d_foo.is_location_empty(coord2));
        EXPECT_TRUE(sologrid1d_foo.is_location_empty(coord3));
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_FALSE(sologrid1d_foo.is_location_empty(coord2));
        EXPECT_TRUE(sologrid1d_foo.is_location_empty(coord3));
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        EXPECT_FALSE(sologrid1d_foo.is_location_empty(coord2));
        EXPECT_TRUE(sologrid1d_foo.is_location_empty(coord3));
    }
}

TEST(SoloGrid1D, move_agent) {
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord2(2), coord3(3), coord7(7), coord10(10);

    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        auto agent_id_baz = sologrid1d_foo.move_agent(agent_id_foo, coord7);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(auto agent_id_baz = sologrid1d_foo.move_agent(agent_id_foo, coord10), InvalidCoordinates);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        auto agent_id_baz = sologrid1d_foo.move_agent(agent_id_foo, coord2);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord2)), LocationUnavailable);
        auto agent_id_baz = sologrid1d_foo.move_agent(agent_id_foo, coord7);
        EXPECT_EQ(agent_id_baz, agent_id_foo);
    }
}

TEST(SoloGrid1D, get_neighborhood) {
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord0(0), coord1(1), coord2(2), coord3(3), coord9(9);

    {
        SoloGrid1D sologrid1d_foo(10, true);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord9 });
        auto rval = sologrid1d_foo.get_neighborhood(coord0, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(coord1, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1 });
        auto rval = sologrid1d_foo.get_neighborhood(coord0, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(coord1, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        auto tval = unordered_set < GridCoord1D > ({ coord1, coord9 });
        auto rval = sologrid1d_foo.get_neighborhood(coord0, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(coord1, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);

        auto tval = unordered_set < GridCoord1D > ({ coord1 });
        auto rval = sologrid1d_foo.get_neighborhood(coord0, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(coord1, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord9 });
        EXPECT_THROW(auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, true), AgentNotFound);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        sologrid1d_foo.add_agent(agent_id_foo, coord0);
        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord9 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        sologrid1d_foo.add_agent(agent_id_foo, coord1);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);
        sologrid1d_foo.add_agent(agent_id_foo, coord0);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);
        sologrid1d_foo.add_agent(agent_id_foo, coord1);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord1, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, true);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        sologrid1d_foo.add_agent(agent_id_foo, coord0);

        auto tval = unordered_set < GridCoord1D > ({ coord1, coord9 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        sologrid1d_foo.add_agent(agent_id_foo, coord1);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);
        sologrid1d_foo.add_agent(agent_id_foo, coord0);

        auto tval = unordered_set < GridCoord1D > ({ coord1 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, false);

        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, false);
        sologrid1d_foo.add_agent(agent_id_foo, coord1);

        auto tval = unordered_set < GridCoord1D > ({ coord0, coord2 });
        auto rval = sologrid1d_foo.get_neighborhood(agent_id_foo, false);

        EXPECT_EQ(tval, *rval);
    }
}

TEST(SoloGrid1D, get_location_by_agent) {
    const AgentID agent_id_foo, agent_id_bar;
    const GridCoord1D coord2(2), coord3(3);

    {
        SoloGrid1D sologrid1d_foo(10, true);

        EXPECT_THROW(auto loc1 = sologrid1d_foo.get_location_by_agent(agent_id_foo), AgentNotFound);
        EXPECT_THROW(auto loc2 = sologrid1d_foo.get_location_by_agent(agent_id_bar), AgentNotFound);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord2));
        auto local = sologrid1d_foo.get_location_by_agent(agent_id_foo);
        EXPECT_EQ(local, coord2);
        EXPECT_THROW(auto loc = sologrid1d_foo.get_location_by_agent(agent_id_bar), AgentNotFound);
    }
}

TEST(SoloGrid1D, get_location_contents) {
    const AgentID agent_id_foo, agent_id_bar, agent_id_baz;
    const GridCoord1D coord0(0), coord1(1), coord9(9), coord10(10);

    {
        SoloGrid1D sologrid1d_foo(10, true);
        EXPECT_THROW(auto agent_list_foo = sologrid1d_foo.get_location_contents(coord10), LocationUnavailable);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);

        auto agent_list_foo = sologrid1d_foo.get_location_contents(coord1);

        EXPECT_TRUE(agent_list_foo);
        EXPECT_TRUE(agent_list_foo->empty());
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord1));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord1)), LocationUnavailable);
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_baz, coord1)), LocationUnavailable);

        auto tval = set < AgentID > ({ agent_id_foo });
        auto rval = sologrid1d_foo.get_location_contents(coord1);

        EXPECT_TRUE(rval);
        EXPECT_EQ(tval, *rval);
    }
    {
        SoloGrid1D sologrid1d_foo(10, true);
        static_cast<void>(sologrid1d_foo.add_agent(agent_id_foo, coord1));
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_bar, coord1)), LocationUnavailable);
        EXPECT_THROW(static_cast<void>(sologrid1d_foo.add_agent(agent_id_baz, coord1)), LocationUnavailable);

        auto tval = set < AgentID > ({ agent_id_foo });
        auto rval = sologrid1d_foo.get_location_contents(coord1);

        EXPECT_TRUE(rval);
        EXPECT_EQ(tval, *rval);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

