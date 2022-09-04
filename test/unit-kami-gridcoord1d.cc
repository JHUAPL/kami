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

#include <kami/grid1d.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace kami;

class GridCoord1DTest : public ::testing::Test {
protected:
    GridCoord1D gridcoord1d_foo = GridCoord1D(0);
    GridCoord1D gridcoord1d_bar = GridCoord1D(1);
    GridCoord1D gridcoord1d_baz = GridCoord1D(-1);
    GridCoord1D gridcoord1d_qux = GridCoord1D(0);
};

TEST_F(GridCoord1DTest, DefaultConstructor) {
    EXPECT_EQ(gridcoord1d_foo, gridcoord1d_foo);
    EXPECT_EQ(gridcoord1d_foo, gridcoord1d_qux);

    EXPECT_NE(gridcoord1d_foo, gridcoord1d_bar);
    EXPECT_NE(gridcoord1d_foo, gridcoord1d_baz);
    EXPECT_NE(gridcoord1d_bar, gridcoord1d_baz);
}

TEST_F(GridCoord1DTest, to_string) {
    EXPECT_THAT(gridcoord1d_foo.to_string(), "(0)");
    EXPECT_THAT(gridcoord1d_bar.to_string(), "(1)");
    EXPECT_THAT(gridcoord1d_baz.to_string(), "(-1)");
}

TEST_F(GridCoord1DTest, equality) {
    EXPECT_TRUE(gridcoord1d_foo == gridcoord1d_foo);
    EXPECT_TRUE(gridcoord1d_foo == gridcoord1d_qux);

    EXPECT_FALSE(gridcoord1d_foo == gridcoord1d_bar);
    EXPECT_FALSE(gridcoord1d_foo == gridcoord1d_baz);
    EXPECT_FALSE(gridcoord1d_bar == gridcoord1d_baz);
}

TEST_F(GridCoord1DTest, inequality) {
    EXPECT_FALSE(gridcoord1d_foo != gridcoord1d_foo);
    EXPECT_FALSE(gridcoord1d_foo != gridcoord1d_qux);

    EXPECT_TRUE(gridcoord1d_foo != gridcoord1d_bar);
    EXPECT_TRUE(gridcoord1d_foo != gridcoord1d_baz);
    EXPECT_TRUE(gridcoord1d_bar != gridcoord1d_baz);
}

TEST_F(GridCoord1DTest, x) {
    EXPECT_TRUE(gridcoord1d_foo.x() == 0);
    EXPECT_TRUE(gridcoord1d_bar.x() == 1);
    EXPECT_TRUE(gridcoord1d_baz.x() == -1);

    EXPECT_TRUE(gridcoord1d_foo.x() == gridcoord1d_foo.x());
    EXPECT_TRUE(gridcoord1d_foo.x() == gridcoord1d_qux.x());

    EXPECT_FALSE(gridcoord1d_foo.x() == gridcoord1d_bar.x());
    EXPECT_FALSE(gridcoord1d_foo.x() == gridcoord1d_baz.x());
    EXPECT_FALSE(gridcoord1d_bar.x() == gridcoord1d_baz.x());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

