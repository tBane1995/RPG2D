# add the library that runs
file(GLOB RPG2D_Editor_SOURCES LIST_DIRECTORIES false *.cpp)
file(GLOB RPG2D_Editor_HEADERS LIST_DIRECTORIES false *.hpp)

file(GLOB RPG2D_Editor_Common_SOURCES LIST_DIRECTORIES false ../*.cpp)
file(GLOB RPG2D_Editor_Common_HEADERS LIST_DIRECTORIES false ../*.hpp)

add_executable(RPG2D_Editor ${RPG2D_Editor_SOURCES} ${RPG2D_Editor_HEADERS} ${RPG2D_Editor_Common_SOURCES} ${RPG2D_Editor_Common_HEADERS} ${Common_SOURCES} ${Common_HEADERS})
target_include_directories(RPG2D_Editor PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/include>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>")
set_target_properties(RPG2D_Editor PROPERTIES
                      LINKER_LANGUAGE CXX
                      )
                      
#target_link_libraries(RPG2D_Editor PUBLIC optimized RPG2D_compiler_flags sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(RPG2D_Editor PUBLIC RPG2D_compiler_flags sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d)
target_link_directories(RPG2D_Editor PUBLIC ${CMAKE_CURRENT_BINARY_DIR} "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/dependencies/SFML/lib>")
set_property(TARGET RPG2D_Editor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

source_group("Source Files\\" FILES ${RPG2D_Editor_SOURCES} ${RPG2D_Editor_Common_SOURCES})
source_group("Header Files\\" FILES ${RPG2D_Editor_HEADERS} ${RPG2D_Editor_Common_HEADERS})
source_group("Source Files\\Platform" FILES ${Common_SOURCES})
source_group("Header Files\\Platform" FILES ${Common_HEADERS})
