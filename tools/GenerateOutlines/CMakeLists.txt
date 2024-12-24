# add the library that runs
file(GLOB GenerateOutlines_SOURCES LIST_DIRECTORIES false *.cpp)

add_executable(GenerateOutlines ${GenerateOutlines_SOURCES})
target_include_directories(GenerateOutlines PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/include>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tools>")
set_target_properties(GenerateOutlines PROPERTIES
                      LINKER_LANGUAGE CXX
                      )

#target_link_libraries(RPG2D_Game PUBLIC optimized RPG2D_compiler_flags sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(GenerateOutlines PUBLIC RPG2D_compiler_flags sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d)
target_link_directories(GenerateOutlines PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/lib>")
set_property(TARGET GenerateOutlines PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

source_group("Source Files\\" FILES ${GenerateOutlines_SOURCES})
