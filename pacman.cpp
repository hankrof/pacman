#include "pacman.h"
#include <QDebug>
#include <ctime>
#include <QSize>
#include <cmath>

CPacManGame::CPacManGame(int width,int height,int mapRows,int mapCols,int blockSize)
    : player(U_Player,30,30), collider(&map)
{
    setWindowSize(width,height);
    setPictureSize(blockSize);
    setMapSize(mapRows,mapCols);
    map.open("map.txt");
}

CPacManGame& CPacManGame::setPictureSize(int newBlockSize)
{
    factory.loadPicture(newBlockSize);
    return *this;
}

CPacManGame& CPacManGame::setWindowSize(int width,int height)
{
    size = QSize(width,height);
    return *this;
}

CPacManGame& CPacManGame::openMap(QString filename)
{
    map.open(filename);
    return *this;
}

CPacManGame& CPacManGame::setMapSize(int rows,int cols)
{
    map.allocate(rows,cols);
    return *this;
}

void CPacManGame::movePlayer(int xOffset,int yOffset)
{
    movePlayer(QPoint(xOffset,yOffset));
}

void CPacManGame::movePlayer(const QPoint &offset)
{
    bool moveFlag = false;
    int blockSize = factory.blockSize();
    if(offset.x() == 0 && offset.y() == 0)
        return;
    player.setDirection(player.calcDirection(offset));
    if(collider.collide(blockSize,player.pos()+offset) == nullptr)
    {
        moveFlag = true;
        player.move(offset);
    }
    else //try smoothly move
    {
        int xldiff = abs(player.x() / blockSize * blockSize
                        - player.x());
        int xrdiff = abs(ceil((double)player.x() / blockSize) * blockSize
                        - player.x());
        int yudiff = abs(ceil((double)player.y() / blockSize) * blockSize
                        - player.y());
        int yddiff = abs(player.y() / blockSize * blockSize
                        - player.y());
        //move up smoothly
        if(xldiff < 15 && offset.y() < 0)
        {
            QPoint p;
            p.setX(player.x() / blockSize * blockSize);
            p.setY(player.y() + offset.y());
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        else if(xrdiff < 15 && offset.y() < 0)
        {
            QPoint p;
            p.setX(ceil((double)player.x() / blockSize) * blockSize);
            p.setY(player.y() + offset.y());
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }

        }
        //move down smoothly
        if(xldiff < 15 && offset.y() > 0)
        {
            QPoint p;
            p.setX(player.x() / blockSize * blockSize);
            p.setY(player.y() + offset.y());
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        else if(xrdiff < 15 && offset.y() > 0)
        {
            QPoint p;
            p.setX(ceil((double)player.x() / blockSize) * blockSize);
            p.setY(player.y() + offset.y());
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        //move left smoothly
        if(yudiff < 15 && offset.x() < 0)
        {
            QPoint p;
            p.setX(player.x() + offset.x());
            p.setY(ceil((double)player.y() / blockSize) * blockSize);
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        else if(yddiff < 15 && offset.x() < 0)
        {
            QPoint p;
            p.setX(player.x() + offset.x());
            p.setY(player.y() / blockSize * blockSize);
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        //move right smoothly
        if(yudiff < 15 && offset.x() > 0)
        {
            QPoint p;
            p.setX(player.x() + offset.x());
            p.setY(ceil((double)player.y() / blockSize) * blockSize);
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
        else if(yddiff < 15 && offset.x() > 0)
        {
            QPoint p;
            p.setX(player.x() + offset.x());
            p.setY(player.y() / blockSize * blockSize);
            if(collider.collide(blockSize,p) == nullptr)
            {
                moveFlag = true;
                player.pos() = p;
            }
        }
    }
    if(moveFlag)
    {
        if(map.eatDot(transform(player,player.pos())))
        {
            static int i;
            qDebug() << "Eat a dot (" << ++i << ")";
        }
        player.countState();
    }
    else
        player.setAnimatedState(AS_1);
}

Character& CPacManGame::getPlayer()
{
    return player;
}

const Character& CPacManGame::getPlayer() const
{
    return player;
}

const PictureFactory& CPacManGame::getFactory() const
{
    return factory;
}

QPoint CPacManGame::transform(const Character &c,const QPoint &p)
{
    int blockSize = factory.blockSize();
    switch(c.direction())
    {
    case LD_Left:
        return QPoint((p.x() / blockSize + 1),
                      (p.y() / blockSize));
        break;
    case LD_Up:
        return QPoint((p.x() / blockSize),
                      (p.y() / blockSize + 1));
        break;
    default:
        return QPoint((p.x() / blockSize),
                      (p.y() / blockSize));
    }
}

int CPacManGame::rows() const
{
    return map.rows();
}
int CPacManGame::cols() const
{
    return map.cols();
}

CGameWindow::CGameWindow(CPacManGame *game)
{
    this->game = game;
}

void CGameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    drawBackground(painter);
    drawCharacter(painter);
}


void CGameWindow::drawBackground(QPainter& painter)
{
    PictureFactory &factory = game->factory;
    int blockSize = factory.blockSize();
    MapInteger unit;
    for(int i=0;i<game->map.rows();i++)
    {
        for(int j=0;j<game->map.rows();j++)
        {
            unit = game->map[i][j];
            if((unit & MU_PATH) == MU_PATH)
                painter.drawPixmap(i*blockSize,j*blockSize,blockSize,blockSize,factory.getPixmap(MU_PATH));
            else if((unit & MU_BLOCK) == MU_BLOCK)
                painter.drawPixmap(i*blockSize,j*blockSize,blockSize,blockSize,factory.getPixmap(MU_BLOCK));
            if((unit & MU_GHOST_DOOR) == MU_GHOST_DOOR)
                painter.drawPixmap(i*blockSize,j*blockSize,blockSize,blockSize,factory.getPixmap(MU_GHOST_DOOR));
            if((unit & MU_SCORE_DOT) == MU_SCORE_DOT)
                painter.drawPixmap(i*blockSize,j*blockSize,blockSize,blockSize,factory.getPixmap(MU_SCORE_DOT));
        }
    }
}

void CGameWindow::drawCharacter(QPainter& painter)
{
    Character &player = game->player;
    PictureFactory &factory = game->factory;
    int blockSize = factory.blockSize();
    painter.drawPixmap(player.x(),player.y(),blockSize,blockSize,factory.getPixmap(player));
}
