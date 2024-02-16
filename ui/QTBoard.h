//
// Created by beloin on 12/02/24.
//

#ifndef ONE_LEFT_QTBOARD_H
#define ONE_LEFT_QTBOARD_H

#include <QGraphicsView>
#include "QTCell.h"
#include "Board.h"

class QTBoard : public QGraphicsView {

private:
    Board &board;

public:
    QTBoard(Board& board, QGraphicsScene *scene, QWidget *parent);

    void updateCells();

protected:
    void paintEvent(QPaintEvent *event) override;


};


#endif //ONE_LEFT_QTBOARD_H
