//
// Created by beloin on 12/02/24.
//

#include <QPen>
#include "QTCell.h"
#include "GameStateMachine.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <iostream>

void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Qt::GlobalColor color{Qt::white};
    if (cell.isValid()) {
        color = cell.isActive() ? Qt::red : Qt::black;
    }


    if (cell.isSelected()) {
        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(5);
        painter->setPen(pen);
    } else {
        QPen pen;
        pen.setColor(Qt::white);
        pen.setWidth(1);
        painter->setPen(pen);
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

void QTCell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    StateMachine::GameStateMachine *pStateMachine = StateMachine::GameStateMachine::getInstance();
//    std::cout << "Cell { " << this->cell.x() << ", " << cell.y() << " }" << std::endl;

    if (!this->cell.isSelected()) {
        pStateMachine->selectCell(&this->cell);
    } else {
        pStateMachine->removeCell(&this->cell);
    }

    QGraphicsItem::mousePressEvent(event);
}
