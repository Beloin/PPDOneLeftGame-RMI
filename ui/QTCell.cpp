//
// Created by beloin on 12/02/24.
//

#include <QPen>
#include "QTCell.h"
#include<QPainter>

QTCell::QTCell(QGraphicsItem *parent, Cell &cell) : QGraphicsItem(parent), cell(cell) {
}

void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
}

QRectF QTCell::boundingRect() const {
    return {-10, -10, 20, 20};
}

QTCell::QTCell(Cell &cell) : cell(cell) {

}
