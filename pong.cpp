#include "pong.h"

#include <QDebug>
#include <QKeyEvent>
#include <sstream>

#define WIDTH 600
#define HEIGHT (WIDTH/16*10)
#define PADDLE (WIDTH/30)

Pong::Pong() {
    // players
    player1 = new QGraphicsRectItem(0, 0, PADDLE, PADDLE * 3);
    player1->setPos(PADDLE, (HEIGHT - PADDLE * 3) / 2);
    player1->setBrush(QBrush(Qt::gray));
    addItem(player1);
    player2 = new QGraphicsRectItem(0, 0, PADDLE, PADDLE * 3);
    player2->setPos(WIDTH - PADDLE * 2, (HEIGHT - PADDLE * 3) / 2);
    player2->setBrush(QBrush(Qt::gray));
    addItem(player2);

    // ball
    ball = new QGraphicsEllipseItem(0, 0, PADDLE, PADDLE);
    ball->setPos((WIDTH - PADDLE) / 2, (HEIGHT - PADDLE) / 2);
    ball->setBrush(QBrush(Qt::gray));
    addItem(ball);

    // score
    tscore1 = new QGraphicsSimpleTextItem();
    tscore1->setText("0");
    tscore1->setFont(QFont("Times", 36, QFont::Bold));
    tscore1->setPos(WIDTH / 2 - PADDLE - 24, PADDLE);
    tscore1->setBrush(QBrush(Qt::gray));
    addItem(tscore1);
    tscore2 = new QGraphicsSimpleTextItem();
    tscore2->setText("0");
    tscore2->setFont(QFont("Times", 36, QFont::Bold));
    tscore2->setPos(WIDTH / 2 + PADDLE, PADDLE);
    tscore2->setBrush(QBrush(Qt::gray));
    addItem(tscore2);

    // line
    int h = 0;
    int pointSize = PADDLE / 4;
    while (h < HEIGHT) {
        QGraphicsRectItem *linePoint = new QGraphicsRectItem(0, 0, pointSize, pointSize);
        linePoint->setBrush(QBrush(Qt::gray));
        linePoint->setPos((WIDTH - pointSize) / 2, h);
        addItem(linePoint);
        h += pointSize * 2;
    }

    score1 = 0;
    score2 = 0;
    dx = -1;
    dy = -1;
    speedUpCounter = 0;
    ballSpeed = 0.2;
    setSceneRect(0, 0, WIDTH, HEIGHT);
    setBackgroundBrush(QBrush(Qt::black));

    QTimeLine *timer = new QTimeLine();
    timer->setFrameRange(0, 100);
    timer->setLoopCount(10000);
    timer->start();

    connect(timer, SIGNAL(frameChanged(int)), this, SLOT(value_changed(int)));
}

void Pong::value_changed(int) {
    speedUpCounter++;
    if (ball->x() >= PADDLE * 2 - (ballSpeed * PADDLE) && ball->x() <= WIDTH + (ballSpeed * PADDLE) - PADDLE * 3) {
        // ball is in game
        if (ball->collidesWithItem(player1) || ball->collidesWithItem(player2)) {
            // hit paddle
            dx = -dx;
            dy += (rand() % 3) + 1;; // random y
        } else if (ball->y() <= 0 || ball->y() >= HEIGHT - PADDLE) {
            // hit top or bottom
            dy = -dy;
        }
        if (speedUpCounter % 100 == 0) {
            // ball go faster
            ballSpeed += 0.01;
        }
        // move ball
        ball->moveBy(PADDLE * dx * ballSpeed, PADDLE * dy * ballSpeed);
    } else {
        // ball hit goal -> reset speed
        std::string s;
        std::stringstream out;
        speedUpCounter = 0;
        ballSpeed = 0.2;
        dx = -dx; // kick off 
        dy = 1; // reset random y
        if (ball->x() <= PADDLE * 2) {
            // player 1 miss -> player 2 scores
            score2++;
            out << score2;
            s = out.str();
            tscore2->setText(s.c_str());
        } else if (ball->x() >= WIDTH - PADDLE * 3) {
            // player 2 miss -> player 1 scores
            score1++;
            out << score1;
            s = out.str();
            tscore1->setText(s.c_str());
        }
        // reset ball
        ball->setPos((WIDTH - PADDLE) / 2, (HEIGHT - PADDLE) / 2);
    }
}

void Pong::keyPressEvent(QKeyEvent *e) {
    int y1 = 0;
    int y2 = 0;
    switch (e->key()) {
        case (Qt::Key_Up):
            y2 = -1;
            break;
        case (Qt::Key_Down):
            y2 = 1;
            break;
        case (Qt::Key_Q):
            y1 = -1;
            break;
        case (Qt::Key_A):
            y1 = 1;
            break;
        default:
            y1 = 0;
            y2 = 0;
            break;
    }
    if (player1->y() + ((PADDLE * y1) / 2) > 0 && player1->y() + ((PADDLE * y1) / 2) < HEIGHT - PADDLE * 3) {
        player1->moveBy(0, PADDLE * y1);
    }
    if (player2->y() + ((PADDLE * y2) / 2) > 0 && player2->y() + ((PADDLE * y2) / 2) < HEIGHT - PADDLE * 3) {
        player2->moveBy(0, PADDLE * y2);
    }
}