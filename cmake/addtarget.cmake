function(addExecutable target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" sources)
    file(GLOB_RECURSE
        headers
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.hpp"
    )
    file(GLOB_RECURSE
        ui
        "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
    )

    add_executable(
        ${target}
        ${sources}
        ${headers}
        ${ui}
    )

    target_include_directories(${target} PRIVATE include)
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

    useSanitize(${target})
endfunction(addExecutable)


function(addLibrary target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" sources)
    file(GLOB_RECURSE
        headers
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.hpp"
    )
    file(GLOB_RECURSE
        ui
        "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
    )

    add_library(
        ${target}
        OBJECT
        ${sources}
        ${headers}
        ${ui}
    )

    target_include_directories(${target} PUBLIC include)
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

    useSanitize(${target})
endfunction(addLibrary)
