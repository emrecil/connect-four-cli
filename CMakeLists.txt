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

add_subdirectory(connect_four)

add_executable(ConnectFour connect_four.c)

target_link_libraries(ConnectFour PRIVATE connect_four)
