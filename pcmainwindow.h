#ifndef PCMAINWINDOW_H
#define PCMAINWINDOW_H

#include <QMainWindow>
#include "pacman.h"

class PcMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PcMainWindow(QWidget *parent = 0);
    ~PcMainWindow();
    void                keyPressEvent(QKeyEvent *event);
    void                keyReleaseEvent(QKeyEvent *event);
    void                timerEvent(QTimerEvent *event);
    void                setTimer(int delayMs);
private:
    int                 pixelVelocity;
    int                 timerID;
    int                 delay;
    QPoint              offset;
    CPacManGame         game;
    CGameWindow        *centralWidget;
};

#endif // PCMAINWINDOW_H
