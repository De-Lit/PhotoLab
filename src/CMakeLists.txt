cmake_minimum_required(VERSION 3.5)

project(PhotoLab VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories("${PROJECT_SOURCE_DIR}/view")
include_directories("${PROJECT_SOURCE_DIR}/model")
include_directories("${PROJECT_SOURCE_DIR}/controller")
include_directories("${PROJECT_SOURCE_DIR}/model/image")
include_directories("${PROJECT_SOURCE_DIR}/tests")

set(PROJECT_SOURCES
    main.cc

    controller/controller.h

    view/imagewidget.cc
    view/imagewidget.h
    view/mainwindow.ui
    view/mainwindow.cc
    view/mainwindow.h
    view/matrixwindow.cc
    view/matrixwindow.h
    view/matrixwindow.ui

    model/model.h
    model/model.cc
    model/filter.cc
    model/filter.h

    model/image/rgb.h
    model/image/color.h
    model/image/color.cc
    model/image/iimage.h
    model/image/image.h
    model/image/image.cc
)

add_executable(PhotoLab
    ${PROJECT_SOURCES}
)

target_link_libraries(PhotoLab PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PhotoLab PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PhotoLab
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Add a block to find and include GTest before creating the "tests" target
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests EXCLUDE_FROM_ALL
    tests/tests.cc
    model/model.cc
    model/filter.cc
    model/image/color.cc
    model/image/image.cc)

target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Specify the path to GTest header files
target_include_directories(tests PRIVATE
        ${GTEST_INCLUDE_DIRS})

# Link the necessary libraries for testing
target_link_libraries(tests PRIVATE
        GTest::GTest
        GTest::Main
        pthread)

# Option for coverage
option(GCOVREPORT OFF)
if (GCOVREPORT)
    target_compile_options(tests PRIVATE
        -Werror -Wall -Wextra
        -fprofile-arcs -ftest-coverage)
    target_link_libraries(tests PRIVATE gcov)
else()
    target_compile_options(tests PRIVATE
        -Werror -Wall -Wextra)
endif()
