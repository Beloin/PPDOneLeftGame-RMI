add_library(
        game_lib STATIC
        Board.cpp Board.h
        Cell.cpp Cell.h
        Game.cpp Game.h
        OneLeftClient.cpp OneLeftClient.h
        OneLeftServer.cpp OneLeftServer.h
        GameClient.cpp GameClient.h Messages/Command.cpp Messages/Command.h config.h Utils/GameUtils.cpp Utils/GameUtils.h)

target_include_directories(game_lib PUBLIC ../network)
