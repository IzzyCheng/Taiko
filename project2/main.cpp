#include "mainwindow.h"

Game * game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QGraphicsView *view= new QGraphicsView;
    QGraphicsScene *start_scene = new QGraphicsScene();
    game= new Game;

    start_scene->setSceneRect(0, 0, 1120, 725);
    view->setBackgroundBrush(QBrush(QImage(":/picture/taiko_startview.png")));
    view->setScene(start_scene);
    view->setFixedSize(1120, 725);

    QPushButton Start(view);
    QPixmap start(":/picture/start.png");
    Start.setIcon(QIcon(start));
    Start.setIconSize(start.rect().size());
    Start.setGeometry(570, 410, start.width()+35, start.height()+35);

    QPushButton Quit(view);
    QPixmap quit_1(":/picture/exit.png");
    Quit.setIcon(QIcon(quit_1));
    Quit.setIconSize(quit_1.rect().size());
    Quit.setGeometry(950, 505, quit_1.width()+35, quit_1.height()+35);

    QObject::connect(&Quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(&Start, SIGNAL(clicked()), game, SLOT(start()));
    //QObject::connect(&Start, SIGNAL(clicked()), view, SLOT(close()));
    view->show();

    return a.exec();
}
