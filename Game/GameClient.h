//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_GAMECLIENT_H
#define ONE_LEFT_GAMECLIENT_H

#include <ostream>

class GameClient {

public:
  int id;
  std::string clientAddr;

  GameClient(int id);

  GameClient(int id, std::string clientAddr);

  void operator()(const GameClient &other, bool isStartTurn) const;

  friend std::ostream &operator<<(std::ostream &os, const GameClient &client);

  friend std::ostream &operator<<(std::ostream &os, const GameClient *client);
};

#endif // ONE_LEFT_GAMECLIENT_H
