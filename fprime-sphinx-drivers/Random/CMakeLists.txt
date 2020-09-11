get_directory_property(COMP_DEFS COMPILE_DEFINITIONS)

if(COMP_DEFS MATCHES "TGT_OS_TYPE_VXWORKS")
  set(SOURCE_FILES
          "${CMAKE_CURRENT_LIST_DIR}/RandomStub.cpp"
     )
else()
  set(SOURCE_FILES
          "${CMAKE_CURRENT_LIST_DIR}/bsd_random.c"
          "${CMAKE_CURRENT_LIST_DIR}/Random.cpp"
     )
endif()
register_fprime_module()
