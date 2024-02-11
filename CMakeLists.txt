cmake_minimum_required(VERSION 3.24)
project(test_qt5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(test_qt5 main.cpp ApplicationMain.cpp ApplicationMain.h)
target_link_libraries(test_qt5
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

add_subdirectory(ui)