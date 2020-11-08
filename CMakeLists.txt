cmake_minimum_required(VERSION 3.16)
project(untitled3)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#add_subdirectory(./googletest)
#include_directories(./googletest/googletest/include)
#set(CMAKE_PREFIX_PATH "E:/toolchain/qt/5.15.1/mingw81_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "/Users/mano233/qt/5.15.1/clang_64/lib/cmake")
set(CMAKE_PREFIX_PATH "/Users/mano233/qt/6.0.0/clang_64/lib/cmake")
#set(CXX_FLAGS -mcmodel=large)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)

set(MOC_FILE src/include/ProdConsService2.h)
include_directories(src/include)
# QT5
#set(QT_VERSION 5)
#set(REQUIRED_LIBS Core Gui Widgets Quick)
#set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick)

# QT6
set(REQUIRED_LIBS Core Gui Widgets Quick QuickControls2 ShaderTools)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::QuickControls2)
find_package(Qt6 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
qt6_add_executable(${PROJECT_NAME}
        main.cpp
#        src/TaskManager.cpp
        src/ProdConsService2.cpp
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
#add_executable(test test/Test.cpp)
#add_executable(p test.cpp src/include/ProdConsService2.h src/ProdConsService2.cpp)
#target_link_libraries(test gtest)


#find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${REQUIRED_LIBS_QUALIFIED})
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG>)
