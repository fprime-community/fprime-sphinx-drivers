set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/GPTimerDriverComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/GPTimerDriverComponentImpl.cpp"
        )
set(MOD_DEPS
        fprime-sphinx-drivers/Util
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    list(APPEND MOD_DEPS
        "fprime-vxworks/VxWorks"
    )
endif()
register_fprime_module()
set(UT_MOD_DEPS
        fprime-sphinx-drivers/Random
        fprime-sphinx-drivers/Util
        )
set(UT_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Owner.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Read.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Write.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Scenarios/Selected.cpp"
        )
register_fprime_ut()
