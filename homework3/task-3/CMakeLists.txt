cmake_minimum_required(VERSION 3.10)
project(SortingComparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройки компилятора
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")
endif()

# Основная программа
add_executable(SortingComparison main.cpp)

# Включение директив для предварительно скомпилированных заголовков (опционально)
target_include_directories(SortingComparison PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})