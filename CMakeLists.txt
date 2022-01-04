cmake_minimum_required(VERSION 3.17)

include(FetchContent)

project(DofusBotFM)

#######################################################
#                       LIBS                          #
#######################################################

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#######################################################
#                       FLAGS                         #
#######################################################

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "/EHsc /MP /GR- /W4 /WX /wd4100 /wd4244")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /DNDEBUG /O2 /Ob2 /GF")

add_compile_definitions(__cpp_lib_format=201907L)

#######################################################
#                       BUILD                         #
#######################################################

add_library(DBFLib)

include(script/EnumGenerator/EnumGenerator.cmake)

set(ENUM_JSONS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Rune.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Stat.json")

Generate_Enum(${ENUM_JSONS})

target_link_libraries(DBFLib PUBLIC DofusBotFM::Stat DofusBotFM::Rune)

target_sources(
    DBFLib
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FM.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/FM.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Item.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Item.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ItemJsonFormatExemple.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RuneApplicationInterface.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RuneProperties.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RuneProperties.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsDensity.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsDensity.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsRunes.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsRunes.cpp"
        )

target_link_libraries(DBFLib PUBLIC nlohmann_json::nlohmann_json)

add_executable(DofusBotFM)
target_sources(DofusBotFM PRIVATE "src/main.cpp")
target_link_libraries(DofusBotFM DBFLib)
target_include_directories(
    DBFLib
    PUBLIC
        ${GENERATED_SOURCES_FOLDER}
    PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")

#######################################################
#                        TEST                         #
#######################################################

# Add a way to access private headers for testing
# Use set_property(TARGET <YourProject> PROPERTY DBFLib_PRIVATE_HEADERS 1) to enable it
target_include_directories(DBFLib PUBLIC "$<BUILD_INTERFACE:$<$<BOOL:$<TARGET_PROPERTY:DBFLib_PRIVATE_HEADERS>>:${CMAKE_CURRENT_SOURCE_DIR}/src>>")

enable_testing()
add_subdirectory(test)
