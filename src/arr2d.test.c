/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <stdio.h> /* fputs() */
#include <assert.h> /* assert() */
#include "jzdsx.h"

int main(void)
{
	const int H = 7, W = 10;

	struct jzds_arr2d a2;
	jzdsX_arr2d_init(&a2, sizeof(int), H, W);

	assert((int)a2.hgt == H);
	assert((int)a2.wdt == W);

	for (int i = 0; i != H; ++i) {
		for (int j = 0; j != W; ++j) {
			int val = i * i + j;
			*(int*)jzds_arr2d_at(&a2, i, j) = val;
		}
	}
	for (int i = 0; i != H; ++i) {
		for (int j = 0; j != W; ++j) {
			int exp  = i * i + j;
			int val = ((int*)a2.dat)[i * W + j];
			assert(val == exp);
		}
	}

	for (int i = 0; i != H; ++i) {
		for (int j = 0; j != W; ++j) {
			int val = i + j * j;
			((int*)a2.dat)[i * W + j] = val;
		}
	}
	for (int i = 0; i != H; ++i) {
		for (int j = 0; j != W; ++j) {
			int exp  = i + j * j;
			int val = *(int*)jzds_arr2d_at(&a2, i, j);
			assert(val == exp);
		}
	}

	jzds_arr2d_cleanup(&a2);

	fputs("ok\n", stdout);
	return 0;
}
