cmake_minimum_required(VERSION 3.16)
project(demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER /Users/mano233/Documents/dev_tool/llvm-11.0.0/bin/clang)
set(CMAKE_CXX_COMPILER /Users/mano233/Documents/dev_tool/llvm-11.0.0/bin/clang++)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

#add_subdirectory(./googletest)
#include_directories(./googletest/googletest/include)
#set(CXX_FLAGS -mcmodel=large)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(FLAGS  "-Wunused-variable -Wno-infinite-recursion -Werror=implicit-function-declaration -Wshadow -Wno-shadow-field-in-constructor-modified -Wno-shadow-ivar -Wuninitialized -Wunused-label -Wunused-lambda-capture")

include_directories(src/include)

set(CMAKE_C_FLAGS ${FLAGS})

set(CMAKE_CXX_FLAGS ${FLAGS})

set(MOC_FILE
        src/include/ProdConsService2.h
        src/include/DynamicAlloc.h
        )
set(SRC_FILE
        main.cpp
        src/TaskManager.cpp
        src/malloc/memlib.cpp
        src/malloc/mm.cpp
        src/DynamicAlloc.cpp
        src/ProdConsService2.cpp)

option(QT6 "qt version 6" ON)

if (QT6)
    MESSAGE(STATUS "use QT6")
    IF (WIN32)
        MESSAGE(STATUS "Now is windows")
        set(CMAKE_PREFIX_PATH "E:\\toolchain\\qt\\6.0.0\\mingw81_64\\lib\\cmake")
    ELSEIF (APPLE)
        MESSAGE(STATUS "Now is Apple systens.")
#        set(CMAKE_PREFIX_PATH "/Users/mano233/qt/6.0.0/clang_64/lib/cmake")
        set(CMAKE_PREFIX_PATH "/Users/mano233/Documents/GitHub/qt5/qt6-build/install/lib/cmake")
    ENDIF ()
    set(REQUIRED_LIBS Core Gui Widgets Quick QuickControls2 ShaderTools)
    set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::QuickControls2)
    find_package(Qt6 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
    qt6_add_executable(${PROJECT_NAME}
            ${SRC_FILE}
            ${MOC_FILE})
    qt6_add_shaders(${PROJECT_NAME} "untitled3_shaders"
            MSL "20"
            PRECOMPILE
            PREFIX
            /
            FILES
            qml/shader/shader.frag
            qml/shader/mask.frag
            qml/shader/heart.frag
            qml/shader/lighting.frag
            )
    qt6_add_resources(${PROJECT_NAME} "untitled3"
            PREFIX
            /
            FILES
            qml/ProdconsService.qml
            qml/mainwindow.qml
            qml/qml01.qml
            qml/qml02.qml
            qml/qml03.qml
            qml/qml04.qml
            qml/Request.qml
            qml/DynamicAlloc.qml
            arrow.svg
            )
else ()
    MESSAGE(STATUS "use QT5")
    option(QT5 "qt version 5" ON)
    set(CMAKE_PREFIX_PATH "/Users/mano233/qt/5.15.1/clang_64/lib/cmake")
    set(REQUIRED_LIBS Core Gui Widgets Quick)
    set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)
    find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
    add_executable(${PROJECT_NAME}
            ${SRC_FILE}
            ${MOC_FILE})

endif ()

#add_executable(test test/Test.cpp)
#add_executable(p test.cpp src/include/ProdConsService2.h src/ProdConsService2.cpp)
#target_link_libraries(test gtest)
#add_compile_options(-x objective-c++)
#set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation")
#add_executable(tmp02 main.mm)
configure_file(option.h.in option.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED})
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG)
