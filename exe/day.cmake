get_filename_component(DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${DAY} main.cpp)
target_link_libraries(${DAY} aoc scn::scn)
target_compile_options(${DAY} PRIVATE -pedantic -Wall -Wextra)
