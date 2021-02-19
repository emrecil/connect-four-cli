# list all source files
set(SourceFiles
    src/connect_four/game.c
    src/connect_four/negamax.c
)

# list all header files
set(HeaderFiles
    src/connect_four/game.h
    src/connect_four/negamax.h
)

add_library(connect_four 
    ${SourceFiles}
    ${HeaderFiles}
)

target_include_directories(connect_four PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")