cmake_minimum_required(VERSION 3.1)

project(clover C)
add_library(clover STATIC
  src/clover_sscanf.c
  )

target_include_directories(clover PUBLIC -I include)
if(APPLE)
target_compile_options(clover PUBLIC -W -Wall)
target_compile_options(clover PUBLIC
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:MiniSizeRel>:-Os>
  $<$<CONFIG:RelWithDebgInfo>:-O3 -g>
  )
elseif(WIN32)
target_compile_options(clover PUBLIC -Wall)
target_compile_options(clover PUBLIC
  $<$<CONFIG:Debug>:-Od -g>
  $<$<CONFIG:Release>:-O2>
  $<$<CONFIG:MiniSizeRel>:-O1>
  $<$<CONFIG:RelWithDebgInfo>:-O2 -g>
  )
endif()
target_compile_definitions(clover PUBLIC
  $<$<CONFIG:Debug>:_DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
  )

add_subdirectory(test)
