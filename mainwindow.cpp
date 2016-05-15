#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

extern Game * game;

Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent) {
}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F) {
        Bullet * bullet =new Bullet();
        bullet->setPos(x(), y());
        scene()->addItem(bullet);
    }
    else if(event->key() == Qt::Key_J) {
        Bullet_2 * bullet_2 = new Bullet_2();
        bullet_2->setPos(x(), y());
        scene()->addItem(bullet_2);
    }
}

void Player::spawn() {
    int rand_pic=rand()%2+1;
    if (game->clock_1->time<0) {
        return;
    }
    if (rand_pic==1) {
        Drum *drum=new Drum();
        scene()->addItem(drum);
    }
    else if (rand_pic==2) {
        Drum_2 *drum_2=new Drum_2();
        scene()->addItem(drum_2);
    }
}


Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent) {
    setRect(20, 0, 2, 2);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Bullet::move() {
    QList<QGraphicsItem *> collid_item = collidingItems();
    for (int i=0, n=collid_item.size(); i<n; ++i) {
        if (typeid(*(collid_item[i])) == typeid(Drum)) {
            game->score->increase();
            scene()->removeItem(collid_item[i]);
            scene()->removeItem(this);
            delete collid_item[i];
            delete this;
            return;
        }
    }
    setPos(x(), y()-20);
    if (pos().y()+rect().height()<200) {
        scene()->removeItem(this);
        delete this;
    }
}

Bullet_2::Bullet_2(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent) {
    setRect(20, 0, 2, 2);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Bullet_2::move() {
    QList<QGraphicsItem *> collid_item = collidingItems();
    for (int i=0, n=collid_item.size(); i<n; ++i) {
        if (typeid(*(collid_item[i])) == typeid(Drum_2)) {
            game->score->increase();
            scene()->removeItem(collid_item[i]);
            scene()->removeItem(this);
            delete collid_item[i];
            delete this;
            return;
        }
    }
    setPos(x(), y()-20);
    if (pos().y()+rect().height()<200) {
        scene()->removeItem(this);
        delete this;
    }
}


Drum::Drum(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPos(1050, 190);
    setPixmap(QPixmap(":/picture/taiko_red.png"));
    setTransformOriginPoint(40, 40);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Drum::move() {
    setPos(x()-10, y());
    if (pos().x() <280) {
        scene()->removeItem(this);
        delete this;
    }
}

Drum_2::Drum_2(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPos(1050, 190);
    setPixmap(QPixmap(":/picture/taiko_blue.png"));
    setTransformOriginPoint(40, 40);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Drum_2::move() {
    setPos(x()-10, y());
    if (pos().x() <280) {
        scene()->removeItem(this);
        delete this;
    }
}


Score::Score(QGraphicsTextItem *parent): QGraphicsTextItem(parent) {
    score=0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 36));
}

void Score::increase() {
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore() {
    return score;
}


Clock::Clock(QGraphicsTextItem *parent): QGraphicsTextItem(parent) {
    time=30;
    setPlainText(QString("Time: ")+QString::number(time));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 36));
}

void Clock::countdown() {
    time--;
    if (time>=0) {
        setPlainText(QString("Time: ")+QString::number(time));
    }
    else if(time == -7) {
        game->close();
        Result *result=new Result;
    }
}

void Game::start() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 50, 1120, 625);
    setBackgroundBrush(QBrush(QImage(":/picture/taiko_bg.png")));
    setScene(scene);
    setFixedSize(1120, 725);

    underbar= new QGraphicsPixmapItem();
    underbar->setPixmap(QPixmap(":/picture/taiko_underbar.png"));
    underbar->setPos(0, 625);
    scene->addItem(underbar);

    player = new Player();
    player->setRect(0, 0, 40, 5);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(345, 313);
    scene->addItem(player);

    score=new Score();
    scene->addItem(score);
    score->setPos(850, 40);
    clock_1=new Clock();
    scene->addItem(clock_1);
    clock_1->setPos(650, 40);

    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), clock_1, SLOT(countdown()));
    timer->start(1000);

    QTimer * timer_2 = new QTimer();
    QObject::connect(timer_2, SIGNAL(timeout()), player, SLOT(spawn()));
    timer_2->start(800);
    show();
}

Result::Result(QWidget * parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 570, 560);
    view = new QGraphicsView();
    view->setBackgroundBrush(QBrush(QImage(":/picture/taiko_result.jpg")));
    view->setScene(scene);
    view->setFixedSize(570, 560);

    scene->addItem(game->score);
    game->score->setPos(210, 180);

    /*
    QPushButton Restart(view);
    QPixmap start(":/picture/start.png");
    Restart.setIcon(QIcon(start));
    Restart.setIconSize(start.rect().size());
    Restart.setGeometry(100, 100, start.width()+35, start.height()+35);

    QPushButton Quit(view);
    QPixmap quit_1(":/picture/exit.png");
    Quit.setIcon(QIcon(quit_1));
    Quit.setIconSize(quit_1.rect().size());
    Quit.setGeometry(110, 100, quit_1.width()+35, quit_1.height()+35);

    QObject::connect(&Quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(&Restart, SIGNAL(clicked()), game, SLOT(start()));
    QObject::connect(&Restart, SIGNAL(clicked()), view, SLOT(close()));
    */
    view->show();
}
