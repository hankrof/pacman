#include "picture.h"
Picture     Picture::trans(int angle)
{
    Picture    result;
    QTransform tran;
    if(!empty())
    {
        QImage     as1   = AS_1.toImage();
        QImage     as2   = AS_2.toImage();
        QImage     ascg  = AS_CHASED_GHOST.toImage();
        QImage     ascg2 = AS_CHASED_GHOST_2.toImage();
        tran.rotate(angle);
        result.AS_1 = QPixmap::fromImage(as1.transformed(tran));
        result.AS_2 = QPixmap::fromImage(as2.transformed(tran));
        result.AS_CHASED_GHOST =
                QPixmap::fromImage(ascg.transformed(tran));
        result.AS_CHASED_GHOST_2 =
                QPixmap::fromImage(ascg2.transformed(tran));
    }
    return result;
}

Picture Picture::mirror()
{
    Picture    result;
    if(!empty())
    {
        QImage     as1   = AS_1.toImage();
        QImage     as2   = AS_2.toImage();
        QImage     ascg  = AS_CHASED_GHOST.toImage();
        QImage     ascg2 = AS_CHASED_GHOST_2.toImage();
        result.AS_1 = QPixmap::fromImage(as1.mirrored(true,false));
        result.AS_2 = QPixmap::fromImage(as2.mirrored(true,false));
        result.AS_CHASED_GHOST =
                QPixmap::fromImage(ascg);
        result.AS_CHASED_GHOST_2 =
                QPixmap::fromImage(ascg2);
    }
    return result;
}

const QPixmap& Picture::getByState(AnimatedState state) const
{
    switch(state)
    {
    case AnimatedState::AS_1:
        return this->AS_1;
    case AnimatedState::AS_2:
        return this->AS_2;
    case AnimatedState::AS_CHASED_GHOST:
        return this->AS_CHASED_GHOST;
    default:
        return this->AS_1;
    }
}

bool Picture::empty() const
{
    return AS_1.isNull() && AS_2.isNull() && AS_CHASED_GHOST.isNull();
}

PictureFactory::PictureFactory(int blockSize)
{
    loadPicture(blockSize);
}

const QPixmap& PictureFactory::getPixmap(MapUnit mapUnit) const
{
    switch(mapUnit)
    {
    case MU_PATH:
        return path;
    case MU_BLOCK:
        return block;
    case MU_SCORE_DOT:
        return scoreDot;
    case MU_GHOST_DOOR:
        return ghostDoor;
    default:
        return nullPixmap;
    }
}

const QPixmap& PictureFactory::getPixmap(const Character& character) const
{
    switch(character.user())
    {
    case U_Player:
        return player[character.direction()].getByState(character.animatedState());
        break;
    case U_Comptuer:
        return ghost1[character.direction()].getByState(character.animatedState());
        break;
    }
    return nullPixmap;
}
void PictureFactory::loadPicture(int blockSize)
{
    m_blockSize           = blockSize;
    path                  = QPixmap("pic/path.png").scaled(QSize(blockSize,blockSize));
    block                 = QPixmap("pic/block.png").scaled(QSize(blockSize,blockSize));
    scoreDot              = QPixmap("pic/score_dot.png").scaled(QSize(blockSize,blockSize));
    ghostDoor             = QPixmap("pic/ghost_door.png").scaled(QSize(blockSize,blockSize));


    player[LD_Right].AS_1 = QPixmap("pic/pacman_as_1.png").scaled(QSize(blockSize,blockSize));
    player[LD_Right].AS_2 = QPixmap("pic/pacman_as_2.png").scaled(QSize(blockSize,blockSize));
    player[LD_Right].AS_CHASED_GHOST
            = player[LD_Right].AS_1;
    player[LD_Left] = player[LD_Right].trans(180);
    player[LD_Down] = player[LD_Right].trans(90);
    player[LD_Up]   = player[LD_Right].trans(270);


    ghost1[LD_Right].AS_1  = QPixmap("pic/ghost1_as_1.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Right].AS_2  = QPixmap("pic/ghost1_as_2.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Right].AS_CHASED_GHOST
            = QPixmap("pic/ghost_chased.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Right].AS_CHASED_GHOST_2
            = QPixmap("pic/ghost_chased_2.png").scaled(QSize(blockSize,blockSize));

    ghost1[LD_Left ]       = ghost1[LD_Right].mirror();

    ghost1[LD_Down ].AS_1  = QPixmap("pic/ghost1_down_as_1.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Down ].AS_2  = QPixmap("pic/ghost1_down_as_2.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Down ].AS_CHASED_GHOST
            = ghost1[LD_Right].AS_CHASED_GHOST;
    ghost1[LD_Down ].AS_CHASED_GHOST_2
            = ghost1[LD_Right].AS_CHASED_GHOST_2;

    ghost1[LD_Up   ].AS_1  = QPixmap("pic/ghost1_up_as_1.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Up   ].AS_2  = QPixmap("pic/ghost1_up_as_2.png").scaled(QSize(blockSize,blockSize));
    ghost1[LD_Up ].AS_CHASED_GHOST
            = ghost1[LD_Right].AS_CHASED_GHOST;
    ghost1[LD_Up ].AS_CHASED_GHOST_2
            = ghost1[LD_Right].AS_CHASED_GHOST_2;


}

int PictureFactory::blockSize() const
{
    return m_blockSize;
}
