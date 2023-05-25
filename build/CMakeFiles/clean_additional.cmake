# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appAutoNota_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appAutoNota_autogen.dir\\ParseCache.txt"
  "appAutoNota_autogen"
  )
endif()
