/*
 * File:   main.cpp
 * Author: Andreas Peichert <peichert@gmail.com>
 *
 * Created on January 30, 2013, 3:08 PM
 */

#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "pong.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget *main = new QWidget();

    QGraphicsScene *scn = new Pong();
    QGraphicsView *view = new QGraphicsView(scn, main);

    main->resize(scn->width(), scn->height());
    main->show();
    return app.exec();
}
