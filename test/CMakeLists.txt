cmake_minimum_required(VERSION 3.1)

project(test C)
add_executable(a.out main.c)

target_compile_options(a.out PUBLIC -W -Wall)
target_compile_options(a.out PUBLIC
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:MiniSizeRel>:-Os>
  $<$<CONFIG:RelWithDebgInfo>:-O3 -g>
  )
target_compile_definitions(a.out PUBLIC
  $<$<CONFIG:Debug>:_DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
  )

target_link_libraries(a.out clover)
