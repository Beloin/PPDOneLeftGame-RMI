//
// Created by beloin on 12/02/24.
//

#ifndef ONE_LEFT_COMMAND_H
#define ONE_LEFT_COMMAND_H

#include <string>

enum CommandType {
    GAME = 1,
    CHAT = 2,
    OPTION = 4
};

enum Option {
    FLEE = 1,
    EXPLODE = 2
};

class RawCommand {
private:
    CommandType commandType;

public:
    explicit RawCommand(CommandType commandType) : commandType(commandType) {};
};

class GameCommand : public RawCommand {
public:
    int from;
    int to;

    GameCommand(int from, int to);

    GameCommand &operator=(GameCommand &&other) noexcept;

};

class ChatCommand : public RawCommand {
public:
    explicit ChatCommand(std::string text);

    std::string text;

    ChatCommand &operator=(ChatCommand &&other) noexcept;
};

class OptionCommand : public RawCommand {
public:
    Option option;

    explicit OptionCommand(Option option);

    OptionCommand &operator=(OptionCommand &&other) noexcept;
};

#endif //ONE_LEFT_COMMAND_H
