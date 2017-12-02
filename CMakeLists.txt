cmake_minimum_required(VERSION 3.8)
project(ex04)

set(CMAKE_CXX_STANDARD 98)

include_directories(src/client/reversi)

set(SOURCE_FILES src/client/Client.cpp src/client/Client.h
        src/server/Server.cpp src/server/Server.h)

set(REVERSI_FILES src/client/reversi/AIPlayer.cpp src/client/reversi/AIPlayer.h
        src/client/reversi/Board.cpp src/client/reversi/Board.h
        src/client/reversi/Cell.cpp src/client/reversi/Cell.h
        src/client/reversi/ConsolePrinter.cpp src/client/reversi/ConsolePrinter.h
        src/client/reversi/GameManager.cpp src/client/reversi/GameManager.h
        src/client/reversi/GameRules.h src/client/reversi/Printer.h
        src/client/reversi/GenralDef.h src/client/reversi/GameState.cpp
        src/client/reversi/GameState.h src/client/reversi/ReversiDefaultRules.cpp
        src/client/reversi/ReversiDefaultRules.h src/client/reversi/Player.h
        src/client/reversi/HumanPlayer.cpp src/client/reversi/HumanPlayer.h src/client/reversi/Point.cpp
        src/client/reversi/Point.h src/client/reversi/RemoteGameManager.cpp src/client/reversi/RemoteGameManager.h)

add_executable(Client ${SOURCE_FILES} ${REVERSI_FILES} src/client/mainClient.cpp)

add_executable(Server ${SOURCE_FILES} src/server/mainServer.cpp)