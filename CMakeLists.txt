
cmake_minimum_required(VERSION 3.5)

project(Toast VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Command.cpp
        Command.h
        CommandWords.cpp
        CommandWords.h
        item.cpp
        item.h
        Parser.cpp
        Parser.h
        Room.cpp
        Room.h
        ZorkUL.cpp
        ZorkUL.h
        Character.cpp
        Character.h
        puzzle.h
        puzzle.cpp
        commandexception.h
        commandexception.cpp
        GameObject.h
        GameWindow.h
)

set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
set(MACOSX_BUNDLE_ICON_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/icon.icns")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Toast
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Toast APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Toast SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Toast
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Toast PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Toast PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Toast
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Toast)
endif()
