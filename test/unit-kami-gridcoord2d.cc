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

#include <kami/grid2d.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(GridCoord2D, DefaultConstructor) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_EQ(gridcoord2d_foo, gridcoord2d_foo);

    EXPECT_NE(gridcoord2d_foo, gridcoord2d_bar);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_baz);
    EXPECT_NE(gridcoord2d_bar, gridcoord2d_baz);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_qux);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_qu2);

}

TEST(GridCoord2D, to_string) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_THAT(gridcoord2d_foo.to_string(), "(0, 0)");
    EXPECT_THAT(gridcoord2d_bar.to_string(), "(1, 1)");
    EXPECT_THAT(gridcoord2d_baz.to_string(), "(-1, -1)");
    EXPECT_THAT(gridcoord2d_qux.to_string(), "(0, 1)");
    EXPECT_THAT(gridcoord2d_qu2.to_string(), "(1, 0)");
}

TEST(GridCoord2D, Equality) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo == gridcoord2d_foo);

    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_bar);
    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_baz);
    EXPECT_FALSE(gridcoord2d_bar == gridcoord2d_baz);
    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_qux);
    EXPECT_FALSE(gridcoord2d_qux == gridcoord2d_qu2);
    EXPECT_FALSE(gridcoord2d_qux == gridcoord2d_qu2);
}

TEST(GridCoord2D, Inequality) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_FALSE(gridcoord2d_foo != gridcoord2d_foo);

    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_qux);
    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_bar);
    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_baz);
    EXPECT_TRUE(gridcoord2d_bar != gridcoord2d_baz);
    EXPECT_TRUE(gridcoord2d_qux != gridcoord2d_qu2);
}

TEST(GridCoord2D, get_x_location) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo.get_x_location() == 0);
    EXPECT_TRUE(gridcoord2d_bar.get_x_location() == 1);
    EXPECT_TRUE(gridcoord2d_baz.get_x_location() == -1);
    EXPECT_FALSE(gridcoord2d_qux.get_x_location() == -1);
    EXPECT_FALSE(gridcoord2d_qu2.get_x_location() == -1);

    EXPECT_TRUE(gridcoord2d_foo.get_x_location() == gridcoord2d_foo.get_x_location());
    EXPECT_TRUE(gridcoord2d_foo.get_x_location() == gridcoord2d_qux.get_x_location());
    EXPECT_TRUE(gridcoord2d_bar.get_x_location() == gridcoord2d_qu2.get_x_location());

    EXPECT_FALSE(gridcoord2d_foo.get_x_location() == gridcoord2d_bar.get_x_location());
    EXPECT_FALSE(gridcoord2d_foo.get_x_location() == gridcoord2d_baz.get_x_location());
    EXPECT_FALSE(gridcoord2d_bar.get_x_location() == gridcoord2d_baz.get_x_location());
    EXPECT_FALSE(gridcoord2d_foo.get_x_location() == gridcoord2d_baz.get_x_location());
    EXPECT_FALSE(gridcoord2d_qux.get_x_location() == gridcoord2d_qu2.get_x_location());
}

TEST(GridCoord2D, get_y_location) {
    const kami::GridCoord2D gridcoord2d_foo(0, 0);
    const kami::GridCoord2D gridcoord2d_bar(1, 1);
    const kami::GridCoord2D gridcoord2d_baz(-1, -1);
    const kami::GridCoord2D gridcoord2d_qux(0, 1);
    const kami::GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo.get_y_location() == 0);
    EXPECT_TRUE(gridcoord2d_bar.get_y_location() == 1);
    EXPECT_TRUE(gridcoord2d_baz.get_y_location() == -1);
    EXPECT_FALSE(gridcoord2d_qux.get_y_location() == -1);
    EXPECT_FALSE(gridcoord2d_qu2.get_y_location() == -1);

    EXPECT_TRUE(gridcoord2d_foo.get_y_location() == gridcoord2d_foo.get_y_location());
    EXPECT_TRUE(gridcoord2d_bar.get_y_location() == gridcoord2d_qux.get_y_location());

    EXPECT_FALSE(gridcoord2d_foo.get_y_location() == gridcoord2d_bar.get_y_location());
    EXPECT_FALSE(gridcoord2d_foo.get_y_location() == gridcoord2d_baz.get_y_location());
    EXPECT_FALSE(gridcoord2d_bar.get_y_location() == gridcoord2d_baz.get_y_location());
    EXPECT_FALSE(gridcoord2d_foo.get_y_location() == gridcoord2d_baz.get_y_location());
    EXPECT_FALSE(gridcoord2d_qux.get_y_location() == gridcoord2d_qu2.get_y_location());
    EXPECT_FALSE(gridcoord2d_bar.get_y_location() == gridcoord2d_qu2.get_y_location());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

