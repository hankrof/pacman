#include "pcmainwindow.h"
PcMainWindow::PcMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    offset = QPoint(0,0);
    timerID = 0;
    pixelVelocity = 5;
    delay         = 40;
    centralWidget = new CGameWindow(&game);
    game.openMap("map.txt")
        .setPictureSize(30)
        .setWindowSize(30 * game.cols(),30 * game.rows());
    setCentralWidget(centralWidget);
    setFixedSize(30 * game.cols(),30 * game.rows());
    setTimer(delay);
}

PcMainWindow::~PcMainWindow()
{

}

void PcMainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    switch(event->key())
    {
    case Qt::Key_Up:
        offset = QPoint(0,-pixelVelocity);
        break;
    case Qt::Key_Down:
        offset = QPoint(0,pixelVelocity);
        break;
    case Qt::Key_Left:
        offset = QPoint(-pixelVelocity,0);
        break;
    case Qt::Key_Right:
        offset = QPoint(pixelVelocity,0);
        break;
    case Qt::Key_Space:
        delay = delay == 40 ? 5 : 40;
        setTimer(delay);
        break;
    case Qt::Key_Escape:
        close();
        break;
    }
}

void PcMainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    switch(event->key())
    {
    case Qt::Key_Up:
//        offset -= QPoint(0,-pixelVelocity);
        break;
    case Qt::Key_Down:
//        offset -= QPoint(0,pixelVelocity);
        break;
    case Qt::Key_Left:
//        offset -= QPoint(-pixelVelocity,0);
        break;
    case Qt::Key_Right:
//        offset -= QPoint(pixelVelocity,0);
        break;
    }
}

void PcMainWindow::timerEvent(QTimerEvent *)
{
    game.movePlayer(offset);
    repaint();
}

void PcMainWindow::setTimer(int delayMs)
{
    if(timerID)
        killTimer(timerID);
    timerID = startTimer(delayMs);
}
