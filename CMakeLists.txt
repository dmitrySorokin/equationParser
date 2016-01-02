cmake_minimum_required(VERSION 3.3)
project(equationParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/include)


# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


# Add the executable
#add_executable(equationParser equationParser.cpp ${sources} ${headers})


set(SOURCE_FILES main.cpp operator.h number.h function.h token.h parenthesis.h reader.cpp equationParser.h equationParser.cpp delimiter.h exceptions.h)
add_executable(equationParser ${SOURCE_FILES})