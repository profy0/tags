#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPicture>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

tag t;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(auto i = 0; i < 4; i++) {
        ui->table->setColumnWidth(i,122);
        ui->table->setRowHeight(i, 122);
    }
    ui->labelTimer->setText("Времени прошло: 0");
    ui->steps->setText("Шагов: 0");
    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1000);

    for(int i = 0; i < 16; i++) a[i] = new QTableWidgetItem;

    for(int i = 0; i < 15; i++) {
        a[i]->setBackground(QBrush(Qt::green));
        a[i]->setData(Qt::FontRole, QFont("times", 50, QFont::Bold));
        a[i]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        a[i]->setText(QString::number(i+1));
    }

    showTable();

}


void MainWindow::timeReset() {
    this->time = 0;
}

void MainWindow::showTable() {
    ui->steps->setText("Шагов: " + QString::number(t.getStep()));
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ui->table->setItem(i, j, new QTableWidgetItem(*a[t.getItem(i, j)]));
        }
    }
}

void MainWindow::on_table_cellClicked(int row, int column) {
    t.reCalc(row, column);
    showTable();
    if(t.isFinished()) {
        timer->stop();
        if(QMessageBox::question(this, "Игра закончена", "Победа! Желаете сыграть еще раз?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
            t.startGame();
            ui->labelTimer->setText("Времени прошло: 0");
            timeReset();
            timer->start(1000);
            showTable();
        } else {
            QApplication::quit();
        }
    }
}

void MainWindow::on_mnuExit_triggered() {
    QApplication::quit();
}

void MainWindow::timerSlot() {
    time++;
    ui->labelTimer->setText("Времени прошло: " + QString::number(time));
}

void MainWindow::on_mnuNewGame_triggered() {
    timeReset();
    ui->labelTimer->setText("Времени прошло: 0");
    t.startGame();
    showTable();
}

void MainWindow::on_mnuRestart_triggered() {
    t.restartGame();
    showTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0; i < 16; i++) {
        delete a[i];
    }
}


