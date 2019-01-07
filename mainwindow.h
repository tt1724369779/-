#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <Qpalette>
#include <QtDebug>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <bits/stdc++.h>
using namespace std;
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void _inite();
    void addedge(int a,int b);
    void _input();
    void tarjan(int now);
    void suodian();
    bool topsort();
    void paintEvent(QPaintEvent*);
    int getPointAt(QPoint p,int dir,int offset);
    void update_table(int x, int y);
    void printdian(QMouseEvent *event);
    void printxian(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);//鼠标键被按下的事件.
    void mouseReleaseEvent(QMouseEvent *event); //鼠标键被放开的事件.
    void mouseMoveEvent(QMouseEvent *event); //按住鼠标键移动的事件.


private slots:
    void on_pushButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_pushButton_2_clicked();

//    void on_radioButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *SelectModeGroup;
};

#endif // MAINWINDOW_H
