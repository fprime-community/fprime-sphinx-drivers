set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/SphinxUartOnboardDriverComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/SphinxUartOnboardDriverComponentImpl.cpp"
        )
set(MOD_DEPS
        fprime-sphinx-drivers/Util
        fprime-sphinx-drivers/Ports/SphinxUart_bytesUsedPort
        fprime-sphinx-drivers/Ports/SphinxUart_readPort
        fprime-sphinx-drivers/Ports/SphinxUart_writePort
        )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
    list(APPEND MOD_DEPS
        "fprime-vxworks/VxWorks"
    )
endif()
register_fprime_module()
set(UT_MOD_DEPS
        fprime-sphinx-drivers/Util/LinuxDrvReg
        fprime-sphinx-drivers/Random
        fprime-sphinx-drivers/Util
        fprime-sphinx-drivers/Ports/SphinxUart_bytesUsedPort
        fprime-sphinx-drivers/Ports/SphinxUart_readPort
        fprime-sphinx-drivers/Ports/SphinxUart_writePort
        )
set(UT_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/BytesUsed.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Init.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Interrupt.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Reader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Writer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/ut/Scenarios/Selected.cpp"

        )
register_fprime_ut()
