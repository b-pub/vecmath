cmake_minimum_required(VERSION 3.10)

project(vecmath CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Werror")

# The "btest" library is https://github.com/b-pub/btest.git
set(BTEST_DIR "../btest")
set(BTEST_INC "${BTEST_DIR}/include")
set(BTEST_MAIN "${BTEST_DIR}/src/btest_main.cpp")

#----------------
# Add test executable
add_executable(runtests
    tests/test_ctor.cpp
    tests/test_dotcross.cpp
    tests/test_funcs.cpp
    tests/test_circle.cpp
    tests/test_circled.cpp
    tests/test_mats.cpp
    ${BTEST_MAIN}
)

include_directories(${BTEST_INC})
include_directories(include)

target_link_libraries(runtests)
