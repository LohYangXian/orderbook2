cmake_minimum_required(VERSION 3.12)
project(OrderBookDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(OrderBookDemo ${SOURCE_FILES})

include_directories(OrderBook)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(OrderBook)
add_subdirectory(OrderBookTests)

target_link_libraries(OrderBookDemo OrderBook)
