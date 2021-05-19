set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/WakeupManagerComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/WakeupManagerComponentImpl.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/WakeupQueue.cpp"
        )
set(UT_MOD_DEPS
        fprime-sphinx-drivers/Util
        Fw/Types
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    list(APPEND MOD_DEPS
        "fprime-vxworks/VxWorks"
    )
endif()
register_fprime_module()
set(UT_MOD_DEPS
        fprime-sphinx-drivers/Util
        Fw/Types
        Os
        )
set(UT_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/WakeupQueueTester.cpp"
        )
register_fprime_ut()
