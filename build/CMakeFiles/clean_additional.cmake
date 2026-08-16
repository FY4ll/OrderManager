# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/OrderManager_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/OrderManager_autogen.dir/ParseCache.txt"
  "OrderManager_autogen"
  )
endif()
