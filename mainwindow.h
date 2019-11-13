#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "QPushButton"
#include  "QWidget"
#include  "QLabel"
#include "QLCDNumber"
#include "QTimer"
#include "QRandomGenerator"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);



    ~MainWindow();


public slots:

    void slotRestartClicked();
    void slotButtonClicked();
    void Timer();
    void closeCard();
    void showAllCards();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
