cmake_minimum_required(VERSION 3.16)
project(untitled3)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(./googletest)
#include_directories(./googletest/googletest/include)
#set(CXX_FLAGS -mcmodel=large)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(src/include)
set(MOC_FILE src/include/ProdConsService2.h src/include/TaskManager.h)
set(SRC_FILE
        main.cpp
        src/TaskManager.cpp
        src/ProdConsService2.cpp)

set(qt_version 6)
if (qt_version EQUAL 6)
    MESSAGE("use QT 6.0.0")
    set(CMAKE_PREFIX_PATH "/Users/mano233/qt/6.0.0/clang_64/lib/cmake")
    set(REQUIRED_LIBS Core Gui Widgets Quick QuickControls2 ShaderTools)
    set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::QuickControls2)
    find_package(Qt6 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
    qt6_add_executable(${PROJECT_NAME}
            ${SRC_FILE}
            ${MOC_FILE})
    qt6_add_shaders(${PROJECT_NAME} "untitled3_shaders"
            PREFIX
            /
            FILES
            qml/shader/shader.frag
            )
    qt6_add_resources(${PROJECT_NAME} "untitled3"
            PREFIX
            /
            FILES
            qml/ProdconsService.qml
            )
else ()
    MESSAGE("use QT 5.15.1")
    set(REQUIRED_LIBS Core Gui Widgets Quick)
    set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
    set(CMAKE_PREFIX_PATH "/Users/mano233/qt/5.15.1/clang_64/lib/cmake")
    find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
endif ()

#add_executable(test test/Test.cpp)
#add_executable(p test.cpp src/include/ProdConsService2.h src/ProdConsService2.cpp)
#target_link_libraries(test gtest)
#add_executable(tmp01 temp/tmp01.cpp src/TaskManager.cpp src/include/TaskManager.h)
target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED})
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG)
