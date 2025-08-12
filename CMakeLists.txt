cmake_minimum_required(VERSION 3.31)
project(pipicap C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")

set(PIPICAP_SOURCE_FILES
        src/emulator.c
        src/instructions.c
)

add_executable(pipicap main.c ${PIPICAP_SOURCE_FILES})
target_include_directories(pipicap PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
