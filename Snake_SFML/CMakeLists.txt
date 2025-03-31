# CMakeList.txt : CMake project for Snake_SFML, include source and define
# project specific logic here.
#

set(SFML_CLASS

    SFML/Snake_SFML.cpp
    SFML/Snake_SFML.h
)


set(GAME_CLASSES 

    classes/common.h
    classes/snake.cpp
    classes/snake.h
    classes/random.h
    classes/game.h
    classes/game.cpp 
    classes/playerController.h 
    classes/playerController.cpp
    classes/display.cpp
    classes/display.h
    classes/food.h
    classes/food.cpp 
    classes/board.h)


# Add source to this project's executable.
add_executable (Snake_SFML ${SFML_CLASS} ${GAME_CLASSES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(Snake_SFML
        ${CMAKE_SOURCE_DIR}/lib/sfml-graphics-d.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-audio-d.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-system-d.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-window-d.lib
    )


else()
    target_link_libraries(Snake_SFML
        ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib
        ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib
    )

endif()


include_directories(${CMAKE_SOURCE_DIR}/include)


set_property(TARGET Snake_SFML PROPERTY CXX_STANDARD 17)
set_property(TARGET Snake_SFML PROPERTY CXX_STANDARD_REQUIRED ON)


set(RESOURCES_POLICE_DIR "${CMAKE_SOURCE_DIR}/Snake_SFML/police")

add_custom_command(TARGET Snake_SFML POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_POLICE_DIR} $<TARGET_FILE_DIR:Snake_SFML>/police
)
