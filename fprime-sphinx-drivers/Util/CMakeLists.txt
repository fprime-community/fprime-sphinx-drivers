set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/SphinxDrvTimerUtil.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/SphinxDrvUtil.cpp"
        )
set(MOD_DEPS
        Fw/Types
        Fw/Cfg
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    list(APPEND MOD_DEPS
        "fprime-vxworks/VxWorks"
    )
endif()
register_fprime_module()
set(UT_MOD_DEPS
        fprime-sphinx-drivers/Util/LinuxDrvReg
        Fw/Types
        Fw/Cfg
        Os
        )
set(UT_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/AtomicBitTwiddleTester.cpp"
        )
register_fprime_ut()

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/LinuxDrvReg/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlightDrvReg/")
