#include "mainwindow.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <iostream>
#include <unistd.h>

using namespace std;

//static int counter=0;
static int tries=0;
static int pairs=0;
static vector<string> alphabet={"A","B","C","D","E","F","G","H","I","J","K","L","A","B","C","D","E","F","G","H","I","J","K","L"};
static queue<QPushButton *> button_queue;
static QPushButton * Buttons[24];
static QPushButton * popped;
static QPushButton * button;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{
    ui->setupUi(this);
srand(time(0));
std::random_shuffle(alphabet.begin(),alphabet.end());


for(int i=1; i<=24;++i){

    if(i<10){
        QString butName="B0"+ QString::number(i);
        Buttons[i-1]=MainWindow::findChild<QPushButton *>(butName);
        connect(Buttons[i-1], SIGNAL(clicked()) , this , SLOT (slotButtonClicked()));

    }else{
        QString butName="B"+ QString::number(i);
        Buttons[i-1]=MainWindow::findChild<QPushButton *>(butName);
        connect(Buttons[i-1], SIGNAL(clicked()) , this , SLOT (slotButtonClicked()));

    }
}

connect(ui->Reset, SIGNAL (clicked()), this, SLOT (slotRestartClicked()));




}
void MainWindow::Timer(){
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->start(1110);

    connect(timer, SIGNAL(timeout()), this, SLOT(closeCard()));

}
void MainWindow::showAllCards(){
    for (QPushButton * x : Buttons){
        x->setDisabled(true);
        QString mystring=x->objectName();
        string subString=mystring.right(2).toUtf8().constData();
        int index=stoi(subString);
        QString tmp = QString::fromStdString(alphabet[(unsigned)index-1]);
        button->setText(tmp);
    }
}

void MainWindow::closeCard(){

    popped->setDisabled(false);
    button->setDisabled(false);
    popped->setText("X");
    button->setText("X");
    for(int i=0; i<24;++i)
    connect(Buttons[i], SIGNAL(clicked()) , this , SLOT (slotButtonClicked()));

}



void MainWindow::slotButtonClicked(){

    button= (QPushButton *)sender();
    QString mystring=button->objectName();
    string subString=mystring.right(2).toUtf8().constData();
    int index=stoi(subString);
    QString tmp = QString::fromStdString(alphabet[(unsigned)index-1]);
    button->setText(tmp);


    button->setDisabled(true);

    button_queue.push(button);
    if(button_queue.size()==2){

        for(int i=0; i<24;++i)
        disconnect(Buttons[i], SIGNAL(clicked()) , this , SLOT (slotButtonClicked()));

       tries++;
       popped=button_queue.front();
       button_queue.pop();
       button_queue.pop();

       if(button->text()==popped->text()){
           popped->setDisabled(true);
           button->setDisabled(true);
           pairs++;
           ui->Npairs->display(pairs);
           for(int i=0; i<24;++i)
           connect(Buttons[i], SIGNAL(clicked()) , this , SLOT (slotButtonClicked()));

         }else{
           Timer();
       }
    }



    ui->NTries->display(tries);
}
void MainWindow::slotRestartClicked(){
    tries=0;
    pairs=0;
    ui->NTries->display(tries);
    ui->Npairs->display(pairs);
    while(!button_queue.empty()){
        button_queue.pop();}

    for(int i=0;i<24;i++){

        Buttons[i]->setText(QString::fromStdString("X"));
        Buttons[i]->setDisabled(false);
    }
std::random_shuffle(alphabet.begin(),alphabet.end());
  }


MainWindow::~MainWindow()
{
    delete ui;
}
