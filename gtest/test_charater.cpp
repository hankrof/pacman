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

TEST(Character, MovePositionFromOriginalPoint)
{
    Character c;
    c.position() = QPoint(0, 0);
    c.move(QPoint(10, 15));
    ASSERT_EQ(c.position(), QPoint(10, 15));
}

TEST(Character, MovePositionFromMinusPoint)
{
    Character c;
    c.position() = QPoint(-5, -7);
    c.move(QPoint(10, 15));
    ASSERT_EQ(c.position(), QPoint(5, 8));
}

TEST(Character, MovePositionFor10Times)
{
    Character c;
    c.position() = QPoint(-5, -3);
    for(int i = 0; i < 10; i++)
    {
        c.move(QPoint(2, 3));
    }
    ASSERT_EQ(c.position(), QPoint(15, 27));
}
