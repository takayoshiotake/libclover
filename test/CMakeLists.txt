cmake_minimum_required(VERSION 3.1)

project(test C)
add_executable(a.out main.c)

if(APPLE)
target_compile_options(a.out PUBLIC -W -Wall)
target_compile_options(a.out PUBLIC
  $<$<CONFIG:Debug>:-O0 -g>
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:MiniSizeRel>:-Os>
  $<$<CONFIG:RelWithDebgInfo>:-O3 -g>
  )
elseif(WIN32)
target_compile_options(a.out PUBLIC -Wall)
target_compile_options(a.out PUBLIC
  $<$<CONFIG:Debug>:-Od -g>
  $<$<CONFIG:Release>:-O2>
  $<$<CONFIG:MiniSizeRel>:-O1>
  $<$<CONFIG:RelWithDebgInfo>:-O2 -g>
  )
endif()
target_compile_definitions(a.out PUBLIC
  $<$<CONFIG:Debug>:_DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
  )

target_link_libraries(a.out clover)
