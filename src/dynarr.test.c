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
	const int N = 10;

	struct jzds_dynarr my_da;
	jzds_dynarr_init(&my_da, sizeof(int));

	for (int i = 0; i != N * 2; ++i) {
		int val = i * i;
		jzdsX_dynarr_push(&my_da, &val);
	}
	assert((int)my_da.len == N * 2);
	assert(my_da.len <= my_da.cap);

	for (int z = N; z--;) {
		int val;
		jzds_dynarr_pop(&my_da, &val);
		int i = my_da.len;
		int exp = i * i;
		assert(val == exp);
	}
	assert((int)my_da.len == N);

	for (int z = N * 2; z--;) {
		int val = -1;
		jzds_dynarr_push(&my_da, &val);
	}
	assert((int)my_da.len == N * 3);
	assert(my_da.len <= my_da.cap);

	for (int i = 0; i != N * 3; ++i) {
		int exp = i < N ? i * i : -1;
		int val1 = *(int*)jzds_dynarr_at(&my_da, i);
		int val2 = ((int*)my_da.dat)[i];
		assert(val1 == exp);
		assert(val2 == exp);
	}

	for (int z = N * 3; z--;)
		jzds_dynarr_pop(&my_da, NULL);
	assert(my_da.len == 0);

	jzds_dynarr_cleanup(&my_da);

	fputs("ok\n", stdout);
	return 0;
}
