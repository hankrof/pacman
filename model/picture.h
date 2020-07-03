#ifndef PICTURE_H
#define PICTURE_H
#include <QPixmap>
#include "character.h"
#include "gamemap.h"
class PictureFactory;
class Picture
{
friend class PictureFactory;
private:
    Picture           trans(int angle);
    Picture           mirror();
    const QPixmap&    getByState(AnimatedState state) const;
    bool              empty() const;
    QPixmap           AS_1;
    QPixmap           AS_2;
    QPixmap           AS_CHASED_GHOST;
    QPixmap           AS_CHASED_GHOST_2;
};

class PictureFactory
{
public:
     PictureFactory(int blockSize = 30);
     const QPixmap& getPixmap(MapUnit mapUnit) const;
     const QPixmap& getPixmap(const Character& character) const;
     void    loadPicture(int blockSize);
     int     blockSize() const;
private:
     int     m_blockSize;
     Picture player[4]; //Up,Down,Left,Right
     Picture ghost1[4];
     QPixmap path;
     QPixmap ghostDoor;
     QPixmap scoreDot;
     QPixmap block;
     QPixmap nullPixmap;
};
#endif // DRAWENGINE

