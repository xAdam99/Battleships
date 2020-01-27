cmake_minimum_required(VERSION 3.15)

project(battleships)

set(CMAKE_CXX_STANDARD 17)

file(GLOB main_SRC
        "src/*.cpp"
        )

set(SOURCE_FILES ${main_SRC})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

add_executable(main ${SOURCE_FILES})
include_directories(include)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
