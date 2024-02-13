add_library(
        ui STATIC
        QTBoard.cpp QTBoard.h QTCell.cpp QTCell.h)

target_link_libraries(ui
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

target_include_directories(ui PUBLIC ../Game)
