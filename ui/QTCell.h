//
// Created by beloin on 12/02/24.
//

#ifndef ONE_LEFT_QTCELL_H
#define ONE_LEFT_QTCELL_H


#include <QGraphicsItem>
#include <QPaintEvent>
#include "Cell.h"

class QTCell : public QGraphicsItem {

public:
    QTCell(Cell &cell, QPoint pos);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

    Cell &cell;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPoint pos{-1, -1};

};


#endif //ONE_LEFT_QTCELL_H
