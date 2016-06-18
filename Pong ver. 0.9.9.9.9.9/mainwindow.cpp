#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iPunkty(0)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QImage(":/obrazy/tlo.png")));

    //QString nazwaPliku = "tlo.png";
    //QImage image(nazwaPliku);
    //QGraphicsPixmapItem* tlo = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    //scene->addItem(tlo);

    QGraphicsRectItem *g1 = new QGraphicsRectItem(0, 0, 100, 13); //gracz
    g1->setBrush(QBrush(Qt::white));
    QGraphicsDropShadowEffect *effect_g1 = new QGraphicsDropShadowEffect();
    effect_g1->setBlurRadius(55);
    effect_g1->setOffset(4,4);
    g1->setGraphicsEffect(effect_g1);

    QGraphicsRectItem *g2 = new QGraphicsRectItem(0, 0, 100, 13); //gracz2
    g2->setBrush(QBrush(Qt::black));
    QGraphicsDropShadowEffect *effect_g2 = new QGraphicsDropShadowEffect();
    effect_g2->setBlurRadius(55);
    effect_g2->setOffset(4,-4);
    g2->setGraphicsEffect(effect_g2);

    QGraphicsEllipseItem *pilka = new QGraphicsEllipseItem(0, 0, 15, 15); //pileczka
    pilka->setBrush(QBrush(Qt::darkGreen));
    QGraphicsDropShadowEffect *effect_pilka = new QGraphicsDropShadowEffect();
    effect_pilka->setBlurRadius(45);
    effect_pilka->setOffset(1,1);
    pilka->setGraphicsEffect(effect_pilka);

    ui->boardView->setScene(scene);

    iPetla = new Gameplay(*scene, g1, g2, pilka, this);
    QSize m(scene->sceneRect().size().width() + 10, scene->sceneRect().size().height() + 10);
    ui->boardView->setMinimumSize(m);

    resize(minimumSize());
    ui->boardView->installEventFilter(iPetla);

    QObject::connect(iPetla, SIGNAL(gol(int)), this, SLOT(dodajPunkt(int)));

    ui->lcdNumber->setPalette(Qt::black);
    setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dodajPunkt(int count)
{
    iPunkty += count;
    ui->lcdNumber->display(iPunkty);
}

