#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Gameplay;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void dodajPunkt(int count);

private:
    Ui::MainWindow *ui;
    Gameplay *iPetla;
    int iPunkty;
};

#endif // MAINWINDOW_H
