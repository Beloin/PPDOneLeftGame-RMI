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
    QTCell(QGraphicsItem *parent, Cell &cell);
    explicit QTCell(Cell &cell);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    [[nodiscard]] QRectF boundingRect() const override;

private:
    Cell &cell;
};


#endif //ONE_LEFT_QTCELL_H
