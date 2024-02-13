//
// Created by beloin on 12/02/24.
//

#include "QTBoard.h"
#include "QGraphicsRectItem"

QTBoard::QTBoard(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            auto *cell = new QTCell{board.at(i, j)}; // TODO: Add position? No, we will use position in who we call
            this->scene()->addItem(cell);
        }
    }

//    const QList<QGraphicsItem *> &list = scene->items(); // Use this instead os vector
//    for (const auto &item: list) {
//        item->update(); // Updates drawable QTCell
//    }
}

void QTBoard::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
}


