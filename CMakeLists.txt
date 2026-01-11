cmake_minimum_required(VERSION 3.16)
project(rencpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    src/main.cpp
    src/gameengine.cpp
    src/storynode.cpp
    src/choice.cpp
    src/storyloader.cpp
    src/mainwindow.cpp
)

set(HEADERS
    src/gameengine.h
    src/storynode.h
    src/choice.h
    src/storyloader.h
    src/mainwindow.h
)

set(RESOURCES
    resources/stories.qrc
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
