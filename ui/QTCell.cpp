//
// Created by beloin on 12/02/24.
//

#include <QPen>
#include "QTCell.h"
#include<QPainter>

void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Qt::GlobalColor color{Qt::white};
    if (cell.isValid()) {
        color = cell.isActive() ? Qt::red : Qt::black;
    }

    painter->setBrush(cell.isValid() ? color : Qt::white);
    painter->drawRect(boundingRect());
}

QRectF QTCell::boundingRect() const {
    qreal x = pos.x() * -50;
    qreal y = pos.y() * -50;
    return {x, y, 50, 50};
}

QTCell::QTCell(Cell &cell, QPoint pos) : cell(cell), pos(pos) {
}
