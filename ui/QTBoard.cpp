//
// Created by beloin on 12/02/24.
//

#include "QTBoard.h"
#include "QGraphicsRectItem"

QTBoard::QTBoard(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            auto *cell = new QTCell{board.at(i, j), QPoint{i, j}};
            this->scene()->addItem(cell);
        }
    }

//    const QList<QGraphicsItem *> &list = scene->items(); // Use this instead os vector
//    for (const auto &item: list) {
//        item->update(); // Updates drawable QTCell
//    }

    board.setup();
}

void QTBoard::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
}


