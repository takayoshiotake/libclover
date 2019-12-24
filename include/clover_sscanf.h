#pragma once

#include <stdarg.h>


// Supported formats are:
//   - %%
//   - %d, %ld
//   - %u, %lu
//   - %f, %lf
//   - %s
//   - whitespace (" ")
//   - some character
// 
// NOTE: Not supported scanset likes "%[^ ]"
extern int clover_sscanf(char const * str, char const * format, ...);
extern int clover_vsscanf(char const * str, char const * format, va_list arg);
