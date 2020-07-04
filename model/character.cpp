#include "character.h"
#include <QDebug>

Character::Character()
    : m_pos(QPoint(0, 0))
{
   m_user   = U_Player;
   m_lookAt = LD_Right;
   m_state  = AS_1;
   lastDirection = LD_Right;
}

QPoint& Character::position()
{
    return m_pos;
}

QPoint Character::position() const
{
    return m_pos;
}

User Character::user() const
{
    return m_user;
}

Character& Character::move(int xOffset,int yOffset)
{
    m_pos.setX(m_pos.x() + xOffset);
    m_pos.setY(m_pos.y() + yOffset);
//  m_lookAt = calcDirection(xOffset,yOffset);
    return *this;
}

Character& Character::move(const QPoint &offset)
{
    m_pos = m_pos + offset;
//  m_lookAt = calcDirection(offset.x(),offset.y());
    return *this;
}

LookDirection Character::direction() const
{
    return m_lookAt;
}
Character& Character::setDirection(LookDirection newDirection)
{
    m_lookAt = newDirection;
    return *this;
}

Character& Character::setAnimatedState(AnimatedState newState)
{
    m_state = newState;
    return *this;
}

AnimatedState Character::animatedState() const
{
    return m_state;
}

void Character::countState()
{
    static int c;
    if(c > 2 && m_state == AS_1)
    {
        m_state = AS_2;
        c = 0;
    }
    else if(c > 2 && m_state == AS_2)
    {
        m_state = AS_1;
        c = 0;
    }
    c++;
}

LookDirection Character::calcDirection(const QPoint &Offset)
{
    if(Offset.x() > 0)
        return lastDirection = LD_Right;
    else if(Offset.x() < 0)
        return lastDirection = LD_Left;
    else if(Offset.y() > 0)
        return lastDirection = LD_Down;
    else if(Offset.y() < 0)
        return lastDirection = LD_Up;
    else
        return lastDirection;
}


LookDirection Character::calcDirection(int xOffset,int yOffset)
{
    if(xOffset > 0)
        return lastDirection = LD_Right;
    else if(xOffset < 0)
        return lastDirection = LD_Left;
    else if(yOffset > 0)
        return lastDirection = LD_Down;
    else if(yOffset < 0)
        return lastDirection = LD_Up;
    else
        return lastDirection;
}
