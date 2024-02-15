//
// Created by beloin on 12/02/24.
//

#include "Command.h"

#include <utility>

GameCommand::GameCommand(const int from, const int to)
        : RawCommand(CommandType::GAME), from(from), to(to) {

}

GameCommand &GameCommand::operator=(GameCommand &&other) noexcept {
    if (this == &other)
        return *this;

    this->from = other.from;
    this->to = other.to;

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
