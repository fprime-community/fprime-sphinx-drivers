if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    SET(SOURCE_FILES
            "${CMAKE_CURRENT_LIST_DIR}/VxWorks/IntervalTimer.cpp"
            )
    # Shared libraries need an -rt dependency for mq libs
    if (BUILD_SHARED_LIBS)
        list(APPEND MOD_DEPS "-lrt")
    endif()
else()
    SET(SOURCE_FILES
            "${CMAKE_CURRENT_LIST_DIR}/Linux/TaskLock.cpp"
            )
endif()
register_fprime_module()
