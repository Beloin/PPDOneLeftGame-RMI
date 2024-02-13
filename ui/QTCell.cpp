//
// Created by beloin on 12/02/24.
//

#include <QPen>
#include "QTCell.h"
#include<QPainter>

QTCell::QTCell(QGraphicsItem *parent, Cell &cell) : QGraphicsItem(parent), cell(cell) {
}

void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(cell.isActive() ? Qt::black : Qt::red);
    painter->drawEllipse(boundingRect());
}

QRectF QTCell::boundingRect() const {
    return {-50, -50, 50, 50};
}

QTCell::QTCell(Cell &cell) : cell(cell) {

}
