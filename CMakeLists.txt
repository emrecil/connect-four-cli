cmake_minimum_required(VERSION 3.1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# name of this project
set(ProjectName ConnectFour)

project(${ProjectName}
        VERSION 1.0
        LANGUAGES C
)

set(CMAKE_C_STANDARD 99)


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# list all source files
set(SourceFiles
    connect_four.c
    game.c
)

# list all header files
set(HeaderFiles
    game.h
)


add_executable(${ProjectName} ${SourceFiles} ${Header})
