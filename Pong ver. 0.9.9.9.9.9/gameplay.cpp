#include "gameplay.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>

Gameplay::Gameplay(QGraphicsScene & scene, QGraphicsItem *g1, QGraphicsItem *g2, QGraphicsItem *pilka, QObject *parent) :
    QObject(parent),

    iScene (scene),
    iG1 (g1),
    iG2 (g2),
    iPilka (pilka),

    iPilkaKierunek (3, 3),
    iG1Kierunek(0),
    iG2Kierunek(0)
{
    iScene.setSceneRect(0, 0, 550, 500);
    iScene.addItem(iG1);
    iScene.addItem(iG2);
    iScene.addItem(iPilka);

    iG1->setPos(275, 5);
    iG2->setPos(375, 482);
    iPilka->setPos(275, 250);

    iTimer = new QTimer(this);
    iTimer->setInterval(10);
    iTimer->start();
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));
}

void Gameplay::tick()
{
    qreal newX = iPilka->pos().x() + iPilkaKierunek.x();
    qreal newY = iPilka->pos().y() + iPilkaKierunek.y();

    qreal gnewx = iG1->pos().x() + iG1Kierunek;
    qreal g2newx = iG2->pos().x() + iG2Kierunek;

    if ((newX < 0) || (newX + iPilka->boundingRect().right() > iScene.sceneRect().right()))
    {
        iPilkaKierunek.rx() *= -1;
    }

    if ( (newY < 0) || (newY + iPilka->boundingRect().bottom() > iScene.sceneRect().bottom()))
    {
        emit gol(newY / abs(newY));
        iPilkaKierunek.ry() *= -1;
    }

    if ((gnewx < 2) || (gnewx + iG1->boundingRect().right() > iScene.sceneRect().right()))
    {
        iG1Kierunek = 0;
    }

    if ( (g2newx < 2) || (g2newx + iG2->boundingRect().right() > iScene.sceneRect().right()))
    {
        iG2Kierunek = 0;
    }

    if ((iPilka->collidesWithItem(iG1)) && ( iPilkaKierunek.y() < 0))
    {
        iPilkaKierunek.ry() *= -1;
    }

    if ((iPilka->collidesWithItem(iG2) ) && ( iPilkaKierunek.y() > 0))
    {
        iPilkaKierunek.ry() *= -1;
    }

    if ( qrand() % 10 == 0 )
    {
        iG2Kierunek = obliczKierunekG2();
    }

    iPilka->moveBy(iPilkaKierunek.x(), iPilkaKierunek.y());
    iG1->moveBy(iG1Kierunek, 0);
    iG2->moveBy(iG2Kierunek, 0);
}

bool Gameplay::eventFilter(QObject *target, QEvent *e)
{
    Q_UNUSED(target);

    bool handled = false;

    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)e;

        if (keyEvent->key() == Qt::Key_A)
        {
            iG1Kierunek = (iG1Kierunek == 0 ? -5 : 0);
            handled = true;
        }
        else if (keyEvent->key() == Qt::Key_D)
        {
            iG1Kierunek  = (iG1Kierunek == 0 ? 5 : 0);
            handled = true;
        }
    }

    return handled;
}

qreal Gameplay::obliczKierunekG2()
{
    qreal kierunek = 0;

    if ( iPilka->pos().x() + iPilkaKierunek.x() > iG2->sceneBoundingRect().right() )
    {
        kierunek = 5;
    }

    else if ( iPilka->pos().x() + iPilkaKierunek.x() < iG2->sceneBoundingRect().left() )
    {
        kierunek = -5;
    }

    return kierunek;
}
