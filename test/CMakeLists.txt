set(script_copy_directory "${CMAKE_BINARY_DIR}/_cmake/copy_directory.cmake")
file(WRITE "${script_copy_directory}" "
    if(NOT IS_DIRECTORY \"\${DIR_SRC}\" OR \"\${DIR_DST}\" STREQUAL \"\")
        message(FATAL_ERROR \"Internal error while calling copy_directory script!
            src[\${DIR_SRC}]
            dst[\${DIR_DST}]
        \")
    endif()
    file(GLOB_RECURSE files RELATIVE \"\${DIR_SRC}\" \"\${DIR_SRC}/*.*\")
    foreach(entry \${files})
        set(src \"\${DIR_SRC}/\${entry}\")
        set(dst \"\${DIR_DST}/\${entry}\")
        file(TIMESTAMP \"\${src}\" src_ts UTC)
        file(TIMESTAMP \"\${dst}\" dst_ts UTC)
        if(src_ts STRGREATER dst_ts)
            execute_process(COMMAND \"${CMAKE_COMMAND}\" -E copy \"\${src}\" \"\${dst}\")
        endif()
    endforeach()
    message(STATUS \"copy done: \${DIR_SRC} -> \${DIR_DST} \")
")

function(use_assets TGT)
    add_custom_target(${TGT}_assets
            COMMAND ${CMAKE_COMMAND}
            "-DDIR_SRC=${CMAKE_SOURCE_DIR}/assets"
            "-DDIR_DST=$<TARGET_FILE_DIR:${TGT}>/assets"
            -P "${script_copy_directory}")
    add_dependencies(${TGT} ${TGT}_assets)
endfunction()


if (OALPP_ENABLE_INTEGRATION_TESTS)
    add_subdirectory(integration_tests)
endif ()

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()

if (OALPP_ENABLE_APPROVAL_TESTS)
    add_subdirectory(approval_tests)
endif ()
