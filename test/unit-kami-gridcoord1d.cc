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

TEST(GridCoord1D, DefaultConstructor) {
    const kami::GridCoord1D gridcoord1d_foo(0);
    const kami::GridCoord1D gridcoord1d_bar(1);
    const kami::GridCoord1D gridcoord1d_baz(-1);
    const kami::GridCoord1D gridcoord1d_qux(0);

    EXPECT_EQ(gridcoord1d_foo, gridcoord1d_foo);
    EXPECT_EQ(gridcoord1d_foo, gridcoord1d_qux);

    EXPECT_NE(gridcoord1d_foo, gridcoord1d_bar);
    EXPECT_NE(gridcoord1d_foo, gridcoord1d_baz);
    EXPECT_NE(gridcoord1d_bar, gridcoord1d_baz);
}

TEST(GridCoord1D, to_string) {
    const kami::GridCoord1D gridcoord1d_foo(0);
    const kami::GridCoord1D gridcoord1d_bar(1);
    const kami::GridCoord1D gridcoord1d_baz(-1);

    EXPECT_THAT(gridcoord1d_foo.to_string(), "(0)");
    EXPECT_THAT(gridcoord1d_bar.to_string(), "(1)");
    EXPECT_THAT(gridcoord1d_baz.to_string(), "(-1)");
}

TEST(GridCoord1D, Equality) {
    const kami::GridCoord1D gridcoord1d_foo(0);
    const kami::GridCoord1D gridcoord1d_bar(1);
    const kami::GridCoord1D gridcoord1d_baz(-1);
    const kami::GridCoord1D gridcoord1d_qux(0);

    EXPECT_TRUE(gridcoord1d_foo == gridcoord1d_foo);
    EXPECT_TRUE(gridcoord1d_foo == gridcoord1d_qux);

    EXPECT_FALSE(gridcoord1d_foo == gridcoord1d_bar);
    EXPECT_FALSE(gridcoord1d_foo == gridcoord1d_baz);
    EXPECT_FALSE(gridcoord1d_bar == gridcoord1d_baz);
}

TEST(GridCoord1D, Inequality) {
    const kami::GridCoord1D gridcoord1d_foo(0);
    const kami::GridCoord1D gridcoord1d_bar(1);
    const kami::GridCoord1D gridcoord1d_baz(-1);
    const kami::GridCoord1D gridcoord1d_qux(0);

    EXPECT_FALSE(gridcoord1d_foo != gridcoord1d_foo);
    EXPECT_FALSE(gridcoord1d_foo != gridcoord1d_qux);

    EXPECT_TRUE(gridcoord1d_foo != gridcoord1d_bar);
    EXPECT_TRUE(gridcoord1d_foo != gridcoord1d_baz);
    EXPECT_TRUE(gridcoord1d_bar != gridcoord1d_baz);
}

TEST(GridCoord1D, get_x_location) {
    const kami::GridCoord1D gridcoord1d_foo(0);
    const kami::GridCoord1D gridcoord1d_bar(1);
    const kami::GridCoord1D gridcoord1d_baz(-1);
    const kami::GridCoord1D gridcoord1d_qux(0);

    EXPECT_TRUE(gridcoord1d_foo.get_x_location() == 0);
    EXPECT_TRUE(gridcoord1d_bar.get_x_location() == 1);
    EXPECT_TRUE(gridcoord1d_baz.get_x_location() == -1);

    EXPECT_TRUE(gridcoord1d_foo.get_x_location() == gridcoord1d_foo.get_x_location());
    EXPECT_TRUE(gridcoord1d_foo.get_x_location() == gridcoord1d_qux.get_x_location());

    EXPECT_FALSE(gridcoord1d_foo.get_x_location() == gridcoord1d_bar.get_x_location());
    EXPECT_FALSE(gridcoord1d_foo.get_x_location() == gridcoord1d_baz.get_x_location());
    EXPECT_FALSE(gridcoord1d_bar.get_x_location() == gridcoord1d_baz.get_x_location());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

