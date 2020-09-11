get_directory_property(COMP_DEFS COMPILE_DEFINITIONS)

if(COMP_DEFS MATCHES "TGT_OS_TYPE_VXWORKS")
  set(SOURCE_FILES	
          "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentVxWorksImpl.cpp"	
     )
else()
  set(SOURCE_FILES
          "${FPRIME_FRAMEWORK_PATH}/Svc/FatalHandler/FatalHandlerComponentLinuxImpl.cpp"
     )
endif()

set(MOD_DEPS
        Svc/FatalHandler
    )

register_fprime_module()
