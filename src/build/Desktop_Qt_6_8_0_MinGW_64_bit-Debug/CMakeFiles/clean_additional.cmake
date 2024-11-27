# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CoffeeHouseSoftware_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CoffeeHouseSoftware_autogen.dir\\ParseCache.txt"
  "CoffeeHouseSoftware_autogen"
  )
endif()
