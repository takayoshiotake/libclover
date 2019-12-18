#include <assert.h>
#include <stdio.h>

#include "clover_sscanf.h"


int main(void) {
	{
		int d1;
		int d2;
		int scanned_count = clover_sscanf("100, -20", "%d, %d", &d1, &d2);
		printf("%d: %d, %d\n", scanned_count, d1, d2);
	}

	{
		float f1;
		float f2;
		int scanned_count = clover_sscanf("[-10.3e-4, 1e3]", "[%f, %f]", &f1, &f2);
		printf("%d: %f, %f\n", scanned_count, f1, f2);
	}

	{
		char s1[16];
		char s2[16];
		int scanned_count = clover_sscanf("Hello, world!", "%s %s", s1, s2);
		printf("%d: %s, %s\n", scanned_count, s1, s2);
	}

	{
		int d;
		float f;
		char s[16];
		int scanned_count = clover_sscanf("123-3.5e1test.123", "%d%f%s", &d, &f, s);
		printf("%d: %d, %f, %s\n", scanned_count, d, f, s);
	}

	return 0;
}
