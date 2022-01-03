cmake_minimum_required(VERSION 3.16)
project(TEST_RateLimiter)

set(CMAKE_CXX_STANDARD 17)
set (THIRD_PARTY_LIBS third_party/lib)
set (THIRD_PARTY_INCLUDE third_party/include)
include_directories(third_party/include
        include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB INCLUDES
        include/rateLimiter/RateLimiter.cpp
        )

add_executable(${PROJECT_NAME} test.cpp ${INCLUDES})
target_link_libraries(${PROJECT_NAME}
        pthread)
