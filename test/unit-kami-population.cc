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
#include <kami/error.h>
#include <kami/population.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;
using namespace kami::error;
using namespace std;

class TestAgent : public Agent {
private:
    int _x;

public:
    explicit TestAgent(int x) : _x(x) {};

    AgentID step(shared_ptr<Model> model) override {
        return get_agent_id();
    }

    int getval() {
        return _x;
    }
};

TEST(Population, DefaultConstructor) {
    // There is really no way this can go wrong, but
    // we add this check anyway in case of future
    // changes.
    EXPECT_NO_THROW(
            const Population population_foo;
    );
}

TEST(Population, add_agent) {
    Population population_foo;
    auto agent_foo = make_shared<TestAgent>(8675309);
    auto agent_bar = make_shared<TestAgent>(1729);

    {
        auto agent_id_baz = population_foo.add_agent(agent_foo);
        EXPECT_EQ(agent_id_baz, agent_foo->get_agent_id());
    }
    {
        auto agent_id_baz = population_foo.add_agent(agent_bar);
        EXPECT_EQ(agent_id_baz, agent_bar->get_agent_id());
    }
    {
        auto agent_id_baz = population_foo.add_agent(agent_foo);
        EXPECT_EQ(agent_id_baz, agent_foo->get_agent_id());
        auto agent_id_qux = population_foo.add_agent(agent_bar);
        EXPECT_EQ(agent_id_qux, agent_bar->get_agent_id());
    }
}

TEST(Population, get_agent_by_id) {
    auto agent_foo = make_shared<TestAgent>(8675309);
    auto agent_bar = make_shared<TestAgent>(1729);

    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        auto agent_baz_opt = population_foo.get_agent_by_id(agent_foo->get_agent_id());
        EXPECT_TRUE(agent_baz_opt);

        auto agent_baz = dynamic_pointer_cast<TestAgent>(agent_baz_opt);
        EXPECT_EQ(agent_baz->getval(), 8675309);
    }
    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        EXPECT_THROW(auto agent_baz_opt = population_foo.get_agent_by_id(agent_bar->get_agent_id()), AgentNotFound);
    }
    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        static_cast<void>(population_foo.add_agent(agent_bar));

        auto agent_baz_opt = population_foo.get_agent_by_id(agent_foo->get_agent_id());
        EXPECT_TRUE(agent_baz_opt);

        auto agent_baz = dynamic_pointer_cast<TestAgent>(agent_baz_opt);
        EXPECT_EQ(agent_baz->getval(), 8675309);

        auto agent_qux_opt = population_foo.get_agent_by_id(agent_bar->get_agent_id());
        EXPECT_TRUE(agent_qux_opt);

        auto agent_qux = dynamic_pointer_cast<TestAgent>(agent_qux_opt);
        EXPECT_EQ(agent_qux->getval(), 1729);
    }
    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        static_cast<void>(population_foo.add_agent(agent_bar));

        auto agent_qux_opt = population_foo.get_agent_by_id(agent_bar->get_agent_id());
        EXPECT_TRUE(agent_qux_opt);

        auto agent_qux = dynamic_pointer_cast<TestAgent>(agent_qux_opt);
        EXPECT_EQ(agent_qux->getval(), 1729);

        auto agent_baz_opt = population_foo.get_agent_by_id(agent_foo->get_agent_id());
        EXPECT_TRUE(agent_baz_opt);

        auto agent_baz = dynamic_pointer_cast<TestAgent>(agent_baz_opt);
        EXPECT_EQ(agent_baz->getval(), 8675309);
    }
}

TEST(Population, get_agent_list) {
    auto agent_foo = make_shared<TestAgent>(8675309);
    auto agent_bar = make_shared<TestAgent>(1729);
    auto agent_baz = make_shared<TestAgent>(4104);
    auto agent_qux = make_shared<TestAgent>(196);

    {
        Population population_foo;
        auto tval = make_shared<vector<AgentID>>();
        auto rval = population_foo.get_agent_list();

        EXPECT_EQ(*tval, *rval);
    }
    {
        Population population_foo;
        auto tval = make_shared<vector<AgentID>>();
        auto rval = population_foo.get_agent_list();

        tval->push_back(agent_foo->get_agent_id());
        EXPECT_NE(*tval, *rval);
    }
    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        static_cast<void>(population_foo.add_agent(agent_bar));

        auto tval = make_shared<vector<AgentID>>();
        auto uval = make_shared<vector<AgentID>>();
        auto rval = population_foo.get_agent_list();

        tval->push_back(agent_foo->get_agent_id());
        tval->push_back(agent_bar->get_agent_id());
        EXPECT_EQ(*tval, *rval);

        //  Ordering matters
        uval->push_back(agent_bar->get_agent_id());
        uval->push_back(agent_foo->get_agent_id());
        EXPECT_NE(*uval, *rval);
    }
    {
        Population population_foo;
        static_cast<void>(population_foo.add_agent(agent_foo));
        static_cast<void>(population_foo.add_agent(agent_bar));
        static_cast<void>(population_foo.add_agent(agent_baz));
        static_cast<void>(population_foo.add_agent(agent_qux));

        auto tval = make_shared<vector<AgentID>>();
        auto rval = population_foo.get_agent_list();

        tval->push_back(agent_foo->get_agent_id());
        tval->push_back(agent_bar->get_agent_id());
        tval->push_back(agent_baz->get_agent_id());
        tval->push_back(agent_qux->get_agent_id());
        EXPECT_EQ(*tval, *rval);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

