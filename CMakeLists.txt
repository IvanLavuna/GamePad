cmake_minimum_required(VERSION 3.16)
project(GamePad)

set(CMAKE_CXX_STANDARD 14)

set(HEADER Headers/Game.h States/State.h States/MainMenuState.h Entities/Entity.h States/GameState.h
        Animation/Animation.h Animation/BurstAnimation.h GUI/gui.h)

set(SOURCE Source/main.cpp Source/Game.cpp States/State.cpp States/GameState.cpp  Entities/Entity.cpp
        States/MainMenuState.cpp Animation/Animation.cpp
        Animation/BurstAnimation.cpp GUI/gui.cpp States/PlayState.cpp States/PlayState.h Source/Matrix.cpp Source/Matrix.h Source/BlockFigure.cpp Source/BlockFigure.h)

include_directories(Headers Source States Entities Fonts Images Animation GUI)

add_executable(GamePad ${HEADER} ${SOURCE})

target_link_libraries(GamePad
        sfml-audio
        sfml-graphics
        sfml-network
        sfml-system
        sfml-window)