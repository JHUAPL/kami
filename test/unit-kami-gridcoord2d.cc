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

using namespace kami;

class GridCoord2DTest
        : public ::testing::Test {
protected:
    GridCoord2D gridcoord2d_foo = GridCoord2D(0, 0);
    GridCoord2D gridcoord2d_bar = GridCoord2D(1, 1);
    GridCoord2D gridcoord2d_baz = GridCoord2D(-1, -1);
    GridCoord2D gridcoord2d_qux = GridCoord2D(0, 1);
    GridCoord2D gridcoord2d_qu2 = GridCoord2D(1, 0);
};

TEST_F(GridCoord2DTest, DefaultConstructor) {
    EXPECT_EQ(gridcoord2d_foo, gridcoord2d_foo);

    EXPECT_NE(gridcoord2d_foo, gridcoord2d_bar);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_baz);
    EXPECT_NE(gridcoord2d_bar, gridcoord2d_baz);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_qux);
    EXPECT_NE(gridcoord2d_foo, gridcoord2d_qu2);

}

TEST_F(GridCoord2DTest, to_string) {
    const GridCoord2D gridcoord2d_foo(0, 0);
    const GridCoord2D gridcoord2d_bar(1, 1);
    const GridCoord2D gridcoord2d_baz(-1, -1);
    const GridCoord2D gridcoord2d_qux(0, 1);
    const GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_THAT(gridcoord2d_foo.to_string(), "(0, 0)");
    EXPECT_THAT(gridcoord2d_bar.to_string(), "(1, 1)");
    EXPECT_THAT(gridcoord2d_baz.to_string(), "(-1, -1)");
    EXPECT_THAT(gridcoord2d_qux.to_string(), "(0, 1)");
    EXPECT_THAT(gridcoord2d_qu2.to_string(), "(1, 0)");
}

TEST_F(GridCoord2DTest, Equality) {
    const GridCoord2D gridcoord2d_foo(0, 0);
    const GridCoord2D gridcoord2d_bar(1, 1);
    const GridCoord2D gridcoord2d_baz(-1, -1);
    const GridCoord2D gridcoord2d_qux(0, 1);
    const GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo == gridcoord2d_foo);

    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_bar);
    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_baz);
    EXPECT_FALSE(gridcoord2d_bar == gridcoord2d_baz);
    EXPECT_FALSE(gridcoord2d_foo == gridcoord2d_qux);
    EXPECT_FALSE(gridcoord2d_qux == gridcoord2d_qu2);
    EXPECT_FALSE(gridcoord2d_qux == gridcoord2d_qu2);
}

TEST_F(GridCoord2DTest, Inequality) {
    const GridCoord2D gridcoord2d_foo(0, 0);
    const GridCoord2D gridcoord2d_bar(1, 1);
    const GridCoord2D gridcoord2d_baz(-1, -1);
    const GridCoord2D gridcoord2d_qux(0, 1);
    const GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_FALSE(gridcoord2d_foo != gridcoord2d_foo);

    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_qux);
    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_bar);
    EXPECT_TRUE(gridcoord2d_foo != gridcoord2d_baz);
    EXPECT_TRUE(gridcoord2d_bar != gridcoord2d_baz);
    EXPECT_TRUE(gridcoord2d_qux != gridcoord2d_qu2);
}

TEST_F(GridCoord2DTest, x) {
    const GridCoord2D gridcoord2d_foo(0, 0);
    const GridCoord2D gridcoord2d_bar(1, 1);
    const GridCoord2D gridcoord2d_baz(-1, -1);
    const GridCoord2D gridcoord2d_qux(0, 1);
    const GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo.x() == 0);
    EXPECT_TRUE(gridcoord2d_bar.x() == 1);
    EXPECT_TRUE(gridcoord2d_baz.x() == -1);
    EXPECT_FALSE(gridcoord2d_qux.x() == -1);
    EXPECT_FALSE(gridcoord2d_qu2.x() == -1);

    EXPECT_TRUE(gridcoord2d_foo.x() == gridcoord2d_foo.x());
    EXPECT_TRUE(gridcoord2d_foo.x() == gridcoord2d_qux.x());
    EXPECT_TRUE(gridcoord2d_bar.x() == gridcoord2d_qu2.x());

    EXPECT_FALSE(gridcoord2d_foo.x() == gridcoord2d_bar.x());
    EXPECT_FALSE(gridcoord2d_foo.x() == gridcoord2d_baz.x());
    EXPECT_FALSE(gridcoord2d_bar.x() == gridcoord2d_baz.x());
    EXPECT_FALSE(gridcoord2d_foo.x() == gridcoord2d_baz.x());
    EXPECT_FALSE(gridcoord2d_qux.x() == gridcoord2d_qu2.x());
}

TEST_F(GridCoord2DTest, y) {
    const GridCoord2D gridcoord2d_foo(0, 0);
    const GridCoord2D gridcoord2d_bar(1, 1);
    const GridCoord2D gridcoord2d_baz(-1, -1);
    const GridCoord2D gridcoord2d_qux(0, 1);
    const GridCoord2D gridcoord2d_qu2(1, 0);

    EXPECT_TRUE(gridcoord2d_foo.y() == 0);
    EXPECT_TRUE(gridcoord2d_bar.y() == 1);
    EXPECT_TRUE(gridcoord2d_baz.y() == -1);
    EXPECT_FALSE(gridcoord2d_qux.y() == -1);
    EXPECT_FALSE(gridcoord2d_qu2.y() == -1);

    EXPECT_TRUE(gridcoord2d_foo.y() == gridcoord2d_foo.y());
    EXPECT_TRUE(gridcoord2d_bar.y() == gridcoord2d_qux.y());

    EXPECT_FALSE(gridcoord2d_foo.y() == gridcoord2d_bar.y());
    EXPECT_FALSE(gridcoord2d_foo.y() == gridcoord2d_baz.y());
    EXPECT_FALSE(gridcoord2d_bar.y() == gridcoord2d_baz.y());
    EXPECT_FALSE(gridcoord2d_foo.y() == gridcoord2d_baz.y());
    EXPECT_FALSE(gridcoord2d_qux.y() == gridcoord2d_qu2.y());
    EXPECT_FALSE(gridcoord2d_bar.y() == gridcoord2d_qu2.y());
}

int main(
        int argc,
        char** argv
) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
