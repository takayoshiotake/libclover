#include "clover_sscanf.h"
#include <stdarg.h>


static int count_whitespace(char const * str) {
	char const * base = str;
	while (*str == '\r' || *str == '\t' || *str == '\n' || *str == ' ') {
		++str;
	}
	return (int)(str - base);
}


int clover_sscanf(char const * str, char const * format, ...) {
	va_list arg;
	int scanned_count;
	va_start(arg, format);
	scanned_count = clover_vsscanf(str, format, arg);
	va_end(arg);
	return scanned_count;
}

int clover_vsscanf(char const * str, char const * format, va_list arg) {
	int scanned_count = 0;
	while (*format && *str) {
		if (*format == '%') {
			int isLong = 0;
			++format;
			if (!*format) {
				goto DONE;
			}

			if (*format == 'l') {
				++format;
				if (*format == 'd') {
					isLong = 1;
				}
				else if (*format == 'u') {
					isLong = 1;
				}
				else if (*format == 'f') {
					isLong = 1;
				}
				else {
					goto DONE;
				}
			}

			str += count_whitespace(str);
			if (*format == '%') {
				++format;
				if (*str != '%') {
					goto DONE;
				}
				++str;
			}
			else if (*format == 'd') {
				char const * start = str;
				int d = 0;
				int negate = 0;

				++format;
				if (*str == '-') {
					negate = 1;
					++str;
				}
				while (*str >= '0' && *str <= '9') {
					d *= 10;
					d += *str - '0';
					++str;
				}
				if (negate) {
					d *= -1;
				}

				if (str == start) {
					goto DONE;
				}
				if (isLong) {
					*va_arg(arg, long *) = d;
				}
				else {
					*va_arg(arg, int *) = d;
				}
				++scanned_count;
			}
			else if (*format == 'u') {
				char const * start = str;
				int u = 0;

				++format;
				while (*str >= '0' && *str <= '9') {
					u *= 10;
					u += *str - '0';
					++str;
				}

				if (str == start) {
					goto DONE;
				}
				if (isLong) {
					*va_arg(arg, unsigned long *) = u;
				}
				else {
					*va_arg(arg, unsigned int *) = u;
				}
				++scanned_count;
			}
			else if (*format == 'f' && isLong) {
				char const * start = str;
				double f = 0;
				int negate = 0;

				++format;
				if (*str == '-') {
					negate = 1;
					++str;
				}
				while (*str >= '0' && *str <= '9') {
					f *= 10;
					f += *str - '0';
					++str;
				}
				if (*str == '.') {
					double scale = 0.1;

					++str;
					while (*str >= '0' && *str <= '9') {
						f += (*str - '0') * scale;
						scale *= 0.1;
						++str;
					}
				}
				if (*str == 'e') {
					int exponent = 0;
					int negate_exponent = 0;

					++str;
					if (*str == '-') {
						negate_exponent = 1;
						++str;
					}
					while (*str >= '0' && *str <= '9') {
						exponent *= 10;
						exponent += *str - '0';
						++str;
					}
					if (negate_exponent) {
						while (exponent > 0) {
							f *= 0.1;
							--exponent;
						}
					}
					else {
						while (exponent > 0) {
							f *= 10;
							--exponent;
						}
					}
				}
				if (negate) {
					f *= -1;
				}

				if (str == start) {
					goto DONE;
				}
				*va_arg(arg, double *) = f;
				++scanned_count;
			}
			else if (*format == 'f') {
				char const * start = str;
				float f = 0;
				int negate = 0;

				++format;
				if (*str == '-') {
					negate = 1;
					++str;
				}
				while (*str >= '0' && *str <= '9') {
					f *= 10;
					f += *str - '0';
					++str;
				}
				if (*str == '.') {
					float scale = 0.1f;

					++str;
					while (*str >= '0' && *str <= '9') {
						f += (*str - '0') * scale;
						scale *= 0.1f;
						++str;
					}
				}
				if (*str == 'e') {
					int exponent = 0;
					int negate_exponent = 0;

					++str;
					if (*str == '-') {
						negate_exponent = 1;
						++str;
					}
					while (*str >= '0' && *str <= '9') {
						exponent *= 10;
						exponent += *str - '0';
						++str;
					}
					if (negate_exponent) {
						while (exponent > 0) {
							f *= 0.1f;
							--exponent;
						}
					}
					else {
						while (exponent > 0) {
							f *= 10;
							--exponent;
						}
					}
				}
				if (negate) {
					f *= -1;
				}

				if (str == start) {
					goto DONE;
				}
				*va_arg(arg, float *) = f;
				++scanned_count;
			}
			else if (*format == 's') {
				char const * start = str;
				char * s = va_arg(arg, char *);
				++scanned_count;

				++format;
				while (*str && *str != '\r' && *str != '\t' && *str != '\n' && *str != ' ') {
					*s++ = *str;
					++str;
				}
				*s = '\0';
				if (str == start) {
					goto DONE;
				}
			}
			else {
				// Not supported format...
				goto DONE;
			}
		}
		else if (*format == ' ') {
			// white space
			++format;
			str += count_whitespace(str);
		}
		else if (*format == *str) {
			// some character
			++format;
			++str;
		}
		else {
			goto DONE;
		}
	}
DONE:
	return scanned_count;
}
