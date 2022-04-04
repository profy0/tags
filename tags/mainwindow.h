#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPicture>
#include <QTableWidgetItem>
#include "tag.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_table_cellClicked(int row, int column);

    void on_mnuNewGame_triggered();

    void on_mnuRestart_triggered();

    void on_mnuExit_triggered();

    void timerSlot();

private:
    Ui::MainWindow *ui;

    QTableWidgetItem *a[16];

    void showTable();
    void timeReset();

    QTimer *timer;
    int time;

};
#endif // MAINWINDOW_H
