# add the library that runs
file(GLOB GenTextureMap_SOURCES LIST_DIRECTORIES false *.cpp)

add_executable(GenTextureMap ${GenTextureMap_SOURCES})
target_include_directories(GenTextureMap PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/include>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tools>")
set_target_properties(GenTextureMap PROPERTIES
                      LINKER_LANGUAGE CXX
                      )

#target_link_libraries(RPG2D_Game PUBLIC optimized RPG2D_compiler_flags sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(GenTextureMap PUBLIC RPG2D_compiler_flags sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d)
target_link_directories(GenTextureMap PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/lib>")
set_property(TARGET GenTextureMap PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

source_group("Source Files\\" FILES ${GenTextureMap_SOURCES})
