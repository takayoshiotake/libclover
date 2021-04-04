#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "clover_sscanf.h"


static void expect_string(char const * expected, char * target_format, ...) {
	static char target[128];
	va_list arg;
	va_start(arg, target_format);
	vsprintf(target, target_format, arg);
	va_end(arg);
	assert(strcmp(expected, target) == 0);
}


void test_clover_sscanf(void);


int main(void) {
	test_clover_sscanf();
	return 0;
}


void test_clover_sscanf(void) {
	{
		int d1;
		int d2;
		int scanned_count = clover_sscanf("100, -20", "%d, %d", &d1, &d2);
		expect_string("2: 100, -20", "%d: %d, %d", scanned_count, d1, d2);
	}

	{
		float f1;
		float f2;
		int scanned_count = clover_sscanf("[-10.3e-4, 1e3]", "[%f, %f]", &f1, &f2);
		expect_string("2: -0.001030, 1000.000000", "%d: %.6f, %.6f", scanned_count, f1, f2);
	}

	{
		char s1[16];
		char s2[16];
		int scanned_count = clover_sscanf("Hello, world!", "%s %s", s1, s2);
		expect_string("2: Hello,, world!", "%d: %s, %s", scanned_count, s1, s2);
	}

	{
		int d;
		float f;
		char s[16];
		int scanned_count = clover_sscanf("123-3.5e1test.123", "%d%f%s", &d, &f, s);
		expect_string("3: 123, -35.000000, test.123", "%d: %d, %.6f, %s", scanned_count, d, f, s);
	}
}
