set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/SphinxDrvTimerUtil.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/SphinxDrvUtil.cpp"
        )
set(MOD_DEPS
        Fw/Types
        Fw/Cfg
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    list(APPEND SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/SphinxAtomicUtilVxWorks.cpp"
    )
    list(APPEND MOD_DEPS
        "fprime-vxworks/VxWorks"
    )
else()
    list(APPEND SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/SphinxAtomicUtilCompiler.cpp"
    )
endif()

register_fprime_module()
set(UT_MOD_DEPS
        Fw/Types
        Fw/Cfg
        Os
        )
set(UT_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/AtomicBitTwiddleTester.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/AtomicUtilTester.cpp"
        )
register_fprime_ut()
