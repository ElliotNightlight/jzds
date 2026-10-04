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

	struct jzds_arrdeq ad;
	jzdsX_arrdeq_init(&ad, sizeof(int));

	for (int i = 1; i <= N * 2; ++i) {
		int val = i * i;
		jzdsX_arrdeq_push(&ad, &val);
	}
	assert((int)jzds_arrdeq_len(&ad) == N * 2);

	for (int i = 1; i <= N; ++i) {
		int exp = i * i;
		int val;
		jzds_arrdeq_shift(&ad, &val);
		assert(val == exp);
	}
	assert((int)jzds_arrdeq_len(&ad) == N);

	for (int i = 1; i <= N * 2; ++i) {
		int val = i * i * i;
		jzdsX_arrdeq_unshift(&ad, &val);
	}
	assert((int)jzds_arrdeq_len(&ad) == N * 3);

	for (size_t idx = 0; (int)idx != N * 3; ++idx) {
		int exp;
		if ((int)idx < N * 2) {
			int i = N * 2 - idx;
			exp = i * i * i;
		} else {
			int i = idx - N + 1;
			exp = i * i;
		}
		int val = *(int*)jzds_arrdeq_at(&ad, idx);
		assert(val == exp);
	}

	for (int z = N; z--;) {
		jzds_arrdeq_shift(&ad, NULL);
		jzds_arrdeq_pop(&ad, NULL);
	}
	assert((int)jzds_arrdeq_len(&ad) == N);

	for (int i = 1; i <= N; ++i) {
		int exp = i * i * i;
		int val;
		jzds_arrdeq_pop(&ad, &val);
		assert(val == exp);
	}
	assert(jzds_arrdeq_len(&ad) == 0);

	jzds_arrdeq_cleanup(&ad);

	fputs("ok\n", stdout);
	return 0;
}
