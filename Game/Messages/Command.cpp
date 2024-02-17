//
// Created by beloin on 12/02/24.
//

#include "Command.h"

#include <utility>

GameCommand::GameCommand(int fromX, int fromY, int toX, int toY)
        : RawCommand(CommandType::GAME), fromX(fromX), fromY(fromY), toX(toX), toY(toY) {

}

GameCommand &GameCommand::operator=(GameCommand &&other) noexcept {
    if (this == &other)
        return *this;

    this->fromX = other.fromX;
    this->fromY = other.fromY;
    this->toX = other.toX;
    this->toY = other.toY;

    return *this;
}

ChatCommand::ChatCommand(std::string text) : RawCommand(CommandType::CHAT), text(std::move(text)) {}

ChatCommand &ChatCommand::operator=(ChatCommand &&other) noexcept {
    if (this == &other)
        return *this;

    this->text = other.text;
    return *this;
}

OptionCommand::OptionCommand(const Option option) : RawCommand(CommandType::OPTION),
                                                    option(option) {}

OptionCommand &OptionCommand::operator=(OptionCommand &&other) noexcept {
    if (this == &other)
        return *this;

    this->option = other.option;
    return *this;
}
