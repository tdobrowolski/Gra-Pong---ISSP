#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QGraphicsScene>

class Gameplay : public QObject
{
    Q_OBJECT

public:
    Gameplay(QGraphicsScene & scene, QGraphicsItem *G1, QGraphicsItem *G2, QGraphicsItem *pilka, QObject *parent);

protected:
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void gol(int gracz);

private slots:
    void tick();

private:
    QGraphicsScene & iScene;
    QGraphicsItem *iG1, *iG2, *iPilka;
    QTimer *iTimer;

    QPointF iPilkaKierunek;
    qreal iG1Kierunek;
    qreal iG2Kierunek;
    qreal obliczKierunekG2();
};

#endif // GAMEPLAY_H
