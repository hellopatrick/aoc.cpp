file(GLOB DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(DIR ${DIRECTORIES})
    if(IS_DIRECTORY ${DIR})
        add_subdirectory(${DIR})
    endif()
endforeach()
