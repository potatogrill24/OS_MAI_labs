cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CSS_STANDART_REQUIRED ON)

project (prog1)

add_library(Lib1 SHARED lib1/lib1.cpp)
add_library(Lib1::lib1 ALIAS Lib1)
target_include_directories(Lib1 PUBLIC ${PROJECT_SOURCE_DIR}/Lib1)

add_executable(${PROJECT_NAME} prog1.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Lib1::lib1)

project (prog2)

add_library(Lib1_1 SHARED lib1/lib1.cpp)
add_library(Lib1_1::lib1_1 ALIAS Lib1_1)
target_include_directories(Lib1 PUBLIC ${PROJECT_SOURCE_DIR}/Lib1)

add_library(Lib2 SHARED lib2/lib2.cpp)
add_library(Lib2::lib2 ALIAS Lib2)
target_include_directories(Lib2 PUBLIC ${PROJECT_SOURCE_DIR}/Lib2)

add_executable(${PROJECT_NAME} prog2.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Lib1_1::lib1_1 Lib2::lib2)
