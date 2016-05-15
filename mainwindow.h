#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QObject>
#include <QList>
#include <QGraphicsTextItem>
#include <QWidget>
#include <QBrush>
#include <QtGui>
#include <string>
#include <stdlib.h>

class Player: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
private:
    int count;
};

class Bullet: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);
public slots:
    void move();
};

class Bullet_2: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bullet_2(QGraphicsItem * parent=0);
public slots:
    void move();
};

class Drum: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Drum(QGraphicsItem *parent=0);
public slots:
    void move();
};

class Drum_2: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Drum_2(QGraphicsItem *parent=0);
public slots:
    void move();
};

class Score: public QGraphicsTextItem {
public:
    Score(QGraphicsTextItem *parent=0);
    void increase();
    int getScore();
    int score;
};

class Clock: public QGraphicsTextItem {
    Q_OBJECT
public:
    Clock(QGraphicsTextItem *parent=0);
    int time;
public slots:
    void countdown();
};

class Game: public QGraphicsView {
    Q_OBJECT
public:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *underbar;
    Player *player;
    Score *score;
    Clock *clock_1;
public slots:
    void start();
};

class Result: public QGraphicsView {
    Q_OBJECT
public:
    QGraphicsView *view;
    Result(QWidget * parent=0);
    QGraphicsScene *scene;
    QPushButton Restart;
    QPushButton Quit;
};

#endif // MAINWINDOW_H
