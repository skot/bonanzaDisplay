# This file is preserved when LVGL Editor regenerates the UI sources.
include(${CMAKE_CURRENT_LIST_DIR}/file_list_gen.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/user_config.cmake)

add_library(lib-ui ${PROJECT_SOURCES})
target_include_directories(lib-ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(TARGET lvgl)
    target_link_libraries(lib-ui PUBLIC lvgl)
endif()
