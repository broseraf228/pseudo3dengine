cmake_minimum_required(VERSION 3.16)
project(game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

FILE(GLOB_RECURSE headers "src/*.hpp")
FILE(GLOB_RECURSE sources "src/*.cpp")

add_executable(${PROJECT_NAME} ${sources} ${headers})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${sources} ${headers})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)	
	
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
