if(TARGET broadmark)
    return()
endif()

message(STATUS "Third-party: creating target 'broadmark'")

include(FetchContent)
FetchContent_Declare(
    broadmark
    GIT_REPOSITORY https://github.com/dbelgrod/Broadmark.git
    GIT_TAG master
    GIT_SHALLOW FALSE
)
FetchContent_GetProperties(broadmark)

if(NOT broadmark_POPULATED)
    FetchContent_Populate(broadmark)
    add_subdirectory(${broadmark_SOURCE_DIR} ${broadmark_BINARY_DIR})
endif()

target_include_directories(broadmark PUBLIC
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms"
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms/Dependencies" # Add Bullet3 include directory
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms/Dependencies/Bullet3/Bullet3Common"
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms/Dependencies/Bullet3"
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms/Dependencies/Bullet3/Bullet3Collision/BroadPhaseCollision"
    "${broadmark_SOURCE_DIR}/Broadmark/Algorithms/Dependencies/Bullet2"
)
