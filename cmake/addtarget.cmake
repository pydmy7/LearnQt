function(addExecutable target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" sources)

    file(GLOB_RECURSE
        headers
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.hpp"
    )

    if (CMAKE_AUTOUIC)
        file(GLOB_RECURSE
            ui
            "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
        )
    else()
        set(ui "")
    endif()

    if (CMAKE_AUTORCC)
        file(GLOB_RECURSE
            qrc
            "${CMAKE_CURRENT_SOURCE_DIR}/qrc/*.qrc"
        )
    else()
        set(qrc "")
    endif()

    add_executable(
        ${target}
        ${sources}
        ${headers}
        ${ui}
        ${qrc}
    )

    target_include_directories(${target} PRIVATE include)
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

    useSanitize(${target})
    
    if (myself)
        # useClangFormat(${target} ${CMAKE_CURRENT_SOURCE_DIR})
        # useClangTidy(${target})
    endif()
endfunction(addExecutable)


function(addLibrary target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" sources)

    file(GLOB_RECURSE
        headers
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}/*.hpp"
    )

    if (CMAKE_AUTOUIC)
        file(GLOB_RECURSE
            ui
            "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
        )
    else()
        set(ui "")
    endif()
    
    if (CMAKE_AUTORCC)
        file(GLOB_RECURSE
            qrc
            "${CMAKE_CURRENT_SOURCE_DIR}/qrc/*.qrc"
        )
    else()
        set(qrc "")
    endif()

    add_library(
        ${target}
        OBJECT
        ${sources}
        ${headers}
        ${ui}
        ${qrc}
    )

    target_include_directories(${target} PUBLIC include)
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

    useSanitize(${target})
    
    if (myself)
        # useClangFormat(${target} ${CMAKE_CURRENT_SOURCE_DIR})
        # useClangTidy(${target})
    endif()
endfunction(addLibrary)
