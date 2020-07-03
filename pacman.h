#ifndef PACMAN
#define PACMAN
#include "collider.h"
#include "picture.h"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
class CGameWindow;
class CPacManGame
{
friend class CGameWindow;
public:
    CPacManGame(int width = 0,int height = 0,int mapRows = 0,int mapCols = 0,int blockSize = 30);
    CPacManGame& setPictureSize(int newBlockSize);
    CPacManGame& setWindowSize(int width,int height);
    CPacManGame& setMapSize(int rows,int cols);
    CPacManGame& openMap(QString filename);
    void movePlayer(int xOffset,int yOffset);
    void movePlayer(const QPoint &offset);
    Character& getPlayer();
    const Character& getPlayer() const;
    const PictureFactory& getFactory() const;
    QPoint transform(const Character &c,const QPoint &p);
    int rows() const;
    int cols() const;
private:
    QSize     size;
    Character player;
    CPacMap   map;
    CPacCollider collider;
    PictureFactory factory;
};

class CGameWindow : public QWidget
{
public:
    CGameWindow(CPacManGame *game);
    void paintEvent(QPaintEvent *event);
    void drawBackground(QPainter& painter);
    void drawCharacter(QPainter& painter);
private:
    CPacManGame   *game;
};


#endif // PACMAN

