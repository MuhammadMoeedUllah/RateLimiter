cmake_minimum_required(VERSION 3.16)
project(RateLimiter)

set(CMAKE_CXX_STANDARD 17)
set (THIRD_PARTY_LIBS third_party/lib)
set (THIRD_PARTY_INCLUDE third_party/include)
include_directories(third_party/include
        include/)

file(GLOB INCLUDES
        include/rateLimiter/RateLimiter.hpp
        )


add_executable(${PROJECT_NAME} main.cpp ${INCLUDES})
target_link_libraries(${PROJECT_NAME}
        pthread)
add_subdirectory(tests)