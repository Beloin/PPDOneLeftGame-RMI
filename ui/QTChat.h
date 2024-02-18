//
// Created by beloin on 17/02/24.
//

#ifndef ONE_LEFT_QTCHAT_H
#define ONE_LEFT_QTCHAT_H


#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>

class QTChat : public QVBoxLayout {
private:
    QLineEdit *lineEdit;

    void sendMessage();

public:
    QListWidget *listView;

    void addUserMessage(const std::string &);

    QTChat();

    void addOpponentMessage(const std::string &msg);
};


#endif //ONE_LEFT_QTCHAT_H
