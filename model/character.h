#ifndef CHARACTER
#define CHARACTER
#include <QMainWindow>

typedef enum
{
    LD_Up,
    LD_Down,
    LD_Left,
    LD_Right
}LookDirection;

typedef enum
{
    AS_1,
    AS_2,
    AS_CHASED_GHOST
}AnimatedState;

typedef enum
{
    U_Player,
    U_Comptuer
}User;

/* This could be a user or computer */
class Character
{
public:
    Character();
    QPoint&                     position();
    QPoint                      position() const;
    User                        user() const;
    Character&                  move(int xOffset,int yOffset);
    Character&                  move(const QPoint &offset);
    LookDirection               direction() const;
    Character&                  setDirection(LookDirection newDirection);
    Character&                  setAnimatedState(AnimatedState newState);
    AnimatedState               animatedState() const;
    void                        countState();
    LookDirection               calcDirection(const QPoint& offset);
    LookDirection               calcDirection(int xOffset,int yOffset);
private:

    AnimatedState               m_state;
    QPoint                      m_pos;
    User                        m_user;
    LookDirection               m_lookAt;
    LookDirection               lastDirection;
};

#endif //CHARACTER_H

