#include <gtest/gtest.h>
#include <QPoint>
#include <memory>
#include "character.h"
TEST(Character, Ctor)
{
    Character c;
    ASSERT_EQ(c.position().x(), 0);
    ASSERT_EQ(c.position().y(), 0);
}

TEST(Character, Position1)
{
    Character c;
    c.position() = QPoint(30, 35);
    ASSERT_EQ(c.position().x(), 30);
    ASSERT_EQ(c.position().y(), 35);
}

TEST(Character, Position2)
{
    Character c;
    c.position() = QPoint(-1, -5);
    ASSERT_EQ(c.position().x(), -1);
    ASSERT_EQ(c.position().y(), -5);
    c.position().setX(0);
    ASSERT_EQ(c.position().x(), 0);
    ASSERT_EQ(c.position().y(), -5);
    c.position().setY(0);
    ASSERT_EQ(c.position().y(), 0);
    ASSERT_EQ(c.position().y(), 0);
}

