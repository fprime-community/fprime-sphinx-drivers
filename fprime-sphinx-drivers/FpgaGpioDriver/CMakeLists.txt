set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/FpgaGpioDriverComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/FpgaGpioDriverComponentImpl.cpp"
        )
set(MOD_DEPS
        fprime-sphinx-drivers/Util
        )
register_fprime_module()
set(UT_MOD_DEPS
        )
set(UT_SOURCE_FILES

        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
        )
register_fprime_ut()
