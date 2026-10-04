/*
 * Copyright (c) 2026 Jan Zakrzewski
 * Licensed under the MIT License.
 */

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <stdio.h> /* fputs() */
#include <assert.h> /* assert() */
#include <string.h> /* memset() */
#include "jzdsx.h"

int main(void)
{
	const size_t X = 5;

	struct jzds_sparseset sps;
	jzdsX_sparseset_init(&sps, X);

	size_t val;
	size_t idx;
	bool found;

	jzds_sparseset_add(&sps, 3);
	jzds_sparseset_add(&sps, 4);
	jzds_sparseset_add(&sps, 1);
	jzds_sparseset_remove(&sps, 2);
	jzds_sparseset_add(&sps, 3);

	found = jzds_sparseset_find(&sps, 3, NULL);
	assert(found);

	val = 4;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(found);
	assert(idx < sps.cnt && sps.dense[idx] == val);

	val = 3;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(found);
	assert(idx < sps.cnt && sps.dense[idx] == val);

	idx = 123;
	found = jzds_sparseset_find(&sps, 2, &idx);
	assert(!found);
	assert(idx == 123);

	jzds_sparseset_remove(&sps, 4);
	jzds_sparseset_add(&sps, 0);
	jzds_sparseset_add(&sps, 2);
	jzds_sparseset_remove(&sps, 0);
	jzds_sparseset_remove(&sps, 0);
	jzds_sparseset_add(&sps, 2);

	val = 0;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(!found);

	val = 1;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(found);
	assert(idx < sps.cnt && sps.dense[idx] == val);

	val = 2;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(found);
	assert(idx < sps.cnt && sps.dense[idx] == val);

	val = 3;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(found);
	assert(idx < sps.cnt && sps.dense[idx] == val);

	val = 4;
	found = jzds_sparseset_find(&sps, val, &idx);
	assert(!found);

	assert(sps.cnt == 3);
	bool set[X];
	memset(set, 0, sizeof set);
	for (size_t i = 0; i != sps.cnt; ++i) {
		size_t val = sps.dense[i];
		set[val] = true;
	}

	assert(!set[0]);
	assert(set[1]);
	assert(set[2]);
	assert(set[3]);
	assert(!set[4]);

	jzds_sparseset_cleanup(&sps);

	fputs("ok\n", stdout);
	return 0;
}
