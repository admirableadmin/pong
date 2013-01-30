/* 
 * File:   pong.h
 * Author: Andreas Peichert <peichert@gmail.com>
 *
 * Created on May 26, 2012, 4:44 PM
 */

#ifndef PONG_H
#define	PONG_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimeLine>

class Pong : public QGraphicsScene {
    Q_OBJECT
public:
    Pong();
protected:
    void keyPressEvent(QKeyEvent *e);
public slots:
    void value_changed(int);
private:
    QGraphicsRectItem *player1, *player2;
    QGraphicsEllipseItem *ball;
    QTimeLine *timer;
    QGraphicsSimpleTextItem *tscore1, *tscore2;
    int dx, dy;
    int score1, score2;
    int speedUpCounter;
    double ballSpeed;
};

#endif	/* PONG_H */

