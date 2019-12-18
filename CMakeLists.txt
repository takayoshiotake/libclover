cmake_minimum_required(VERSION 3.1)

project(clover C)
add_library(clover STATIC
  src/clover_sscanf.c
  )

target_include_directories(clover PUBLIC -I include)
target_compile_options(clover PUBLIC -W -Wall)
target_compile_options(clover PUBLIC
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:MiniSizeRel>:-Os>
  $<$<CONFIG:RelWithDebgInfo>:-O3 -g>
  )
target_compile_definitions(clover PUBLIC
  $<$<CONFIG:Debug>:_DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
  )

add_subdirectory(test)
