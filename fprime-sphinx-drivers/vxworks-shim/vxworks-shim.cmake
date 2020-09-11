# Find sources for VxWorks Os
get_target_property(OS_SOURCE fprime-vxworks_VxWorks SOURCES)
# Filter out default Posix implementation
list(FILTER OS_SOURCE EXCLUDE REGEX ".*IntervalTimer\.cpp")
list(APPEND OS_SOURCE "${CMAKE_CURRENT_LIST_DIR}/../Os/VxWorks/IntervalTimer.cpp")
# Reset source property
set_target_properties(fprime-vxworks_VxWorks PROPERTIES SOURCES "${OS_SOURCE}")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Sphinx-VxWorks6")
  # Filter out default Linux implementation
  get_target_property(FATAL_SOURCES Svc_FatalHandler SOURCES)	
  list(FILTER FATAL_SOURCES EXCLUDE REGEX ".*LinuxImpl\.cpp")	
  list(APPEND FATAL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/FatalHandlerComponentVxWorksImpl.cpp")	
  # Reset source property	
  set_target_properties(Svc_FatalHandler PROPERTIES SOURCES "${FATAL_SOURCES}")
endif()
